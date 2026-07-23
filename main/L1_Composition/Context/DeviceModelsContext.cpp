#include "../../L5_DeviceModels/Ws28xx/Ws28xxModel.hpp"
#include "../../L5_DeviceModels/Mcp23017/Mcp23017Model.hpp"
#include "../../L5_DeviceModels/Lcd2004/Lcd2004Model.hpp"
#include "../../L5_DeviceModels/Tm1637/Tm1637Model.hpp"

#include "DeviceModelsContext.hpp"

DeviceModelsContext::DeviceModelsContext() = default;

DeviceModelsContext::~DeviceModelsContext() = default;

void DeviceModelsContext::Set(
    std::unique_ptr<Ws28xxModel> ws28xxModel,
    std::unique_ptr<Mcp23017Model> mcp23017Model,
    std::unique_ptr<Lcd2004Model> lcd2004Model,
    std::unique_ptr<Tm1637Model> tm1637ModelCentralPanel,
    std::unique_ptr<Tm1637Model> tm1637ModelPlayer1,
    std::unique_ptr<Tm1637Model> tm1637ModelPlayer2)
{
    _ws28xxModel = std::move(ws28xxModel);
    _mcp23017Model = std::move(mcp23017Model);
    _lcd2004Model = std::move(lcd2004Model);
    _tm1637ModelCentralPanel = std::move(tm1637ModelCentralPanel);
    _tm1637ModelPlayer1 = std::move(tm1637ModelPlayer1);
    _tm1637ModelPlayer2 = std::move(tm1637ModelPlayer2);
}
