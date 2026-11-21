#include "../../M50_DeviceModels/Lcd2004/Lcd2004DeviceModel.hpp"
#include "../../M50_DeviceModels/Mcp23017/Mcp23017DeviceModel.hpp"
#include "../../M50_DeviceModels/Tm1637/Tm1637DeviceModel.hpp"
#include "../../M50_DeviceModels/Ws28xx/Ws28xxDeviceModel.hpp"
#include "../../M50_DeviceModels/MicroSdCard/MicroSdCardDeviceModel.hpp"
#include "../../M50_DeviceModels/I2s/I2sDeviceModel.hpp"
#include "../../M50_DeviceModels/I2s/Inmp1441/Inmp1441DeviceModel.hpp"
#include "../../M50_DeviceModels/I2s/Max53987a/Max53987aDeviceModel.hpp"
#include "../../M50_DeviceModels/PassiveBuzzer/PassiveBuzzerDeviceModel.hpp"
#include "DeviceModelsContext.hpp"

DeviceModelsContext::DeviceModelsContext()
:
    _lcd2004DeviceModel(nullptr),
    _mcp23017DeviceModel(nullptr),
    _tm1637DeviceModelCentralPanel(nullptr),
    _tm1637DeviceModelPlayer1(nullptr),
    _tm1637DeviceModelPlayer2(nullptr),
    _ws28xxDeviceModel(nullptr),
    _microSdCardDeviceModel(nullptr),
    _i2sDeviceModel(nullptr),
    _inmp1441DeviceModel(nullptr),
    _max53987aDeviceModel(nullptr),
    _passiveBuzzerDeviceModel(nullptr)
{
}

DeviceModelsContext::~DeviceModelsContext() // NOSONAR: No =default
{
    // No actions needed. Do not make = default.
}

void DeviceModelsContext::Set( // NOSONAR S107: >= 7 parameters
    std::unique_ptr<Lcd2004DeviceModel> lcd2004DeviceModel,
    std::unique_ptr<Mcp23017DeviceModel> mcp23017DeviceModel,
    std::unique_ptr<Tm1637DeviceModel> tm1637DeviceModelCentralPanel,
    std::unique_ptr<Tm1637DeviceModel> tm1637DeviceModelPlayer1,
    std::unique_ptr<Tm1637DeviceModel> tm1637DeviceModelPlayer2,
    std::unique_ptr<Ws28xxDeviceModel> ws28xxDeviceModel,
    std::unique_ptr<MicroSdCardDeviceModel> microSdCardDeviceModel,
    std::unique_ptr<I2sDeviceModel> i2sDeviceModel,
    std::unique_ptr<Inmp1441DeviceModel> inmp1441DeviceModel,
    std::unique_ptr<Max53987aDeviceModel> max53987aDeviceModel,
    std::unique_ptr<PassiveBuzzerDeviceModel> passiveBuzzerDeviceModel)
{
    _lcd2004DeviceModel = std::move(lcd2004DeviceModel);
    _mcp23017DeviceModel = std::move(mcp23017DeviceModel);
    _tm1637DeviceModelCentralPanel = std::move(tm1637DeviceModelCentralPanel);
    _tm1637DeviceModelPlayer1 = std::move(tm1637DeviceModelPlayer1);
    _tm1637DeviceModelPlayer2 = std::move(tm1637DeviceModelPlayer2);
    _ws28xxDeviceModel = std::move(ws28xxDeviceModel);
    _microSdCardDeviceModel = std::move(microSdCardDeviceModel);
    _i2sDeviceModel = std::move(i2sDeviceModel);
    _inmp1441DeviceModel = std::move(inmp1441DeviceModel);
    _max53987aDeviceModel = std::move(max53987aDeviceModel);
    _passiveBuzzerDeviceModel = std::move(passiveBuzzerDeviceModel);
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

MicroSdCardDeviceModel&  DeviceModelsContext::GetMicroSdCardDeviceModel()     
{
    return *_microSdCardDeviceModel; 
}

I2sDeviceModel& DeviceModelsContext::GetI2sDeviceModel()
{
    return *_i2sDeviceModel;
}

Inmp1441DeviceModel& DeviceModelsContext::GetInmp1441DeviceModel()
{
    return *_inmp1441DeviceModel;
}

Max53987aDeviceModel& DeviceModelsContext::GetMax53987aDeviceModel()
{
    return *_max53987aDeviceModel;
}

PassiveBuzzerDeviceModel& DeviceModelsContext::GetPassiveBuzzerDeviceModel()
{
    return *_passiveBuzzerDeviceModel;
}
