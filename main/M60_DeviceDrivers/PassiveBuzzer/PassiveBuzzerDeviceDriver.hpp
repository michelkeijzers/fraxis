// @file PassiveBuzzerDeviceDriver.hpp
// Copyright (c) 2026 Michel Keijzers
// SPDX-License-Identifier: GPL-3.0-only

#pragma once

#include "IPassiveBuzzerDeviceDriver.hpp"
#include "../DeviceDriver.hpp"
#include <cstdint>

namespace M80::Pwm
{
    class IPwm;
}

namespace M81::RtosTask
{
    class IRtosTask;
}

namespace M60::I2s
{
    class PassiveBuzzerDeviceDriver : public DeviceDriver, public IPassiveBuzzerDeviceDriver
    {
    public:
        // Do not make =default in .hpp file because of unique_ptr needing complete (sub) types.
        PassiveBuzzerDeviceDriver(
            M90::Assert::IAssert& assert,
            M90::String::IStringUtilities& stringUtilities);

        PassiveBuzzerDeviceDriver(
            const PassiveBuzzerDeviceDriver&) = delete;
        
        PassiveBuzzerDeviceDriver& operator=(
            const PassiveBuzzerDeviceDriver&) = delete;
        
        PassiveBuzzerDeviceDriver(
            PassiveBuzzerDeviceDriver&&) = delete;
        
        PassiveBuzzerDeviceDriver& operator=(
            PassiveBuzzerDeviceDriver&&) = delete;

        ~PassiveBuzzerDeviceDriver() override;

        [[nodiscard]] bool IsInitialized() const override;
        void Initialize() override;

        [[nodiscard]] M80::Pwm::IPwm& GetPwm() override;

        void SetPwm(
            M80::Pwm::IPwm& pwm) override;

        void SetConfiguration(
            uint8_t pwmPin) override;

        void SetRtosTask(
            M81::RtosTask::IRtosTask& rtosTask) override;

        void SetFrequency(
            uint32_t frequency) override;

        void Start() override;

        void Stop() override;

    private:
        uint8_t _pwmPin;

        uint32_t _frequency;

        M80::Pwm::IPwm* _pwm;

        M81::RtosTask::IRtosTask* _rtosTask;
    };
}