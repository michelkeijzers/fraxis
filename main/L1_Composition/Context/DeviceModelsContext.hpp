#pragma once

#include <memory>

// Forward declarations of device models
class Ws28xxModel;
class Mcp23017Model;
class Lcd2004Model;
class Tm1637Model;

class DeviceModelsContext
{
public:
    DeviceModelsContext();
    ~DeviceModelsContext();

    void Set(
        std::unique_ptr<Ws28xxModel> ws28xxModel,
        std::unique_ptr<Mcp23017Model> mcp23017Model,
        std::unique_ptr<Lcd2004Model> lcd2004Model,
        std::unique_ptr<Tm1637Model> tm1637ModelCentralPanel,
        std::unique_ptr<Tm1637Model> tm1637ModelPlayer1,
        std::unique_ptr<Tm1637Model> tm1637ModelPlayer2);

    Ws28xxModel& GetLedStripModel()               { return *_ws28xxModel; }
    Mcp23017Model& GetMcp23017Model()             { return *_mcp23017Model; }
    Lcd2004Model& GetLcd2004Model()               { return *_lcd2004Model; }
    Tm1637Model& GetTm1637ModelCentralPanel()     { return *_tm1637ModelCentralPanel; }
    Tm1637Model& GetTm1637ModelPlayer1()          { return *_tm1637ModelPlayer1; }
    Tm1637Model& GetTm1637ModelPlayer2()          { return *_tm1637ModelPlayer2; }

private:
    std::unique_ptr<Ws28xxModel> _ws28xxModel;
    std::unique_ptr<Mcp23017Model> _mcp23017Model;
    std::unique_ptr<Lcd2004Model> _lcd2004Model;
    std::unique_ptr<Tm1637Model> _tm1637ModelCentralPanel;
    std::unique_ptr<Tm1637Model> _tm1637ModelPlayer1;
    std::unique_ptr<Tm1637Model> _tm1637ModelPlayer2;
};
