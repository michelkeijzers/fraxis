#include "Tm1637DeviceDriver.hpp"
#include "driver/gpio.h"

class Tm1637DeviceModel;

class EspTm1637DeviceDriver : public Tm1637DeviceDriver
{
public:
    EspTm1637DeviceDriver(Tm1637DeviceModel& model, gpio_num_t clkPin, gpio_num_t dioPin);
    ~EspTm1637DeviceDriver() = default;

    void Initialize() override;
    void Write() override;

private:
    gpio_num_t _clkPin;
    gpio_num_t _dioPin;

    void Start();
    void Stop();
    void WriteByte(uint8_t byte);
};