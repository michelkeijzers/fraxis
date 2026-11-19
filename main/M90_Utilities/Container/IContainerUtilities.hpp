// @file IContainerUtilities.hpp
// Copyright (c) 2026 Michel Keijzers
// SPDX-License-Identifier: GPL-3.0-only

#pragma once

#include "../Assert/Assert.hpp"
#include <span>

namespace M90::Container
{
    class IContainerUtilities
    {
    public:
        IContainerUtilities() = default;

        virtual ~IContainerUtilities() = default;

        /// @brief Find first index of an item, or -1 if not found
        [[nodiscard]] virtual int FindFirstIndexOf(
            std::span<const int> container,
            int value) const = 0;

        /// @brief Find first index of an item within two containers which are not equal, or -1
        /// if not found.
        [[nodiscard]] virtual int FindFirstNonEqual(
            std::span<const int> containerA,
            std::span<const int> containerB) const = 0;

        [[nodiscard]] virtual int FindFirstNonEqual(
            std::span<const std::string> first,
            std::span<const std::string> second) const = 0;

        /// @brief Count the different items in two lists.
        /// @return -1 if lists are not same size.
        [[nodiscard]] virtual int CountDifferent(
            std::span<const int> containerA,
            std::span<const int> containerB) const = 0;
    };
}
