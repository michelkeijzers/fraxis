#pragma once

#include "ITm1637DeviceDriver.hpp"
#include "../DeviceDriver.hpp"

namespace M60::SevenSegmentsDisplays
{
    class Tm1637DeviceDriver : public DeviceDriver, public ITm1637DeviceDriver
    {
    public:
        // Do not make =default in .hpp file because of unique_ptr needing complete (sub) types.
        Tm1637DeviceDriver(
            M90::Assert::IAssert& assert,
            M90::String::IStringUtilities& stringUtilities);

        Tm1637DeviceDriver(
            const Tm1637DeviceDriver&) = delete;
        
        Tm1637DeviceDriver& operator=(
            const Tm1637DeviceDriver&) = delete;
        
        Tm1637DeviceDriver(
            Tm1637DeviceDriver&&) = delete;
        
        Tm1637DeviceDriver& operator=(
            Tm1637DeviceDriver&&) = delete;

        // Do not make =default in .hpp file because of unique_ptr needing complete (sub) types.
        ~Tm1637DeviceDriver() override;

        void SetGpio(
            M80::Gpio::IGpio& gpio) override;
        
        void SetPinsConfiguration(
            uint8_t clockPin, 
            uint8_t dataPin) override;
        
        void Initialize() override;

        void SendToDisplay() override;

    private:
        M80::Gpio::IGpio& GetGpio();

        void Start();
        
        void WriteByte(uint8_t byte);
        
        void Stop();

        uint8_t _clockPin;
        
        uint8_t _dataPin;

        M80::Gpio::IGpio* _gpio;
    };
}
