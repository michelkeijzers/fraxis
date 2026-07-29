#include "Tm1637.hpp"
#include "../../../../L5_DeviceModels/Tm1637/Tm1637DeviceModel.hpp"

Tm1637::Tm1637()
{
}

void Tm1637::SetDeviceModel(IDeviceModel& deviceModel)
{
    _tm1637DeviceModel = static_cast<Tm1637DeviceModel*>(&deviceModel);
}

void Tm1637::SetValue(uint32_t value)
{
    _format = EFormat::Value;
    _value = value;

    uint8_t numberOfDigits = _tm1637DeviceModel->GetNrOfDigits();
    for (int index = 7; index >= (8 - numberOfDigits); index--)
    {
        if ((value == 0) && (index != 7))
        {
            _tm1637DeviceModel->SetCharacter(index, ' ');
        }
        else
        {
            _tm1637DeviceModel->SetAuxiliarySegment(index, false);   
            _tm1637DeviceModel->SetDigit(index, value % 10);
            value /= 10;
        }
    }
}

void Tm1637::SetTime(uint8_t first, uint8_t second)
{
    _format = EFormat::Time;
    _first = first;
    _second = second;
    //_tm1637DeviceModel->SetTime(first, second);
}
