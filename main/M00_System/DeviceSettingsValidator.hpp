#pragma once 

#include "../M90_Utilities/Assert/Assert.hpp"

#ifdef ASSERTS_ENABLED

class DeviceSettingsValidator
{
public:
    static void Validate();

private:
    static void ValidatePins();
    static void ValidateI2c();
    static void ValidateMcp23017();
};

#endif // ASSERTS_ENABLED
