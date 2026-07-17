#include "Tm1637Driver.hpp"
#include "driver/gpio.h"

class Tm1637Model;

class EspTm1637Driver : public Tm1637Driver
{
public:
    EspTm1637Driver(Tm1637Model& model, gpio_num_t clkPin, gpio_num_t dioPin);
    ~EspTm1637Driver() = default;

    void Initialize() override;
    void Write() override;

private:
    gpio_num_t _clkPin;
    gpio_num_t _dioPin;

    void Start();
    void Stop();
    void WriteByte(uint8_t byte);
};