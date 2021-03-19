#pragma once
#include <stdint.h>
#include "Streaming.h"

class BitSlicer
{
public:
    void reset();
    void appendBit(bool bit);
private:
    uint8_t byte{0};
    uint8_t bits{0};
};
