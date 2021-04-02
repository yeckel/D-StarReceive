#include "SlowAmbe.h"
//#include <iostream>
#include <string.h>
#include <Streaming.h>

//using namespace std;
//auto& Serial = cout;
namespace
{
    static constexpr uint8_t PKT_LEN_MAP{0x0F};
    static constexpr uint8_t PKT_TYPE_MAP{0xF0};
    static constexpr uint8_t PKT_TYPE_MSG{0x40};//does not have a size
    static constexpr uint8_t PKT_TYPE_GPS{0x30};
    static constexpr uint8_t PKT_TYPE_HEADER{0x50};//repeatet RF header
    static constexpr uint8_t PKT_TYPE_SQUELCH{0x20};
    static constexpr uint8_t FILLER_BYTE{0x66};
}
uint8_t min(uint8_t a, uint8_t b)
{
    return a <= b ? a : b;
}
void SlowAmbe::storeData(uint8_t* buff, bool isFirst, uint8_t* dest, uint& pos)
{
    uint8_t cnt = isFirst ?
                  min(dataLen, 2) ://first line max 2 bytes
                  min(dataLen, 3); //2nd line max 3 bytes
    uint8_t offset = isFirst ? 1 : 0;
    for(uint8_t i = 0; i < cnt; i++)
    {
        dest[pos] = buff[i + offset];
        pos++;
    }
}

SlowAmbe::SlowAmbe()
{
    reset();
}

void SlowAmbe::receiveData(uint8_t* buff)
{
    bool isEven = !(lineNr % 2);
    if(isEven)
    {
        dataLen = (buff[0] & PKT_LEN_MAP);
        dataType = (buff[0] & PKT_TYPE_MAP);
        switch(dataType)
        {
        case PKT_TYPE_MSG:
            dataLen = 5;
            Serial << "T";
            storeData(buff, isEven, dStarMsg, posMSG);
            break;
        case PKT_TYPE_GPS:
            Serial << "A";
            storeData(buff, isEven, dStarGPS, posGPS);
            break;
        case PKT_TYPE_HEADER:
            Serial << "H";
            storeData(buff, isEven, dStarRFHeader, posRF);
            break;
        case PKT_TYPE_SQUELCH:
            Serial << "C";
            break;
        default:
            Serial << "U";//unknown
        }
    }
    else
    {
        if(dataLen > 2)
        {
            dataLen -= 2;
        }
        switch(dataType)
        {
        case PKT_TYPE_MSG:
            //            Serial << "T" << int(dataLen);
            storeData(buff, isEven, dStarMsg, posMSG);
            break;
        case PKT_TYPE_GPS:
            //            Serial << "A" << int(dataLen);
            storeData(buff, isEven, dStarGPS, posGPS);
            break;
        case PKT_TYPE_HEADER:
            //            Serial << "H" << int(dataLen);
            storeData(buff, isEven, dStarRFHeader, posRF);
            break;
        case PKT_TYPE_SQUELCH:
            //            Serial << "C" << int(dataLen);
            break;
        }
    }
    //    Serial << "  :" << hex << int(buff[0]) << " " << int(buff[1]) << " " << int(buff[2]) << endl;
    lineNr++;
}

void SlowAmbe::reset()
{
    memset(dStarMsg, 0x00, sizeof(dStarMsg));
    memset(dStarGPS, 0x00, sizeof(dStarGPS));
    memset(dStarRFHeader, 0x00, sizeof(dStarRFHeader));
    posMSG = 0;
    posGPS = 0;
    posRF = 0;
    lineNr = 0;
}

uint8_t* SlowAmbe::getDStarGPSData(uint16_t& size)
{
    size = posGPS;
    return dStarGPS;
}

uint8_t* SlowAmbe::getDStarMsg(uint16_t& size)
{
    size = sizeof(dStarMsg);
    return dStarMsg;
}

uint8_t* SlowAmbe::getDStarRFHeader(uint16_t& size)
{
    size = posRF;
    return dStarRFHeader;
}
