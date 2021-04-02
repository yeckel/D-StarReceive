#pragma once
#include <stdint.h>
using uint = unsigned int;
class SlowAmbe
{
public:
    static constexpr uint8_t DSTAR_MSG_SIZE{20};//Icom message on the display rotating
    static constexpr uint8_t DSTAR_GPS_MAX_SIZE{100}; //my guess from an example: "$$CRCB3BF,OK1CHP-1>API705,DSTAR*:!4946.70N/01329.42E-/A=001240Playing with ic-705"
    static constexpr uint8_t DSTAR_RF_SIZE{42};
    SlowAmbe();;
    /**
    * @brief receiveData
    * @param buff - three bytes of DV slow data
    */
    void receiveData(uint8_t* buff);
    void reset();
    uint8_t* getDStarGPSData(uint16_t& size);
    uint8_t* getDStarMsg(uint16_t& size);//always 20
    uint8_t* getDStarRFHeader(uint16_t& size);
private:
    uint8_t dStarMsg[DSTAR_MSG_SIZE];
    uint8_t dStarGPS[DSTAR_GPS_MAX_SIZE];
    uint8_t dStarRFHeader[DSTAR_RF_SIZE];
    uint posMSG{0}, posGPS{0}, posRF{0};
    uint lineNr{0};
    uint8_t dataLen{0};
    uint8_t dataType{0};
    void storeData(uint8_t* buff, bool isFirst, uint8_t* dest, uint& pos);
};
