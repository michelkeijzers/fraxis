#pragma once

class Context;

class I2cTaskDeviceDriversDelegate
{
public:
    I2cTaskDeviceDriversDelegate(Context& context);
    ~I2cTaskDeviceDriversDelegate();

    void Run();

private:
    Context& _context;
};
