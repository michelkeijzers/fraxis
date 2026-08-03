#include "Led.hpp"
#include "IoPins.hpp"
#include "../../../L0_System/DeviceSettings.hpp"
#include "../../../L5_DeviceModels/Mcp23017/Mcp23017DeviceModel.hpp"
#include "../../../L9_Utilities/Assert/Assert.hpp"

Led::Led(
    IoPins& ioPins, 
    Types::ELedId ledId) 
:   _ioPins(ioPins),
    _ledId(ledId)
{
}

Led::~Led() 
{
}


void Led::SetState(bool state) 
{
    _state = state;
    uint8_t bit = 0;
    switch (_ledId)
    {
        case Types::ELedId::Player1: bit = DeviceSettings::MCP23017_BIT_PLAYER_1_LED; break;
        case Types::ELedId::Player2: bit = DeviceSettings::MCP23017_BIT_PLAYER_2_LED; break;
        case Types::ELedId::PlayPause: bit = DeviceSettings::MCP23017_BIT_PAUSE_LED; break;
        case Types::ELedId::Select: bit = DeviceSettings::MCP23017_BIT_SELECT_LED; break;
        case Types::ELedId::Setup: bit = DeviceSettings::MCP23017_BIT_SETUP_LED; break;
        default: Assert::Fail("Illegal case");
    }
    _ioPins.GetDeviceModel().SetOutputBit(bit, state);
}

bool Led::GetState() 
{
    return _state;
}
