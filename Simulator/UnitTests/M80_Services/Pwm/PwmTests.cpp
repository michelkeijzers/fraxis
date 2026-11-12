// @file Pwm_Test.cpp
// Copyright (c) 2026 Michel Keijzers
// SPDX-License-Identifier: GPL-3.0-only

#include <gtest/gtest.h>
#include "../../../../main/M80_Services/Pwm/Pwm.hpp"

namespace M80::PwmTests
{
    class TestablePwm : public M80::Pwm::Pwm
    {
    public:
        // Track calls to pure virtual methods for verification in tests
        int configTimerCallCount = 0;
        int adjustFrequencyCallCount = 0;
        int adjustDutyCycleCallCount = 0;
        int ledcStopCallCount = 0;

        esp_err_t configTimerReturn = ESP_OK;
        esp_err_t adjustFrequencyReturn = ESP_OK;
        esp_err_t adjustDutyCycleReturn = ESP_OK;
        esp_err_t ledcStopReturn = ESP_OK;

        // Implement pure virtual methods from Pwm (stubs for testing)
        esp_err_t ConfigTimer() override
        {
            configTimerCallCount++;
            return configTimerReturn;
        }

        esp_err_t AdjustFrequency() override
        {
            adjustFrequencyCallCount++;
            return adjustFrequencyReturn;
        }

        esp_err_t AdjustDutyCycle() override
        {
            adjustDutyCycleCallCount++;
            return adjustDutyCycleReturn;
        }

        esp_err_t LedcStop() override
        {
            ledcStopCallCount++;
            return ledcStopReturn;
        }
    };

    class PwmTest : public ::testing::Test
    {
    protected:
        void SetUp() override
        {
            // No actions required.
        }

        void TearDown() override
        {
            // No actions required.
        }

        TestablePwm pwm;
    };

    // Test initial default state
    TEST_F(PwmTest, InitialState)
    {
        EXPECT_EQ(pwm.GetPin(), 0);
        EXPECT_EQ(pwm.GetFrequency(), 0);
        EXPECT_FLOAT_EQ(pwm.GetDutyCycle(), 0.0f);
        EXPECT_FALSE(pwm.GetStarted());
    }

    // Test Config method
    TEST_F(PwmTest, ConfigSetsValuesCorrectly)
    {
        uint8_t expectedPin = 18;
        uint32_t expectedFreq = 1000;
        float expectedDuty = 50.5f;

        pwm.Config(expectedPin, expectedFreq, expectedDuty);

        EXPECT_EQ(pwm.GetPin(), expectedPin);
        EXPECT_EQ(pwm.GetFrequency(), expectedFreq);
        EXPECT_FLOAT_EQ(pwm.GetDutyCycle(), expectedDuty);
    }

    // Test SetFrequency when frequency changes
    TEST_F(PwmTest, SetFrequencyChangesAndAdjusts)
    {
        pwm.Config(18, 1000, 50.0f);
        pwm.adjustFrequencyReturn = ESP_OK;

        esp_err_t err = pwm.SetFrequency(2000);

        EXPECT_EQ(err, ESP_OK);
        EXPECT_EQ(pwm.GetFrequency(), 2000);
        EXPECT_EQ(pwm.adjustFrequencyCallCount, 1);
    }

    // Test SetFrequency when frequency does not change
    TEST_F(PwmTest, SetFrequencyUnchangedDoesNotAdjust)
    {
        pwm.Config(18, 1000, 50.0f);

        esp_err_t err = pwm.SetFrequency(1000);

        EXPECT_EQ(err, ESP_OK);
        EXPECT_EQ(pwm.GetFrequency(), 1000);
        EXPECT_EQ(pwm.adjustFrequencyCallCount, 0);
    }

    // Test SetDutyCycle when duty cycle changes
    TEST_F(PwmTest, SetDutyCycleChangesAndAdjusts)
    {
        pwm.Config(18, 1000, 50.0f);
        pwm.adjustDutyCycleReturn = ESP_OK;

        esp_err_t err = pwm.SetDutyCycle(75.0f);

        EXPECT_EQ(err, ESP_OK);
        EXPECT_FLOAT_EQ(pwm.GetDutyCycle(), 75.0f);
        EXPECT_EQ(pwm.adjustDutyCycleCallCount, 1);
    }

    // Test SetDutyCycle when duty cycle does not change
    TEST_F(PwmTest, SetDutyCycleUnchangedDoesNotAdjust)
    {
        pwm.Config(18, 1000, 50.0f);

        esp_err_t err = pwm.SetDutyCycle(50.0f);

        EXPECT_EQ(err, ESP_OK);
        EXPECT_FLOAT_EQ(pwm.GetDutyCycle(), 50.0f);
        EXPECT_EQ(pwm.adjustDutyCycleCallCount, 0);
    }

    // Test Start method calls ConfigTimer
    TEST_F(PwmTest, StartCallsConfigTimer)
    {
        pwm.configTimerReturn = ESP_OK;

        esp_err_t err = pwm.Start();

        EXPECT_EQ(err, ESP_OK);
        EXPECT_EQ(pwm.configTimerCallCount, 1);
    }

    // Test Stop method when not started returns ESP_OK without calling LedcStop
    TEST_F(PwmTest, StopWhenNotStartedReturnsOk)
    {
        esp_err_t err = pwm.Stop();

        EXPECT_EQ(err, ESP_OK);
        EXPECT_EQ(pwm.ledcStopCallCount, 0);
    }
}