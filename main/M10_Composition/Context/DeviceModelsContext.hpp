#pragma once

#include <memory>

// Forward declarations of device models
class Lcd2004DeviceModel;
class Mcp23017DeviceModel;
class Tm1637DeviceModel;
class Ws28xxDeviceModel;

class DeviceModelsContext
{
public:
    DeviceModelsContext();
    ~DeviceModelsContext();

    void Set(
        std::unique_ptr<Lcd2004DeviceModel> lcd2004DeviceModel,
        std::unique_ptr<Mcp23017DeviceModel> mcp23017DeviceModel,
        std::unique_ptr<Tm1637DeviceModel> tm1637DeviceModelCentralPanel,
        std::unique_ptr<Tm1637DeviceModel> tm1637DeviceModelPlayer1,
        std::unique_ptr<Tm1637DeviceModel> tm1637DeviceModelPlayer2,
        std::unique_ptr<Ws28xxDeviceModel> ws28xxDeviceModel
    );

    Lcd2004DeviceModel& GetLcd2004DeviceModel();
    Mcp23017DeviceModel& GetMcp23017DeviceModel();
    Tm1637DeviceModel& GetTm1637DeviceModelCentralPanel();
    Tm1637DeviceModel& GetTm1637DeviceModelPlayer1();
    Tm1637DeviceModel& GetTm1637DeviceModelPlayer2();
    Ws28xxDeviceModel& GetWs28xxDeviceModel();

private:
    std::unique_ptr<Lcd2004DeviceModel> _lcd2004DeviceModel;
    std::unique_ptr<Mcp23017DeviceModel> _mcp23017DeviceModel;
    std::unique_ptr<Tm1637DeviceModel> _tm1637DeviceModelCentralPanel;
    std::unique_ptr<Tm1637DeviceModel> _tm1637DeviceModelPlayer1;
    std::unique_ptr<Tm1637DeviceModel> _tm1637DeviceModelPlayer2;
    std::unique_ptr<Ws28xxDeviceModel> _ws28xxDeviceModel;
};
