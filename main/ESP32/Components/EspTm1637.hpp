#include "../../Core/Components/Tm1637.hpp"
#include "driver/gpio.h"

class EspTm1637 : public Tm1637
{
public:
    EspTm1637(uint8_t nrOfDigits, gpio_num_t clkPin, gpio_num_t dioPin);
    ~EspTm1637() override;

    void Initialize() override;
    void Update() override;

    void Write() override;

private:
    gpio_num_t _clkPin;
    gpio_num_t _dioPin;

    void Start();
    void Stop();
    void WriteByte(uint8_t byte);
};