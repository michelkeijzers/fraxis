// @file Initializable.cpp
// Copyright (c) 2026 Michel Keijzers
// SPDX-License-Identifier: GPL-3.0-only

#include "Initializable.hpp"

namespace M90::Initializable
{
    Initializable::Initializable()
        : IInitializable()
    {}

    Initializable::~Initializable() = default;

    bool Initializable::IsInitialized() const
    {
        return _isInitialized;
    }

    void Initializable::MarkInitialized()
    {
        _isInitialized = true;
    }
}
