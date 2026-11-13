// @file Ws2812RmtTests.cpp
// Copyright (c) 2026 Michel Keijzers
// SPDX-License-Identifier: GPL-3.0-only

#include "gtest/gtest.h"
#include "../../../../main/M60_DeviceDrivers/Ws28xx/Ws2812Rmt.hpp"
#include "../../../../main/M80_Services/Rmt/Rmt.hpp"

namespace M60::Ws28xxTests
{
    class MockRmt : public M80::Rmt::Rmt
    {
    public:
        MockRmt() = default;

        esp_err_t NewTxChannel(uint8_t gpio_num) override
        {
            NewTxChannelCallCount++;
            LastPin = gpio_num;
            return NewTxChannelResult;
        }

        esp_err_t Enable() override
        {
            EnableCallCount++;
            return EnableResult;
        }

        esp_err_t NewSimpleEncoder() override
        {
            NewSimpleEncoderCallCount++;
            return NewSimpleEncoderResult;
        }

        esp_err_t DelEncoder() override
        {
            DelEncoderCallCount++;
            return DelEncoderResult;
        }

        esp_err_t DelChannel() override
        {
            DelChannelCallCount++;
            return DelChannelResult;
        }

        esp_err_t Transmit(const void* symbol_buffer, size_t buffer_size) override
        {
            TransmitCallCount++;
            LastBufferSize = buffer_size;
            if (symbol_buffer && buffer_size > 0)
            {
                // Optionally copy or inspect transmitted symbols if needed
            }
            return TransmitResult;
        }

        esp_err_t TxWaitAllDone() override
        {
            TxWaitAllDoneCallCount++;
            return TxWaitAllDoneResult;
        }

    public:
        size_t NewTxChannelCallCount = 0;
        size_t EnableCallCount = 0;
        size_t NewSimpleEncoderCallCount = 0;
        size_t DelEncoderCallCount = 0;
        size_t DelChannelCallCount = 0;
        size_t TransmitCallCount = 0;
        size_t TxWaitAllDoneCallCount = 0;

        uint8_t LastPin = 0;
        size_t LastBufferSize = 0;

        esp_err_t NewTxChannelResult = ESP_OK;
        esp_err_t EnableResult = ESP_OK;
        esp_err_t NewSimpleEncoderResult = ESP_OK;
        esp_err_t DelEncoderResult = ESP_OK;
        esp_err_t DelChannelResult = ESP_OK;
        esp_err_t TransmitResult = ESP_OK;
        esp_err_t TxWaitAllDoneResult = ESP_OK;
    };

    class Ws2812RmtTest : public ::testing::Test
    {
    protected:
        MockRmt _mockRmt;
    };

    TEST_F(Ws2812RmtTest, Initialize_ConfiguresAndEnablesRmtChannel)
    {
        {
            M60::Ws28xx::Ws2812Rmt ledStrip(4, 8, _mockRmt);
            ledStrip.Initialize();

            EXPECT_EQ(_mockRmt.NewTxChannelCallCount, 1U);
            EXPECT_EQ(_mockRmt.LastPin, 4U);
            EXPECT_EQ(_mockRmt.EnableCallCount, 1U);
            EXPECT_EQ(_mockRmt.NewSimpleEncoderCallCount, 1U);
        } // Destructor runs here

        // Verify lifecycle cleanup in destructor
        EXPECT_EQ(_mockRmt.DelEncoderCallCount, 1U);
        EXPECT_EQ(_mockRmt.DelChannelCallCount, 1U);
    }

#ifndef ESP_PLATFORM
    // Windows simulation stub for ESP-IDF rmt_symbol_word_t
    typedef struct {
        uint32_t duration0 : 15;
        uint32_t level0 : 1;
        uint32_t duration1 : 15;
        uint32_t level1 : 1;
    } rmt_symbol_word_t;
#endif

    TEST_F(Ws2812RmtTest, Send_TransmitsEncodedSymbolsAndWaits)
    {
        M60::Ws28xx::Ws2812Rmt ledStrip(4, 2, _mockRmt); // 2 LEDs = (2 * 24 + 1) symbols
        ledStrip.Initialize();

        // Sample GRB data for 2 LEDs (Green, Red, Blue)
        uint8_t grbData[6] = {
            0xFF, 0x00, 0x00, // LED 0: Green
            0x00, 0xFF, 0x00  // LED 1: Red
        };

        ledStrip.Send(grbData);

        EXPECT_EQ(_mockRmt.TransmitCallCount, 1U);
        EXPECT_EQ(_mockRmt.TxWaitAllDoneCallCount, 1U);
        // Expected buffer size: (2 LEDs * 24 bits + 1 reset symbol) * sizeof(rmt_symbol_word_t)
        size_t expectedSymbols = (2 * 24 + 1);
        EXPECT_EQ(_mockRmt.LastBufferSize, expectedSymbols * sizeof(rmt_symbol_word_t));
    }
}
