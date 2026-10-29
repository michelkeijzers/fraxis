#pragma once

#include "ButtonState.hpp"
#include "JoystickState.hpp"
#include "../../M00_System/DeviceSettings.hpp"
#include "../../M30_Messages/Types.hpp"
#include <array>

class IoStates
{
public:
    IoStates() = default;

    IoStates(const IoStates&) = delete;
    IoStates& operator=(const IoStates&) = delete;
    IoStates(IoStates&&) = delete;
    IoStates& operator=(IoStates&&) = delete;

    ~IoStates() = default;

    JoystickState& GetJoystickState(
        Types::EJoystickId joystickId);
    ButtonState& GetSystemButtonState();

private:
    ButtonState _systemButtonState;
    std::array<JoystickState, DeviceSettings::MCP23017_NR_OF_JOYSTICKS> _joystickStates;
};
