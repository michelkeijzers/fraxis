#if !defined(_WIN32) && !defined(_WIN64)

#pragma once

#include "Random.hpp"

class EspRandom : public Random
{
public:
    ~EspRandom() = default;

    virtual uint32_t GetNext() override; 
    virtual uint8_t GetNext8() override;
    virtual uint16_t GetNext16() override;
    virtual uint32_t GetNext(uint32_t max) override;
    virtual uint32_t GetNextBetween(uint32_t min, uint32_t max) override;
};

#endif
