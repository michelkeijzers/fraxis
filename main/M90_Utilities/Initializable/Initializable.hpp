// @file Initializable.hpp
// Copyright (c) 2026 Michel Keijzers
// SPDX-License-Identifier: GPL-3.0-only

#pragma once

#include "IInitializable.hpp"

namespace M90::Initializable
{
    class Initializable : public IInitializable
    {
    public:
        Initializable();

        Initializable(
            const Initializable&) = delete;

        Initializable& operator=(
            const Initializable&) = delete;

        Initializable(
            Initializable&&) = delete;

        Initializable& operator=(
            Initializable&&) = delete;

        ~Initializable() override;

        [[nodiscard]] bool IsInitialized() const override;

        void MarkInitialized() override;

    private:
        bool _isInitialized = false;
    };
}
