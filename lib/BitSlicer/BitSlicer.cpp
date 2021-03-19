#include "BitSlicer.h"

void BitSlicer::appendBit(bool bit)
{
    byte += bit;
    bits++;
    if(bits == 8)
    {
        Serial << "0x" << _HEX(byte) << ",";
        bits = 0;
        byte = 0;
    }
    byte = byte << 1;
}

void BitSlicer::reset()
{
    byte = 0;
    bits = 0;
}
