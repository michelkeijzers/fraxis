#include "../../L5_DeviceModels/Lcd2004/Lcd2004DeviceModel.hpp"
#include "../../L5_DeviceModels/Mcp23017/Mcp23017DeviceModel.hpp"
#include "../../L5_DeviceModels/Tm1637/Tm1637DeviceModel.hpp"
#include "../../L5_DeviceModels/Ws28xx/Ws28xxDeviceModel.hpp"

#include "DeviceModelsContext.hpp"

DeviceModelsContext::DeviceModelsContext() = default;

DeviceModelsContext::~DeviceModelsContext() = default;

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
