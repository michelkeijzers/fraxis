#include "Lcd2004Model.hpp"
#include "../DeviceSettings.hpp"

Lcd2004Model::Lcd2004Model()
{
}

Lcd2004Model::~Lcd2004Model()
{
}

void Lcd2004Model::SetI2cModel(I2cModel& i2cModel)
{
    _i2cModel = &i2cModel;
}

void Lcd2004Model::Initialize()
{
    _i2cAddress = DeviceSettings::I2C_ADDRESS_LCD2004;
}

void Lcd2004Model::WriteLine(uint8_t line, std::string lineContent)
{
    _lines[line] = lineContent;
}
