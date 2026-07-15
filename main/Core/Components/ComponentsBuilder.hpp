#pragma once

class Rtos;
class RtosQueue;
class Random;

class LedStrips;
class LedStripModel;
class PinIo;

class LedStripDriver;
class I2c;
class Mcp23017;
class Lcd1602Display;
class Tm1637;

class ComponentsBuilder
{
public:
    ComponentsBuilder();
    ~ComponentsBuilder() = default;

    struct FraxisComponents
    {
        LedStrips* ledStrips;
        PinIo* pinIo;
    };

    struct Models // Generic but non Fraxis depending models 
    {
        LedStripModel* ledStripModel;
    };

    struct Drivers // Platform specific
    {
    public:
        //TODO: Check if Rtos and random should not be moved elsewhere, or this class should be renamed. ALso it's a combi between common and Fraxis 
        // specific classes.
        Rtos* rtos;
        RtosQueue* rtosQueue;
        Random* random;

        LedStripDriver* ledStripDriver;
        I2c* i2c;
        Mcp23017* mcp23017;
        Lcd1602Display* lcdDisplay;
        Tm1637* tm1637CentralPanel;
        Tm1637* tm1637Player1;
        Tm1637* tm1637Player2;
    };

    void Build();
    
    struct FraxisComponents& GetFraxisComponents() { return _fraxisComponents; };
    struct Models& GetModels() { return _models; };
    struct Drivers& GetDrivers() { return _drivers; };

private:
    void BuildFraxisComponents();
    void BuildModels();
    virtual void BuildDrivers() = 0;

    FraxisComponents _fraxisComponents;
    Models _models;

protected:
    Drivers _drivers;
};
