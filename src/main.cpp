#include "Arduino.h"
#include <RadioLib.h>
#include <Streaming.h>
#include "BitMatcher.h"
#include "BitSlicer.h"

#define LORA_CS 18      // GPIO18 - SX1276 CS
#define LORA_RST 23     // GPIO23 - SX1276 RST
#define LORA_IRQ 26     // GPIO26 - SX1276 IO0
#define LORA_IO0 LORA_IRQ  // alias
#define LORA_IO1 33     // GPIO33 - SX1276 IO1 -> wired on pcb AND connected to header pin LORA1
#define LORA_IO2 32     // GPIO32 - SX1276 IO2 -> wired on pcb AND connected to header pin LORA2

SX1278 radio = new Module(LORA_CS, LORA_IRQ, LORA_RST, LORA_IO1);

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

uint8_t syncWord[] = {0xaa, 0xaa, 0xaa, 0xaa, 0xEC, 0xA0};
static constexpr uint8_t endSyncData[] = {0xaa, 0xaa, 0xaa, 0xaa, 0x13, 0x5e};
float f = 434.800f - 0.00144f;//t-beam sx1278 has XTAL offset

volatile bool inSync = false;
volatile bool receivedPacket = false;

BitMatcher bm(endSyncData, sizeof(endSyncData));

void receivedSyncWord(void)
{
    inSync = true;
}

BitSlicer ba;
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
        ba.appendBit(receivedBit);
    }
}

void setup()
{
    Serial.begin(115200);

    pinMode(LORA_IO2, INPUT);
    pinMode(LORA_IO1, INPUT);
    radio.reset();
    Serial.print(F("[SX1278] Initializing ... "));
    checkLoraState(radio.beginFSK(f, 4.8f, 4.8 * 0.25f, 25.0f, 1, 64, false));
    /// Uncomment to fine tune the radio and find sx1278 frequency offset
    //    MorseClient morse(&radio);
    //    morse.begin(f);
    //    morse.startSignal();
    //    morse.print("001");
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
        Serial << endl;
        receivedPacket = false;
        ba.reset();
        radio.receiveDirect();//reset IRQ flags
    }
}
