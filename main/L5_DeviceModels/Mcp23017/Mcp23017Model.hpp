#pragma once

class I2cModel;

class Mcp23017Model
{
public:
    Mcp23017Model();
    ~Mcp23017Model();

    void SetI2cModel(I2cModel& i2cModel);

private:
    I2cModel* _i2cModel;
};
