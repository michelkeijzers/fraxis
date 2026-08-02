#include "../../L5_DeviceModels/Lcd2004/Lcd2004DeviceModel.hpp"
#include "../../L5_DeviceModels/Mcp23017/Mcp23017DeviceModel.hpp"
#include "../../L5_DeviceModels/Tm1637/Tm1637DeviceModel.hpp"
#include "../../L5_DeviceModels/Ws28xx/Ws28xxDeviceModel.hpp"
#include "DeviceModelsContext.hpp"

DeviceModelsContext::DeviceModelsContext() 
{
}

DeviceModelsContext::~DeviceModelsContext()
{
}

void DeviceModelsContext::Set(
    std::unique_ptr<Lcd2004DeviceModel> lcd2004DeviceModel,
    std::unique_ptr<Mcp23017DeviceModel> mcp23017DeviceModel,
    std::unique_ptr<Tm1637DeviceModel> tm1637DeviceModelCentralPanel,
    std::unique_ptr<Tm1637DeviceModel> tm1637DeviceModelPlayer1,
    std::unique_ptr<Tm1637DeviceModel> tm1637DeviceModelPlayer2,
    std::unique_ptr<Ws28xxDeviceModel> ws28xxDeviceModel
)
{
    _lcd2004DeviceModel = std::move(lcd2004DeviceModel);
    _mcp23017DeviceModel = std::move(mcp23017DeviceModel);
    _tm1637DeviceModelCentralPanel = std::move(tm1637DeviceModelCentralPanel);
    _tm1637DeviceModelPlayer1 = std::move(tm1637DeviceModelPlayer1);
    _tm1637DeviceModelPlayer2 = std::move(tm1637DeviceModelPlayer2);
    _ws28xxDeviceModel = std::move(ws28xxDeviceModel);
}

Lcd2004DeviceModel& DeviceModelsContext::GetLcd2004DeviceModel()              
{
    return *_lcd2004DeviceModel; 
}

Mcp23017DeviceModel&  DeviceModelsContext::GetMcp23017DeviceModel()             
{
    return *_mcp23017DeviceModel; 
}

Tm1637DeviceModel&  DeviceModelsContext::GetTm1637DeviceModelCentralPanel()    
{
    return *_tm1637DeviceModelCentralPanel; 
}

Tm1637DeviceModel&  DeviceModelsContext::GetTm1637DeviceModelPlayer1()          
{
    return *_tm1637DeviceModelPlayer1;
}

Tm1637DeviceModel&  DeviceModelsContext::GetTm1637DeviceModelPlayer2()          
{
    return *_tm1637DeviceModelPlayer2; 
}

Ws28xxDeviceModel&  DeviceModelsContext::GetWs28xxDeviceModel()               
{
    return *_ws28xxDeviceModel; 
}
