#pragma once

#include <cstdint>
#include <stddef.h>
//#include "../../Common/Components/I2c//I2c.hpp"

class I2c 
{
public:
    I2c() {};
    
    virtual void Initialize() = 0;

    virtual void Write(uint8_t addr, const uint8_t* data, size_t len) = 0;
    virtual void Read(uint8_t addr, uint8_t* data, size_t len) = 0;

    virtual void ReadRegister(uint8_t devAddr, uint8_t regAddr, uint8_t* data, size_t len) = 0;
    virtual void WriteRegister(uint8_t devAddr, uint8_t regAddr, const uint8_t* data, size_t len) = 0;
};
