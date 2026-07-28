#pragma once

#include <memory>

// Forward declarations of device models
class Ws28xxDeviceModel;
class Mcp23017DeviceModel;
class Lcd2004DeviceModel;
class Tm1637DeviceModel;

class DeviceModelsContext
{
public:
    DeviceModelsContext();
    ~DeviceModelsContext();

    void Set(
        std::unique_ptr<Ws28xxDeviceModel> ws28xxDeviceModel,
        std::unique_ptr<Mcp23017DeviceModel> mcp23017DeviceModel,
        std::unique_ptr<Lcd2004DeviceModel> lcd2004DeviceModel,
        std::unique_ptr<Tm1637DeviceModel> tm1637DeviceModelCentralPanel,
        std::unique_ptr<Tm1637DeviceModel> tm1637DeviceModelPlayer1,
        std::unique_ptr<Tm1637DeviceModel> tm1637DeviceModelPlayer2);

    Ws28xxDeviceModel& GetWs28xxDeviceModel()               { return *_ws28xxDeviceModel; }
    Mcp23017DeviceModel& GetMcp23017DeviceModel()             { return *_mcp23017DeviceModel; }
    Lcd2004DeviceModel& GetLcd2004DeviceModel()               { return *_lcd2004DeviceModel; }
    Tm1637DeviceModel& GetTm1637DeviceModelCentralPanel()     { return *_tm1637DeviceModelCentralPanel; }
    Tm1637DeviceModel& GetTm1637DeviceModelPlayer1()          { return *_tm1637DeviceModelPlayer1; }
    Tm1637DeviceModel& GetTm1637DeviceModelPlayer2()          { return *_tm1637DeviceModelPlayer2; }

private:
    std::unique_ptr<Ws28xxDeviceModel> _ws28xxDeviceModel;
    std::unique_ptr<Mcp23017DeviceModel> _mcp23017DeviceModel;
    std::unique_ptr<Lcd2004DeviceModel> _lcd2004DeviceModel;
    std::unique_ptr<Tm1637DeviceModel> _tm1637DeviceModelCentralPanel;
    std::unique_ptr<Tm1637DeviceModel> _tm1637DeviceModelPlayer1;
    std::unique_ptr<Tm1637DeviceModel> _tm1637DeviceModelPlayer2;
};
