#include "Arduino.h"
#include <BluetoothSerial.h>
#include <RadioLib.h>
#include <Streaming.h>
#include "BitSlicer.h"
#include "Scrambler.h"
#include "SlowAmbe.h"
#include "DSTAR.h"

#define LORA_CS 18      // GPIO18 - SX1276 CS
//#define LORA_RST 23     // GPIO23 - SX1276 RST
#define LORA_IRQ 26     // GPIO26 - SX1276 IO0
#define LORA_IO0 LORA_IRQ  // alias
#define LORA_IO1 33     // GPIO33 - SX1276 IO1 -> wired on pcb AND connected to header pin LORA1
#define LORA_IO2 32     // GPIO32 - SX1276 IO2 -> wired on pcb AND connected to header pin LORA2

SX1278 radio = new Module(LORA_CS, LORA_IRQ, LORA_RST, LORA_IO1);

#define BUFSIZE 42          //size of bufferTxRx
uint8_t bufferTxRx[BUFSIZE];
uint8_t history[BUFSIZE * 8];  //buffer for viterbi decoding (large buffer need)
uint8_t syncWord[] = {0xaa, 0xaa, 0xaa, 0xaa, 0xEC, 0xA0};
float f = 434.800f + 0.00244f;//t-beam sx1278 has XTAL offset

volatile bool inSync = false;
volatile bool receivedPacket{false};

uint8_t headerBuff[BitSlicer::HEADER_SIZE];

BitSlicer bs;
SlowAmbe sa;
BluetoothSerial serialBT;

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
    Serial << "RX Started" << endl;
    digitalWrite(BUILTIN_LED, true);
}

void dataClk()
{
    auto receivedBit = digitalRead(LORA_IO2);
    if(!inSync)
    {
        return;
    }
    //    Serial << receivedBit;
    auto commStopped = bs.appendBit(receivedBit);
    if(commStopped)
    {
        Serial << endl << "RX Stopped" << endl;
        inSync = false;
        digitalWrite(BUILTIN_LED, false);
        receivedPacket = true;
    }
}

DSTAR dStar;
void decodeHeader(uint8_t* bufferConv)
{
    dStar.pseudo_random(bufferConv, 660);
    dStar.deInterleave(bufferConv);
    dStar.viterbi(bufferConv, history, bufferTxRx); //decode data
    Serial << endl;

    Serial <<  endl <<  "Nb errors:";
    Serial << int(dStar.acc_error[1][0]) << endl;    //print nb errors

    Serial << "Checking crc: " << dStar.check_crc(bufferTxRx) << endl;    //crc testing

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
    pinMode(LED_BUILTIN, OUTPUT);
    serialBT.begin("D-Star Beacon");
    bs.setHeaderBuffer(headerBuff, sizeof(headerBuff));
    pinMode(LORA_IO2, INPUT);
    pinMode(LORA_IO1, INPUT);
    radio.reset();
    Serial.print(F("[SX1278] Initializing ... "));
    checkLoraState(radio.beginFSK(f, 4.8f, 4.8 * 0.25f, 25.0f, 3, 64, false));
    radio.getFrequencyError(true);
    sa.setDataOutput(&serialBT);
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

void loop()
{
    if(receivedPacket)
    {
        Serial << "fd: " << radio.getFrequencyError(true) << endl;
        if(bs.haveHeader())
        {
            decodeHeader(headerBuff);
        }
        receivedPacket = false;
        bs.reset();
        radio.receiveDirect();//reset IRQ flags
        if(sa.haveDStarMsg())
        {
            auto m = sa.getDStarMsg();
            Serial << "Msg:\"";
            for(uint i = 0; i < 20; i++)
            {
                Serial << char(m[i]);
            }
            Serial << "\"" << endl;
        }
        sa.reset();
    }
    if(bs.isEvenDataReady())
    {
        auto data = bs.getEvenData();
        sa.receiveData(data + 9);
    }
    if(bs.isOddDataReady())
    {
        auto data = bs.getOddData();
        sa.receiveData(data + 9);
    }
}
