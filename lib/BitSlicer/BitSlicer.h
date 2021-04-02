#pragma once
#include <stdint.h>
using uint = unsigned int;

class BitSlicer
{
public:
    static constexpr uint HEADER_BITSIZE{660};
    static constexpr uint DATA_BITSIZE{96};//96bits == 12 bytes
    static constexpr uint DATA_FRAME_SIZE{DATA_BITSIZE / 8};
    static constexpr uint HEADER_SIZE{(HEADER_BITSIZE + 4) / 8 + 1}; //header 660 + 4 padding to full byte plus viterbi

    void reset();
    void setBuffer(uint8_t* headerBuff, uint headerBuffSize, uint8_t* dataBuff, uint dataBuffSize);
    bool appendBit(bool bit);
    bool haveHeader();
    uint16_t getDataFrameCount();

private:
    uint8_t receivedByte{0};

    uint8_t* m_headerBuff{nullptr};
    uint m_headerBuffSize{0};
    uint8_t* m_dataBuff{nullptr};
    uint m_dataBuffSize{0};

    uint receivedByteNr{0};
    uint8_t bitInHeader{7};
    uint16_t dataFrameCount{0};
    volatile uint totalReceivedBits{0};
};
