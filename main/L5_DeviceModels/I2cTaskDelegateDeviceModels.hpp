#pragma once

class Context;

class I2cTaskDelegateDeviceModels
{
public:
    I2cTaskDelegateDeviceModels(Context& context);
    ~I2cTaskDelegateDeviceModels();

    void Run();

private:
    Context& _context;
};
