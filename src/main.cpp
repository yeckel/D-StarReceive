#include "Arduino.h"
#include <RadioLib.h>
#include <Streaming.h>
#include "BitSlicer.h"
#include "Scrambler.h"
#include "SlowAmbe.h"
#include "DSTAR.h"
#include "BitMatcher.h"

#define LORA_CS 18      // GPIO18 - SX1276 CS
#define LORA_RST 23     // GPIO23 - SX1276 RST
#define LORA_IRQ 26     // GPIO26 - SX1276 IO0
#define LORA_IO0 LORA_IRQ  // alias
#define LORA_IO1 33     // GPIO33 - SX1276 IO1 -> wired on pcb AND connected to header pin LORA1
#define LORA_IO2 32     // GPIO32 - SX1276 IO2 -> wired on pcb AND connected to header pin LORA2

SX1278 radio = new Module(LORA_CS, LORA_IRQ, LORA_RST, LORA_IO1);

#define BUFSIZE 42          //size of bufferTxRx
uint8_t bufferTxRx[BUFSIZE];
uint8_t history[BUFSIZE * 8];  //buffer for viterbi decoding (large buffer need)
uint8_t syncWord[] = {0xaa, 0xaa, 0xaa, 0xaa, 0xEC, 0xA0};
static constexpr uint8_t endSyncData[] = {0xaa, 0xaa, 0xaa, 0xaa, 0x13, 0x5e};
float f = 434.800f + 0.00244f;//t-beam sx1278 has XTAL offset

volatile bool inSync = false;
volatile bool receivedPacket = false;

BitMatcher bm(endSyncData, sizeof(endSyncData));
uint8_t headerBuff[BitSlicer::HEADER_SIZE];
uint8_t dataBuff[70 * BitSlicer::DATA_FRAME_SIZE];
BitSlicer bs;

void checkLoraState(int state)
{
    if(state == ERR_NONE)
    {
        Serial.println(F("success!"));
    }
    else
    {
        Serial.print(F("failed, code "));
        Serial.println(state);
        while(true);
    }
}


void receivedSyncWord(void)
{
    inSync = true;
}


void dataClk()
{
    auto receivedBit = digitalRead(LORA_IO2);
    if(!inSync)
    {
        return;
    }
    auto isEnd = bm.appendAndCheck(receivedBit);
    if(isEnd)
    {
        inSync = false;
        receivedPacket = true;
        bm.reset();
    }
    else
    {
        bs.appendBit(receivedBit);
        //        Serial << receivedBit;
    }
}

void decodeHeader(uint8_t* bufferConv)
{
    Dstar.pseudo_random(bufferConv, 660);
    Dstar.deInterleave(bufferConv);
    Dstar.viterbi(bufferConv, history, bufferTxRx); //decode data
    Serial << endl;

    Serial <<  endl <<  "Nb errors:";
    Serial << int(Dstar.acc_error[1][0]) << endl;    //print nb errors

    Serial << "Checking crc: " << Dstar.check_crc(bufferTxRx) << endl;    //crc testing

    Serial << endl << "RF Header:";
    for(uint i = 0; i < sizeof(bufferTxRx); i++)
    {
        if(bufferTxRx[i] >= 0x20 && bufferTxRx[i] <= 0x7F)
        {
            Serial << char(bufferTxRx[i]);
        }
        else
        {
            Serial << "0x" << _HEX(bufferTxRx[i]) << " ";
        }
    }
    Serial << endl;
}

void setup()
{
    Serial.begin(115200);
    bs.setBuffer(headerBuff, sizeof(headerBuff), dataBuff, sizeof(dataBuff));
    Dstar.size_buffer = BUFSIZE;
    pinMode(LORA_IO2, INPUT);
    pinMode(LORA_IO1, INPUT);
    radio.reset();
    Serial.print(F("[SX1278] Initializing ... "));
    checkLoraState(radio.beginFSK(f, 4.8f, 4.8 * 0.25f, 25.0f, 3, 64, false));
    /// Uncomment to fine tune the radio and find sx1278 frequency offset
    MorseClient morse(&radio);
    morse.begin(f);
    morse.startSignal();
    morse.print("001");
    checkLoraState(radio.setEncoding(RADIOLIB_ENCODING_NRZ));
    checkLoraState(radio.setDataShaping(RADIOLIB_SHAPING_0_5));

    radio.setDio0Action(receivedSyncWord);
    radio.setDio1Action(dataClk);

    checkLoraState(radio.enableOokBitSychronizer());
    checkLoraState(radio.receiveDirect());
    checkLoraState(radio.setSyncWord(syncWord, sizeof(syncWord)));
}

void processPacket()
{
    auto dataFrames = bs.getDataFrameCount();
    SlowAmbe sa;
    for(uint i = 0 ; i < dataFrames; i++)
    {
        if(!isSyncFrame(dataBuff + i * BitSlicer::DATA_FRAME_SIZE))
        {
            scramble(dataBuff + i * BitSlicer::DATA_FRAME_SIZE, BitSlicer::DATA_FRAME_SIZE);
            sa.receiveData(dataBuff + i * BitSlicer::DATA_FRAME_SIZE + 9);
        }
        //        for(uint j = 0; j < BitSlicer::DATA_FRAME_SIZE; j++)
        //        {
        //            Serial << "0x" << _HEX(dataBuff[i * BitSlicer::DATA_FRAME_SIZE + j]) << ",";
        //        }
        //        Serial << endl;
    }
    Serial << endl;
    {
        uint16_t size{0};
        uint8_t* dStarData = sa.getDStarGPSData(size);
        Serial << "GPSData size: " << size << " val:";
        for(uint16_t i = 0; i < size ; i++)
        {
            if(dStarData[i] == 0x0d)
            {
                break;
            }
            else
            {
                Serial << char(dStarData[i]);
            }
        }
        Serial << endl;
    }
    {
        uint16_t size{0};
        uint8_t* dStarData = sa.getDStarRFHeader(size);
        Serial << "Headersize: " << size << " val:";
        for(uint16_t i = 0; i < size ; i++)
        {
            Serial << char(dStarData[i]);
        }
        Serial << endl;
    }
    {
        uint16_t size{0};
        uint8_t* dStarData = sa.getDStarMsg(size);
        Serial << "MSGsize: " << size << " val:";
        for(uint16_t i = 0; i < size ; i++)
        {
            Serial << char(dStarData[i]);
        }
        Serial << endl;
    }
}

void loop()
{
    if(receivedPacket)
    {
        if(bs.haveHeader())
        {
            decodeHeader(headerBuff);
        }
        processPacket();
        receivedPacket = false;
        bs.reset();
        radio.receiveDirect();//reset IRQ flags
    }
}
