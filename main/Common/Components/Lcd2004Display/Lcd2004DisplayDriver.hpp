#pragma once

class Lcd1602DisplayModel;
class I2c;

class Lcd1602DisplayDriver
{
public:
	Lcd1602DisplayDriver(Lcd1602DisplayModel& model, I2c& i2c) : _model(model), _i2c(i2c) {};
	~Lcd1602DisplayDriver() = default;

	virtual void Initialize() = 0;

	virtual void Update() = 0;

protected:
	Lcd1602DisplayModel& _model;
	I2c& _i2c;
};

