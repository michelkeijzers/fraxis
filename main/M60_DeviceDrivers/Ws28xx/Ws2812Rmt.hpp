#pragma once

#include "IWs2812Rmt.hpp"
#include <vector>

namespace M80::Rmt
{
    class IRmt;
}

namespace M90::Assert
{
    class IAssert;
}

namespace M60::Ws28xx
{
    class Ws2812Rmt : public IWs2812Rmt
    {
    public:
        Ws2812Rmt(
            M90::Assert::IAssert& assert,
            uint8_t pin,
            uint16_t led_count,
            M80::Rmt::IRmt& rmt);

        Ws2812Rmt(
            const Ws2812Rmt&) = default;
        
        Ws2812Rmt& operator=(
            const Ws2812Rmt&) = default;
        
        Ws2812Rmt(
            Ws2812Rmt&&) = default;
        
        Ws2812Rmt& operator=(
            Ws2812Rmt&&) = default;

        ~Ws2812Rmt();

        void Initialize() override;

        void Send(
            const uint8_t* grb_data) override;

    private:
        using rmt_symbol_word_t = struct {
            uint32_t duration0 : 15;
            uint32_t level0 : 1;
            uint32_t duration1 : 15;
            uint32_t level1 : 1;
        };

        M90::Assert::IAssert& _assert;

        uint8_t _pin;
        
        uint16_t _led_count;
        
        M80::Rmt::IRmt& _rmt;
        
        std::vector<rmt_symbol_word_t> _symbol_buffer;
    };
}
