#pragma once

#include "../../L3_Messages/Types.hpp"
#include "../../L3_Messages/QueueProcessor.hpp"

class I2cOutputQueue;
class Lcd2004;
class Tm1637;
class IoPins;

class I2cOutputQueueReader : public QueueProcessor
{
public:
    I2cOutputQueueReader(
        I2cOutputQueue& i2cOutputQueue,  
        Lcd2004& lcd2004, 
        Tm1637& tm1637CentralPanel,
        Tm1637& tm1637Player1, 
        Tm1637& tm1637Player2, 
        IoPins& ioPins);
    ~I2cOutputQueueReader() = default;
    
    bool HandleMessage();

private:
    I2cOutputQueue& GetI2cOutputQueue();
    Tm1637& GetTm1637ById(
        Types::ETm1637Id tm1637Id);

    Lcd2004& _lcd2004;
    Tm1637& _tm1637CentralPanel;
    Tm1637& _tm1637Player1;
    Tm1637& _tm1637Player2;
    IoPins& _ioPins;
};
