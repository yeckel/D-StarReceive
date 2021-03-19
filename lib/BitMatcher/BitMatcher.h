#pragma once
#include <stdint.h>

class BitMatcher
{
public:
    BitMatcher(const uint8_t* data, unsigned int count);
    void reset();
    bool appendAndCheck(bool bit);
private:
    uint8_t* tailData;
    const uint8_t* endSyncData;
    unsigned int dataLength{0};
};
