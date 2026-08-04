#include "Led.hpp"
#include "IoPins.hpp"
#include "../../../L0_System/DeviceSettings.hpp"
#include "../../../L3_Messages/Types.hpp"
#include "../../../L5_DeviceModels/Mcp23017/Mcp23017DeviceModel.hpp"
#include "../../../L9_Utilities/Assert/Assert.hpp"

Led::Led(
    IoPins& ioPins, 
    Types::ELedId ledId) 
:   _ioPins(ioPins),
    _ledId(ledId),
    _state(false)
{
}

void Led::SetState(bool state)
{
    using enum Types::ELedId;   // enables Player1, Player2, PlayPause, ...

    _state = state;
    uint8_t bit = 0;

    switch (_ledId)
    {
    case Player1:   bit = DeviceSettings::MCP23017_BIT_PLAYER_1_LED; break;
    case Player2:   bit = DeviceSettings::MCP23017_BIT_PLAYER_2_LED; break;
    case PlayPause: bit = DeviceSettings::MCP23017_BIT_PAUSE_LED;    break;
    case Select:    bit = DeviceSettings::MCP23017_BIT_SELECT_LED;   break;
    case Setup:     bit = DeviceSettings::MCP23017_BIT_SETUP_LED;    break;
    default:        Assert::Fail("Illegal case");
    }

    _ioPins.GetDeviceModel().SetOutputBit(bit, state);
}

bool Led::GetState() const
{
    return _state;
}
