#pragma once

#include <stdint.h>
#include "Random.hpp"
#include <random>

class WindowsRandom : public Random
{
public:
    WindowsRandom();

    uint32_t GetNext() override;
    uint8_t  GetNext8() override;
    uint16_t GetNext16() override;
    uint32_t GetNext(uint32_t max) override;
    uint32_t GetNextBetween(uint32_t min, uint32_t max) override;

private:
    std::mt19937 _gen;
};
