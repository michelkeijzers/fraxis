#include "Tm1637.hpp"
#include "../../../../L5_DeviceModels/Tm1637/Tm1637DeviceModel.hpp"
#include "../../../../L9_Utilities/Log/Log.hpp"

Tm1637::Tm1637()
: _format(Tm1637::EFormat::Value), _value(0), _first(0), _second(0), _tm1637DeviceModel(nullptr)
{
}

Tm1637::~Tm1637()
{
}

Tm1637DeviceModel& Tm1637::GetTm1637DeviceModel()
{
    return *_tm1637DeviceModel;
}

void Tm1637::SetDeviceModel(IDeviceModel& deviceModel)
{
    _tm1637DeviceModel = static_cast<Tm1637DeviceModel*>(&deviceModel);
}

/// @brief Sets a value with format 12345678 where indices are: 7,6,5,4,3,2,1,0
/// @param value 
void Tm1637::SetValue(uint32_t value)
{
    _format = EFormat::Value;
    _value = value;
    auto& tm1637DeviceModel = GetTm1637DeviceModel();

    uint8_t numberOfDigits = tm1637DeviceModel.GetNrOfDigits();
    for (int index = 0; index < numberOfDigits; index++)
    {
        if ((value == 0) && (index != 0))
        {
            tm1637DeviceModel.SetCharacter(index, ' ');
        }
        else
        {
            tm1637DeviceModel.SetAuxiliarySegment(index, false);   
            tm1637DeviceModel.SetDigit(index, value % 10);
            value /= 10;
        }
    }
}

/// @brief Sets time
/// @details Format:
/// Index:    765432 10
/// Example:  ____12:34 Note that the colon is always at index 2
/// @param first 
/// @param second 
void Tm1637::SetTime(uint8_t first, uint8_t second)
{
    Log::Int("L4 Tm1637::SetTime, first", first);
    Log::Int("L4 Tm1637::SetTime, second", second);
    _format = EFormat::Time;
    _first = first;
    _second = second;
    auto & tm1637DeviceModel = GetTm1637DeviceModel();

    for (uint8_t index = 0; index < 4; index++)
    {
        tm1637DeviceModel.SetAuxiliarySegment(index, index == 2);
        tm1637DeviceModel.SetCharacter(index, ' ');
    }
    
    if (first >= 10)
    {
        tm1637DeviceModel.SetDigit(3, first / 10);
    }
    tm1637DeviceModel.SetDigit(2, first % 10);
    tm1637DeviceModel.SetDigit(1, second / 10);
    tm1637DeviceModel.SetDigit(0, second % 10); 
}
