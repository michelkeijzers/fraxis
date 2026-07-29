#pragma once

#include <memory>
#include "../../L6_DeviceDrivers/I2c/I2cDeviceDriver.hpp"
#include "../../L6_DeviceDrivers/Lcd2004/Lcd2004DeviceDriver.hpp"
#include "../../L6_DeviceDrivers/Mcp23017/Mcp23017DeviceDriver.hpp"
#include "../../L6_DeviceDrivers/Tm1637/Tm1637DeviceDriver.hpp"
#include "../../L6_DeviceDrivers/Ws28xx/Ws28xxDeviceDriver.hpp"

class DeviceDriversContext
{
public:
    DeviceDriversContext();
    ~DeviceDriversContext();

    void Set(
        std::unique_ptr<I2cDeviceDriver> i2cDeviceDriver,
        std::unique_ptr<Lcd2004DeviceDriver> lcd2004DeviceDriver,
        std::unique_ptr<Mcp23017DeviceDriver> mcpDeviceDriver,
        std::unique_ptr<Tm1637DeviceDriver> tm1637DeviceDriverCentralPanel,
        std::unique_ptr<Tm1637DeviceDriver> tm1637DeviceDriverPlayer1,
        std::unique_ptr<Tm1637DeviceDriver> tm1637DeviceDriverPlayer2,
        std::unique_ptr<Ws28xxDeviceDriver> ws28xxDeviceDriver
    );

    I2cDeviceDriver& GetI2cDeviceDriver() { return *_i2cDeviceDriver; }
    Lcd2004DeviceDriver& GetLcd2004DeviceDriver() { return *_lcd2004DeviceDriver; }
    Mcp23017DeviceDriver& GetMcp23017DeviceDriver() { return *_mcp23017DeviceDriver; }
    Tm1637DeviceDriver& GetTm1637DeviceDriverCentralPanel() { return *_tm1637DeviceDriverCentralPanel; }
    Tm1637DeviceDriver& GetTm1637DeviceDriverPlayer1() { return *_tm1637DeviceDriverPlayer1; }
    Tm1637DeviceDriver& GetTm1637DeviceDriverPlayer2() { return *_tm1637DeviceDriverPlayer2; }
    Ws28xxDeviceDriver& GetWs28xxDeviceDriver() { return *_ws28xxDeviceDriver;  }

private:
    std::unique_ptr<I2cDeviceDriver> _i2cDeviceDriver;
    std::unique_ptr<Lcd2004DeviceDriver> _lcd2004DeviceDriver;
    std::unique_ptr<Mcp23017DeviceDriver> _mcp23017DeviceDriver;
    std::unique_ptr<Tm1637DeviceDriver> _tm1637DeviceDriverCentralPanel;    
    std::unique_ptr<Tm1637DeviceDriver> _tm1637DeviceDriverPlayer1;
    std::unique_ptr<Tm1637DeviceDriver> _tm1637DeviceDriverPlayer2;
    std::unique_ptr<Ws28xxDeviceDriver> _ws28xxDeviceDriver;
};
