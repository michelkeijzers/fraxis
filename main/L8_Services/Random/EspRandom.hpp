#ifdef ESP_PLATFORM

#pragma once

#include "Random.hpp"

class EspRandom : public Random
{
public:
    EspRandom();
    ~EspRandom();

private:
    uint32_t GetNext() override; 
    uint8_t GetNext8() override;
    uint16_t GetNext16() override;
    uint32_t GetNext(
        uint32_t max) override;
    uint32_t GetNextBetween(
        uint32_t min,
        uint32_t max) override;
};

#endif // ESP_PLATFORM
