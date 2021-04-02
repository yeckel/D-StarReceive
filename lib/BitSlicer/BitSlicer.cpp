#include "BitSlicer.h"
#include <string.h>

bool BitSlicer::appendBit(bool bit)
{
    if(totalReceivedBits > m_headerBuffSize * 8 + m_dataBuffSize * 8)
    {
        return false;
    }
    totalReceivedBits++;
    //set bit
    receivedByte = (receivedByte & ~(1UL << bitInHeader)) | (bit << bitInHeader);

    if(bitInHeader == 0 || totalReceivedBits == HEADER_BITSIZE)
    {
        bitInHeader = 7;
        if(totalReceivedBits <= HEADER_BITSIZE)
        {
            m_headerBuff[receivedByteNr] = receivedByte;
            if(totalReceivedBits == HEADER_BITSIZE)
            {
                m_headerBuff[receivedByteNr] &= 0xF0;
                receivedByteNr = 0;//switching to m_dataBuff with the next bit
                return true;
            }
        }
        else
        {
            m_dataBuff[receivedByteNr] = receivedByte;
        }
        receivedByteNr += 1;
    }
    else
    {
        bitInHeader--;
    }
    return true;
}

void BitSlicer::reset()
{
    dataFrameCount = 0;
    bitInHeader = 0;
    receivedByteNr = 0;
    totalReceivedBits = 0;
}

void BitSlicer::setBuffer(uint8_t* headerBuff, uint headerBuffSize, uint8_t* dataBuff, uint dataBuffSize)
{
    m_headerBuff = headerBuff;
    m_headerBuffSize = headerBuffSize;
    m_dataBuff = dataBuff;
    m_dataBuffSize = dataBuffSize;
}

bool BitSlicer::haveHeader()
{
    return totalReceivedBits >= HEADER_BITSIZE;
}

uint16_t BitSlicer::getDataFrameCount()
{
    return totalReceivedBits > HEADER_SIZE ? (totalReceivedBits - HEADER_BITSIZE) / DATA_BITSIZE : 0;
}
