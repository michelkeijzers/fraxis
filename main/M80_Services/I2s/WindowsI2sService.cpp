// @file WindowsI2sService.cpp
// Copyright (c) 2026 Michel Keijzers
// SPDX-License-Identifier: GPL-3.0-only

#include "WindowsI2sService.hpp"
#include <cstdint>
#include <cstring>

namespace M80::I2s
{
    WindowsI2sService::WindowsI2sService(
        M90::Assert::IAssert& assert)
    :
        I2sService(assert),
        _port(0),
        _sampleRate(16000),
        _bitsPerSample(16),
        _channels(1),
        _inputPosition(0),
        _started(false)
    {}

    bool WindowsI2sService::ParamConfig(
        uint8_t port,
        uint8_t /* bclkPin */,
        uint8_t /* wsPin */,
        uint8_t /* dinPin */,
        uint8_t /* doutPin */,
        uint32_t sampleRate,
        uint16_t bitsPerSample,
        uint8_t channels)
    {
        // NOSONAR TODO I2S
        _port = port;
        _sampleRate = sampleRate;
        _bitsPerSample = bitsPerSample;
        _channels = channels;
        return true;
    }

    bool WindowsI2sService::DriverInstall(
        uint8_t /* port */)
    {
        // NOSONAR TODO I2S
        return true;
    }

    bool WindowsI2sService::Start(
        uint8_t /* port */)
    {
        //I2S
        _started = true;
        _inputPosition = 0;
        return true;
    }

    bool WindowsI2sService::Stop(
        uint8_t /* port */)
    {
        //I2S
        _started = false;
        return true;
    }

    size_t WindowsI2sService::Read(
        uint8_t /* port */,
        void* buffer,  // NOSONAR: S5008: void *
        size_t length,
        uint32_t /* timeoutInMs */)
    {
        // NOSONAR TODO I2S
        if (!_started || _inputData.empty())
        {
            return 0;
        }

        size_t bytesToRead = length;
        size_t samplesAvailable = _inputData.size() - _inputPosition;
        size_t samplesToRead = bytesToRead / sizeof(int16_t);

        if (samplesToRead > samplesAvailable)
        {
            samplesToRead = samplesAvailable;
            bytesToRead = samplesToRead * sizeof(int16_t);
        }

        if (bytesToRead == 0)
        {
            return 0;
        }

        std::memcpy(buffer, &_inputData[_inputPosition], bytesToRead);
        _inputPosition += samplesToRead;

        if (_inputPosition >= _inputData.size())
        {
            _inputPosition = 0;
        }

        return bytesToRead;
    }

    size_t WindowsI2sService::Write(
        uint8_t /* port */,
        const void* /* buffer */, // NOSONAR: S5008: void * TODO: Change type
        size_t length,
        uint32_t /* timeoutInMs */)
    {
        // NOSONAR TODO I2S
        return length;
    }

    bool WindowsI2sService::SetClock(
        uint8_t /* port */,
        uint32_t sampleRate)
    {
        // NOSONAR TODO I2S
        _sampleRate = sampleRate;
        return true;
    }

    void WindowsI2sService::SetInputData(
        const std::vector<int16_t>& data)
    {
        _inputData = data;
        _inputPosition = 0;
    }
}
