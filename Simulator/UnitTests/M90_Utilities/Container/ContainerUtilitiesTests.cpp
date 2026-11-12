// @file ContainerUtilitiesTests.cpp
// Copyright (c) 2026 Michel Keijzers
// SPDX-License-Identifier: GPL-3.0-only

#pragma warning(push)
#pragma warning(disable : 26495) // Variable unitilized
#include <gtest/gtest.h>
#pragma warning(pop)
#include "../../../../main/M90_Utilities/Container/ContainerUtilities.hpp"
#include <vector>

namespace M90::ContainerUtilitiesTests
{
    // --- FindFindFirstIndexOf Tests ---
    TEST(ContainerUtilitiesTest, FindFirstIndexOf_FoundAtStart)
    {
        std::vector vec = { 10, 20, 30, 40 };
        EXPECT_EQ(M90::Container::ContainerUtilities::FindFirstIndexOf<int>(vec, 10), 0);
    }

    TEST(ContainerUtilitiesTest, FindFirstIndexOf_ReturnsFirstOccurrence)
    {
        std::vector vec = { 10, 20, 30, 20, 40 };
        // Should find the first '20' at index 1, not the second at index 3
        EXPECT_EQ(M90::Container::ContainerUtilities::FindFirstIndexOf<int>(vec, 20), 1);
    }

    TEST(ContainerUtilitiesTest, FindFirstIndexOf_NotFound)
    {
        std::vector vec = { 10, 20, 30 };
        EXPECT_EQ(M90::Container::ContainerUtilities::FindFirstIndexOf<int>(vec, 99), -1);
    }

    TEST(ContainerUtilitiesTest, FindFirstIndexOf_EmptyContainer)
    {
        std::vector<int> emptyVec;
        EXPECT_EQ(M90::Container::ContainerUtilities::FindFirstIndexOf<int>(emptyVec, 10), -1);
    }

    // --- FindFirstNonEqual Tests ---
    TEST(ContainerUtilitiesTest, FindFirstNonEqual_IdenticalContainers)
    {
        std::vector listA = { 1, 2, 3, 4 };
        std::vector listB = { 1, 2, 3, 4 };
        EXPECT_EQ(M90::Container::ContainerUtilities::FindFirstNonEqual(listA, listB), -1);
    }

    TEST(ContainerUtilitiesTest, FindFirstNonEqual_DivergesAtIndex)
    {
        std::vector listA = { 1, 2, 3, 4 };
        std::vector listB = { 1, 2, 9, 4 }; // Differs at index 2
        EXPECT_EQ(M90::Container::ContainerUtilities::FindFirstNonEqual(listA, listB), 2);
    }

    TEST(ContainerUtilitiesTest, FindFirstNonEqual_DifferentSizesReturnsMinusOne)
    {
        std::vector listA = { 1, 2, 3, 4 };
        std::vector listB = { 1, 2, 3 };
        EXPECT_EQ(M90::Container::ContainerUtilities::FindFirstNonEqual(listA, listB), -1);
    }

    // --- CountDifferent Tests ---
    // Note: Depending on how your span is constructed for CountDifferent 
    // (std::span<const TContainerA&>), ensure your container/span wrapper matches.
    TEST(ContainerUtilitiesTest, CountDifferent_MultipleDifferences)
    {
        std::vector listA = { 1, 2, 3, 4 };
        std::vector listB = { 1, 9, 3, 8 }; // Differences at index 1 and 3

        // If CountDifferent expects std::span, pass them as spans:
        int diffCount = M90::Container::ContainerUtilities::CountDifferent<int, int>(listA, listB);
        EXPECT_EQ(diffCount, 2);
    }

    TEST(ContainerUtilitiesTest, CountDifferent_NoDifferences)
    {
        std::vector listA = { 1, 2, 3, 4 };
        int diffCount = M90::Container::ContainerUtilities::CountDifferent<int, int>(listA, listA);
        EXPECT_EQ(diffCount, 0);
    }
}