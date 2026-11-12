// @file IInitializable.hpp
// Copyright (c) 2026 Michel Keijzers
// SPDX-License-Identifier: GPL-3.0-only

#pragma once

namespace M90::Initializable
{
    class IInitializable
    {
    public:
        IInitializable();

        IInitializable(
            const IInitializable&) = delete;

        IInitializable& operator=(
            const IInitializable&) = delete;

        IInitializable(
            IInitializable&&) = delete;

        IInitializable& operator=(
            IInitializable&&) = delete;

        virtual ~IInitializable();

        virtual void Initialize() = 0;

        [[nodiscard]] virtual bool IsInitialized() const = 0;

        virtual void MarkInitialized() = 0;
    };
}
