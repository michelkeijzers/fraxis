// @file PassiveBuzzerDeviceDriver.cpp
// Copyright (c) 2026 Michel Keijzers
// SPDX-License-Identifier: GPL-3.0-only

#include "PassiveBuzzerDeviceDriver.hpp"
#include "../../M90_Utilities/Assert/IAssert.hpp"
#include "../../M80_Services/Pwm/IPwm.hpp"

namespace M60::PassiveBuzzer
{
    PassiveBuzzerDeviceDriver::PassiveBuzzerDeviceDriver(
        M90::Assert::IAssert& assert,
        M90::String::IStringUtilities& stringUtilities)
    : 
        DeviceDriver(assert, stringUtilities),
        _pwmPin(0),
        _frequency(0),
        _pwm(nullptr),
        _rtosTask(nullptr)
    {
        // No functionality required.
    }

    // Do not make =default in .hpp file because of unique_ptr needing complete (sub) types.
    PassiveBuzzerDeviceDriver::~PassiveBuzzerDeviceDriver() = default;

    bool PassiveBuzzerDeviceDriver::IsInitialized() const
    {
        return _pwm != nullptr;
    }

    void PassiveBuzzerDeviceDriver::Initialize()
    {
        //_pwm = new M80::Pwm::Pwm(_pwmPin, _rtosTask);  // NOSONAR TODO: no new, as member
        /// _pwm->Config()
    }


    void PassiveBuzzerDeviceDriver::SetPassiveBuzzerDeviceModel(
        M50::PassiveBuzzer::IPassiveBuzzerDeviceModel& passiveBuzzerDeviceModel)
    {
        _passiveBuzzerDeviceModel = &passiveBuzzerDeviceModel;
    }

    M50::PassiveBuzzer::IPassiveBuzzerDeviceModel& 
        PassiveBuzzerDeviceDriver::GetPassiveBuzzerDeviceModel()
    {
        return *_passiveBuzzerDeviceModel;
    }

    M80::Pwm::IPwm& PassiveBuzzerDeviceDriver::GetPwm()
    {
        return *_pwm;
    }

    void PassiveBuzzerDeviceDriver::SetPwm(
        M80::Pwm::IPwm& pwm)
    {
        _pwm = &pwm;
    }

    void PassiveBuzzerDeviceDriver::SetConfiguration(
        uint8_t pwmPin)
    {
        _pwmPin = pwmPin;
    }

    void PassiveBuzzerDeviceDriver::SetRtosTask(
        M81::RtosTask::IRtosTask& rtosTask)
    {
        _rtosTask = &rtosTask;
    }

    void PassiveBuzzerDeviceDriver::SetFrequency(
        uint32_t frequency)
    {
        _frequency = frequency;
        if (IsInitialized())
        {
            GetPwm().SetFrequency(frequency);
        }
    }

    void PassiveBuzzerDeviceDriver::Start()
    {
        if (_frequency > 0)
        {
            GetPwm().SetFrequency(_frequency);
            GetPwm().Start();
        }
    }

    void PassiveBuzzerDeviceDriver::Stop()
    {
        GetPwm().Stop();
    }
}
