#pragma once

#include <memory>
#include "../../L6_DeviceDrivers/Ws28xx/Ws28xxDriver.hpp"
#include "../../L6_DeviceDrivers/I2c/I2cDriver.hpp"
#include "../../L6_DeviceDrivers/Mcp23017/Mcp23017Driver.hpp"
#include "../../L6_DeviceDrivers/Lcd2004/Lcd2004Driver.hpp"
#include "../../L6_DeviceDrivers/Tm1637/Tm1637Driver.hpp"

class DeviceDriversContext
{
public:
    DeviceDriversContext();
    ~DeviceDriversContext();

    void Set(
        std::unique_ptr<Ws28xxDriver> ws28xxDriver,
        std::unique_ptr<I2cDriver> i2cDriver,
        std::unique_ptr<Mcp23017Driver> mcpDriver,
        std::unique_ptr<Lcd2004Driver> lcd2004Driver,
        std::unique_ptr<Tm1637Driver> tm1637DriverCentralPanel,
        std::unique_ptr<Tm1637Driver> tm1637DriverPlayer1,
        std::unique_ptr<Tm1637Driver> tm1637DriverPlayer2);

    Ws28xxDriver& GetWs28xxDriver() { return *_ws28xxDriver;  }
    I2cDriver& GetI2cDriver() { return *_i2cDriver; }
    Mcp23017Driver& GetMcp23017Driver() { return *_mcp23017Driver; }
    Lcd2004Driver& GetLcd2004Driver() { return *_lcd2004Driver; }
    Tm1637Driver& GetTm1637CentralPanel() { return *_tm1637DriverCentralPanel; }
    Tm1637Driver& GetTm1637Player1() { return *_tm1637DriverPlayer1; }
    Tm1637Driver& GetTm1637Player2() { return *_tm1637DriverPlayer2; }

private:
    std::unique_ptr<Ws28xxDriver> _ws28xxDriver;
    std::unique_ptr<I2cDriver> _i2cDriver;
    std::unique_ptr<Mcp23017Driver> _mcp23017Driver;
    std::unique_ptr<Lcd2004Driver> _lcd2004Driver;
    std::unique_ptr<Tm1637Driver> _tm1637DriverCentralPanel;    
    std::unique_ptr<Tm1637Driver> _tm1637DriverPlayer1;
    std::unique_ptr<Tm1637Driver> _tm1637DriverPlayer2;
};
