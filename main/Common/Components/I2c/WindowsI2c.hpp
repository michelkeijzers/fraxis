#pragma once

#include "I2c.hpp"

class WindowsI2c : public I2c
{
public:
    WindowsI2c() {}
    
    void Initialize();

    void Write(uint8_t addr, const uint8_t* data, size_t len) override;
    void Read(uint8_t addr, uint8_t* data, size_t len) override;

    void ReadRegister(uint8_t devAddr, uint8_t regAddr, uint8_t* data, size_t len) override;
    void WriteRegister(uint8_t devAddr, uint8_t regAddr, const uint8_t* data, size_t len) override;
};
