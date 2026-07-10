#pragma once

#include <cstdint>

class Random
{
public:
    virtual uint32_t GetNext() = 0; 
    virtual uint8_t GetNext8() = 0;
    virtual uint16_t GetNext16() = 0;
    virtual uint32_t GetNext(uint32_t max) = 0;
    virtual uint32_t GetNextBetween(uint32_t min, uint32_t max) = 0;
};
