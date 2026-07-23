#include "DeviceDriversContext.hpp"
#include <memory>

DeviceDriversContext::DeviceDriversContext() = default;

DeviceDriversContext::~DeviceDriversContext() = default;

void DeviceDriversContext::Set(
    std::unique_ptr<Ws28xxDriver> ws28xxDriver,
    std::unique_ptr<I2cDriver> i2cDriver,
    std::unique_ptr<Mcp23017Driver> mcpDriver,
    std::unique_ptr<Lcd2004Driver> lcd2004Driver,
    std::unique_ptr<Tm1637Driver> tm1637DriverCentralPanel,
    std::unique_ptr<Tm1637Driver> tm1637DriverPlayer1,
    std::unique_ptr<Tm1637Driver> tm1637DriverPlayer2)
{
    _ws28xxDriver = std::move(ws28xxDriver);
    _i2cDriver = std::move(i2cDriver);
    _mcp23017Driver = std::move(mcpDriver);
    _lcd2004Driver = std::move(lcd2004Driver);
    _tm1637DriverCentralPanel = std::move(tm1637DriverCentralPanel);
    _tm1637DriverPlayer1 = std::move(tm1637DriverPlayer1);
    _tm1637DriverPlayer2 = std::move(tm1637DriverPlayer2);
}
