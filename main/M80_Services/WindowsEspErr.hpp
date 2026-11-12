// @file WindowsEspErr.hpp
// Copyright (c) 2026 Michel Keijzers
// SPDX-License-Identifier: GPL-3.0-only

#pragma once

#include <cstdint>

using esp_err_t = int;

static const int32_t ESP_OK = 0;
static const int32_t ESP_FAIL = -1;
static const int32_t ESP_ERR_NVS_INVALID_LENGTH = 0x110C; // 4364
static const int32_t ESP_ERR_NVS_NOT_FOUND = 0x1102; // 4354
static const int32_t ESP_ERR_NVS_NO_FREE_PAGES = 0x110D; // 4365
static const int32_t ESP_ERR_NVS_NEW_VERSION_FOUND = 0x1110; // 4368
