// @file ContainerUtilities.cpp
// Copyright (c) 2026 Michel Keijzers
// SPDX-License-Identifier: GPL-3.0-only

#include "ContainerUtilities.hpp"

namespace M90::Container
{
    int ContainerUtilities::FindFirstIndexOf(
        std::span<const int> container,
        int value) const
    {
        for (size_t index = 0; index < container.size(); ++index)
        {
            if (container[index] == value)
            {
                return static_cast<int>(index);
            }
        }

        return -1;
    }

    int ContainerUtilities::FindFirstNonEqual(
        std::span<const int> containerA,
        std::span<const int> containerB) const
    {
        if (containerA.size() != containerB.size())
        {
            return -1;
        }

        for (size_t i = 0; i < containerA.size(); ++i)
        {
            if (containerA[i] != containerB[i])
            {
                return static_cast<int>(i);
            }
        }

        return -1;
    }


    int ContainerUtilities::FindFirstNonEqual(
        std::span<const std::string> containerA,
        std::span<const std::string> containerB) const
    {
        if (containerA.size() != containerB.size())
        {
            return -1;
        }

        for (size_t i = 0; i < containerA.size(); ++i)
        {
            if (containerA[i] != containerB[i])
            {
                return static_cast<int>(i);
            }
        }

        return -1;
    }

    int ContainerUtilities::CountDifferent(
        std::span<const int> containerA,
        std::span<const int> containerB) const
    {
        if (containerA.size() != containerB.size())
        {
            return -1;
        }

        int count = 0;
        for (size_t index = 0; index < containerA.size(); index++)
        {
            if (!(containerA[index] == containerB[index]))
            {
                count++;
            }
        }

        return count;
    }
}
