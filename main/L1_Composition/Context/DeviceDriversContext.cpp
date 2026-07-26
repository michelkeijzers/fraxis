#include "DeviceDriversContext.hpp"
#include <memory>

DeviceDriversContext::DeviceDriversContext() = default;

DeviceDriversContext::~DeviceDriversContext() = default;

void DeviceDriversContext::Set(
    std::unique_ptr<Ws28xxDeviceDriver> ws28xxDeviceDriver,
    std::unique_ptr<I2cDeviceDriver> i2cDeviceDriver,
    std::unique_ptr<Mcp23017DeviceDriver> mcp23017DeviceDriver,
    std::unique_ptr<Lcd2004DeviceDriver> lcd2004DeviceDriver,
    std::unique_ptr<Tm1637DeviceDriver> tm1637DeviceDriverCentralPanel,
    std::unique_ptr<Tm1637DeviceDriver> tm1637DeviceDriverPlayer1,
    std::unique_ptr<Tm1637DeviceDriver> tm1637DeviceDriverPlayer2)
{
    _ws28xxDeviceDriver = std::move(ws28xxDeviceDriver);
    _i2cDeviceDriver = std::move(i2cDeviceDriver);
    _mcp23017DeviceDriver = std::move(mcp23017DeviceDriver);
    _lcd2004DeviceDriver = std::move(lcd2004DeviceDriver);
    _tm1637DeviceDriverCentralPanel = std::move(tm1637DeviceDriverCentralPanel);
    _tm1637DeviceDriverPlayer1 = std::move(tm1637DeviceDriverPlayer1);
    _tm1637DeviceDriverPlayer2 = std::move(tm1637DeviceDriverPlayer2);
}
