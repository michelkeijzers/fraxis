// @file ContainerUtilities.hpp
// Copyright (c) 2026 Michel Keijzers
// SPDX-License-Identifier: GPL-3.0-only

#pragma once

#include "IContainerUtilities.hpp"
#include <span>
#include <string>

namespace M90::Container
{
    class ContainerUtilities : public IContainerUtilities
    {
    public:
        /// @inheritdoc
        [[nodiscard]] int FindFirstIndexOf(
            std::span<const int> container,
            int value) const override;

        /// @inheritdoc
        [[nodiscard]] int FindFirstNonEqual(
            std::span<const int> containerA,
            std::span<const int> containerB) const override;

        /// @inheritdoc
        [[nodiscard]] int FindFirstNonEqual(
            std::span<const std::string> first,
            std::span<const std::string> second) const override;

        /// @inheritdoc
        [[nodiscard]] int CountDifferent(
            std::span<const int> containerA,
            std::span<const int> containerB) const override;
    };
}
