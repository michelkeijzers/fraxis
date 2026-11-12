// @file MathUtilitiesTests.cpp
// Copyright (c) 2026 Michel Keijzers
// SPDX-License-Identifier: GPL-3.0-only

#include <gtest/gtest.h>
#include "../../../../main/M90_Utilities/Math/MathUtilities.hpp"

namespace M90::MathTests
{
    class MathUtilitiesTest : public ::testing::Test
    {
    protected:
        void SetUp() override
        {
            // No actions needed.
        }

        void TearDown() override
        {
            // No actions needed.
        }
    };

    // --- Wrap Tests ---

    TEST_F(MathUtilitiesTest, WrapWithinBoundsReturnsSameValue)
    {
        EXPECT_EQ(M90::Math::MathUtilities::Wrap(3, 5), 3);
        EXPECT_EQ(M90::Math::MathUtilities::Wrap(0, 10), 0);
    }

    TEST_F(MathUtilitiesTest, WrapExceedingMaxWrapsAround)
    {
        EXPECT_EQ(M90::Math::MathUtilities::Wrap(5, 5), 0);
        EXPECT_EQ(M90::Math::MathUtilities::Wrap(7, 5), 2);
        EXPECT_EQ(M90::Math::MathUtilities::Wrap(12, 5), 2);
    }

    TEST_F(MathUtilitiesTest, WrapNegativeIndexWrapsCorrectly)
    {
        EXPECT_EQ(M90::Math::MathUtilities::Wrap(-1, 5), 4);
        EXPECT_EQ(M90::Math::MathUtilities::Wrap(-6, 5), 4);
        EXPECT_EQ(M90::Math::MathUtilities::Wrap(-3, 4), 1);
    }

    // --- WrapEnum Tests ---

    enum class TestColor : uint32_t
    {
        Red = 0,
        Green = 1,
        Blue = 2
    };

    TEST_F(MathUtilitiesTest, WrapEnumPositiveDelta)
    {
        TestColor val = TestColor::Red;

        // Move forward by 1
        val = M90::Math::MathUtilities::WrapEnum(val, 1, 3);
        EXPECT_EQ(val, TestColor::Green);

        // Move forward past bounds
        val = M90::Math::MathUtilities::WrapEnum(TestColor::Blue, 1, 3);
        EXPECT_EQ(val, TestColor::Red);

        // Move forward by a larger delta
        val = M90::Math::MathUtilities::WrapEnum(TestColor::Red, 5, 3); // (0 + 5) % 3 = 2 -> Blue
        EXPECT_EQ(val, TestColor::Blue);
    }

    TEST_F(MathUtilitiesTest, WrapEnumNegativeDelta)
    {
        TestColor val = TestColor::Red;

        // Move backward by 1 from Red (wraps to Blue)
        val = M90::Math::MathUtilities::WrapEnum(val, -1, 3);
        EXPECT_EQ(val, TestColor::Blue);

        // Move backward by 2 from Green
        val = M90::Math::MathUtilities::WrapEnum(TestColor::Green, -2, 3); // (1 - 2 + 3) % 3 = 2 -> Blue
        EXPECT_EQ(val, TestColor::Blue);
    }

    // --- Clamp Tests ---

    TEST_F(MathUtilitiesTest, ClampWithinRangeReturnsValue)
    {
        EXPECT_EQ(M90::Math::MathUtilities::Clamp(5, 0, 10), 5);
        EXPECT_EQ(M90::Math::MathUtilities::Clamp(0, 0, 10), 0);
        EXPECT_EQ(M90::Math::MathUtilities::Clamp(10, 0, 10), 10);
    }

    TEST_F(MathUtilitiesTest, ClampBelowMinReturnsMin)
    {
        EXPECT_EQ(M90::Math::MathUtilities::Clamp(-5, 0, 10), 0);
        EXPECT_EQ(M90::Math::MathUtilities::Clamp(2, 5, 10), 5);
    }

    TEST_F(MathUtilitiesTest, ClampAboveMaxReturnsMax)
    {
        EXPECT_EQ(M90::Math::MathUtilities::Clamp(15, 0, 10), 10);
        EXPECT_EQ(M90::Math::MathUtilities::Clamp(100, 10, 50), 50);
    }

    TEST_F(MathUtilitiesTest, ClampMixedTypesAndConstexpr)
    {
        // Test mixed type handling (e.g., int, float/double, or different integer widths)
        auto result = M90::Math::MathUtilities::Clamp(5, 0.5, 4.5);
        EXPECT_DOUBLE_EQ(result, 4.5);

        // Verify compile-time evaluation capability of Clamp
        static_assert(M90::Math::MathUtilities::Clamp(5, 0, 10) == 5, "Constexpr clamp failed");
        static_assert(M90::Math::MathUtilities::Clamp(-2, 0, 10) == 0, "Constexpr clamp low failed");
        static_assert(M90::Math::MathUtilities::Clamp(15, 0, 10) == 10, "Constexpr clamp high failed");
        SUCCEED();
    }
}