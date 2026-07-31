#pragma once

#include "I2c.hpp"

class WindowsI2c : public I2c
{
public:
    WindowsI2c();
    ~WindowsI2c();
};
