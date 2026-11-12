// @file WindowsRmt.cpp
// Copyright (c) 2026 Michel Keijzers
// SPDX-License-Identifier: GPL-3.0-only

#include "WindowsRmt.hpp"
#include "../../M70_WindowsGdi/GdiSimulator.hpp"
#include "Windows.h"

namespace M80::Rmt
{
    esp_err_t WindowsRmt::DelEncoder()
    {
        return ESP_OK;
    }

    esp_err_t WindowsRmt::DelChannel()
    {
        return ESP_OK;
    }

    esp_err_t WindowsRmt::NewTxChannel(
        uint8_t /* pin */)
    {
        return ESP_OK;
    }

    esp_err_t WindowsRmt::Enable()
    {
        return ESP_OK;
    }

    esp_err_t WindowsRmt::NewSimpleEncoder()
    {
        return ESP_OK;
    }

    esp_err_t WindowsRmt::Transmit(
        const void* /* payload */,  // NOSONAR: S5008: void * TODO: Change type
        size_t /* payload_bytes */)
    {
        // This is the location where a WM Post message to Windows would be in place.
        // However, this overfloods the GDI, so it is handled inside GdiSimulator.
        return ESP_OK;
    }

    esp_err_t WindowsRmt::TxWaitAllDone()
    {
        return ESP_OK;
    }
}
