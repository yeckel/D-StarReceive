#pragma once
#include <stdint.h>
using uint = unsigned int;

bool isSyncFrame(uint8_t* buff);
void scramble(uint8_t* buff, uint size);
