#pragma once 

#include "../M90_Utilities/Assert/Assert.hpp"

#ifdef ASSERTS_ENABLED

namespace M90::Assert
{
    class IAssert;
} 

class DeviceSettingsValidator
{
public:
    DeviceSettingsValidator(
        M90::Assert::IAssert& assert);

    // TODO: copy/move constructors

    ~DeviceSettingsValidator() = default;

    void Validate();

private:
    void ValidatePins();
    
    void ValidateI2c();
    
    void ValidateMcp23017();

    M90::Assert::IAssert &_assert;
};

#endif // ASSERTS_ENABLED
