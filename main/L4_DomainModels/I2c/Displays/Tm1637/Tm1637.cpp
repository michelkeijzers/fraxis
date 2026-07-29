#include "Tm1637.hpp"
#include "../../../../L5_DeviceModels/Tm1637/Tm1637DeviceModel.hpp"

Tm1637::Tm1637()
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
    for (int index = 7; index >= (8 - numberOfDigits); index--)
    {
        if ((value == 0) && (index != 7))
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

/// @brief Sets time with format: ____12:34 where indices are: 7,6,5,4,3,2,1,0, auxiliary segment only at 2 (:)
/// @param first 
/// @param second 
void Tm1637::SetTime(uint8_t first, uint8_t second)
{
    _format = EFormat::Time;
    _first = first;
    _second = second;
    auto & tm1637DeviceModel = GetTm1637DeviceModel();

    for (uint8_t index = 7; index >= 4; index--)
    {
        tm1637DeviceModel.SetAuxiliarySegment(index, false);
        tm1637DeviceModel.SetCharacter(index, ' ');
    }
    
    tm1637DeviceModel.SetAuxiliarySegment(3, false);
    if (first < 10)
    {
        tm1637DeviceModel.SetCharacter(3, ' ');
    }
    else
    {
        tm1637DeviceModel.SetDigit(3, first / 10);
    }
    
    tm1637DeviceModel.SetDigit(2, first % 10);
    tm1637DeviceModel.SetAuxiliarySegment(2, true);

    tm1637DeviceModel.SetDigit(1, second / 10);
    tm1637DeviceModel.SetAuxiliarySegment(1, false);

    tm1637DeviceModel.SetDigit(0, second % 10); 
    tm1637DeviceModel.SetAuxiliarySegment(0, false);
}
