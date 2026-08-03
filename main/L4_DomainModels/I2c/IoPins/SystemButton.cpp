#include "SystemButton.hpp"
#include "../IoPins/IoPins.hpp"
#include "../../../L0_System/DeviceSettings.hpp"
#include "../../../L5_DeviceModels/Mcp23017/Mcp23017DeviceModel.hpp"

SystemButton::SystemButton(
    IoPins& ioPins) 
:   _ioPins(ioPins), 
    _state(false)
{
}

SystemButton::~SystemButton() 
{
}

/// @brief Updates the state of the system button, called after an MCP23017 interrupt by the I2c task delegate.
/// @details The state is reversed because a button has default active low.
void SystemButton::UpdateInput()
{
    bool newState = !(_ioPins.GetDeviceModel().GetInputBit(DeviceSettings::MCP23017_BIT_SYSTEM_BUTTON));
    if (newState != _state)
    {
        _state = newState;
        _dirty.MarkDirty();
    }
}

bool SystemButton::GetState() 
{
    return _state;
}

Dirty& SystemButton::GetStateDirty() 
{
    return _dirty;
}
