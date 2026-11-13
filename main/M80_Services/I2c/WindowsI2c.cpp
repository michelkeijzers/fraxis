// @file WindowsI2c.cpp
// Copyright (c) 2026 Michel Keijzers
// SPDX-License-Identifier: GPL-3.0-only

#include "WindowsI2c.hpp"
#include "../../M00_System/DeviceSettings.hpp"
#include "../../M60_DeviceDrivers/I2c/Mcp23017/Mcp23017Registers.hpp"
#include "../../M70_WindowsGdi/GdiSimulator.hpp"
#include "../../M90_Utilities/Log/Log.hpp"
#include <windows.h> // NOSONAR S3806 non portable path

namespace M80::I2c
{
    WindowsI2c::WindowsI2c()
        : I2c(),
        _deviceAddress(0),
        _registerAddress(0),
        _mcp23017_intcap(0)
    {}

    bool WindowsI2c::IsValidPort(
        uint8_t port)
    {
        return (port == 0) || (port == 1);
    }

    esp_err_t WindowsI2c::ParamConfig(
        uint8_t /* port */,
        uint8_t /* sdaPin */,
        uint8_t /* sclPin */,
        uint32_t /* frequency */)
    {
        return ESP_OK;
    }

    esp_err_t WindowsI2c::DriverInstall(
        uint8_t /* port */)
    {
        return ESP_OK;
    }

    esp_err_t WindowsI2c::MasterWriteToDevice(
        uint8_t /* port */,
        uint8_t deviceAddress,
        const uint8_t* /* data */,
        size_t /* length */,
        uint32_t /* timeoutInMs */)
    {
        if (deviceAddress == DeviceSettings::I2C_ADDRESS_LCD2004)
        {
            PostMessage(
                M70::simulatorContext.hWndMain, 
                M70::WM_LCD2004_UPDATE, 0, 0);
        }
        return ESP_OK;
    }

    esp_err_t WindowsI2c::MasterReadFromDevice(
        uint8_t /* port */,
        uint8_t /* deviceAddress */,
        uint8_t* /* data */,
        size_t /* length */,
        uint32_t /* timeoutInMs */)
    {
        return ESP_OK;
    }

    void* WindowsI2c::CmdLinkCreate() // NOSONAR: ESP expects void*
    {
        return (void*)0x12345678;
    }

    void WindowsI2c::CmdLinkDelete(
        void* /* cmd */) // NOSONAR: ESP expects void*
    {
        // No return value.
    }

    esp_err_t WindowsI2c::MasterStart(
        void* /* cmd */) // NOSONAR: ESP expects void*
    {
        return ESP_OK;
    }

    esp_err_t WindowsI2c::MasterWriteDeviceAddress(
        void* /* cmd */, // NOSONAR: ESP expects void*
        uint8_t deviceAddress)
    {
        _deviceAddress = deviceAddress;
        if (deviceAddress == DeviceSettings::I2C_ADDRESS_MCP23017)
        {
            PostMessage(
                M70::simulatorContext.hWndMain, 
                M70::WM_MCP23017_OUTPUT_UPDATE, 0, 0);
        }
        return ESP_OK;
    }

    esp_err_t WindowsI2c::MasterWriteRegisterAddress(
        void* /* cmd */,  // NOSONAR: ESP expects void*
        uint8_t registerAddress)
    {
        _registerAddress = registerAddress;
        return ESP_OK;
    }

    esp_err_t WindowsI2c::MasterWriteByte(
        void* /* cmd */,  // NOSONAR: ESP expects void*
        uint8_t /* byteToWrite */)
    {
        return ESP_OK;
    }

    esp_err_t WindowsI2c::MasterReadByte(
        void* /* cmd */,  // NOSONAR: ESP expects void*
        uint8_t* byteToRead)
    {
        if (_deviceAddress == DeviceSettings::I2C_ADDRESS_MCP23017)
        {
            if (_registerAddress == M60::Mcp23017::MCP23017_INTCAPA)
            {
                *byteToRead = _mcp23017_intcap >> 8;
            }
            else
            {
                *byteToRead = _mcp23017_intcap & 0xff;
            }
        }
        return ESP_OK;
    }

    esp_err_t WindowsI2c::MasterWrite(
        void* /* cmd */, // NOSONAR: ESP expects void*
        const uint8_t* /* data */,
        size_t /* length */)
    {
        return ESP_OK;
    }

    esp_err_t WindowsI2c::MasterRead(
        void* /* cmd */,  // NOSONAR: ESP expects void*
        uint8_t* /* data */,
        size_t /* length */)
    {
        return ESP_OK;
    }

    esp_err_t WindowsI2c::MasterStop(
        void* /* cmd */) // NOSONAR: ESP expects void*
    {
        return ESP_OK;
    }

    esp_err_t WindowsI2c::MasterCmdBegin(
        uint8_t /* port */,
        void* /* cmd */,  // NOSONAR: ESP expects void*
        uint32_t /* timeoutInMs */)
    {
        return ESP_OK;
    }

    /// @brief Sets MCP23017 INTCAP_A/INTCAP_B values to return for MasterReadByte
    /// @param mcp23017_intcap 
    void WindowsI2c::SetMcp23017IntCapReturn(
        uint16_t mcp23017_intcap)
    {
        _mcp23017_intcap = mcp23017_intcap;
    }
}
