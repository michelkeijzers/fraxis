// @file Random_Test.cpp
// Copyright (c) 2026 Michel Keijzers
// SPDX-License-Identifier: GPL-3.0-only

#include <gtest/gtest.h>
#include "../../../../main/M80_Services/Random/Random.hpp"

namespace M80::RandomTests
{
    class TestableRandom : public M80::Random::Random
    {
    public:
        uint32_t mockRandomValue = 0;

        // Implement pure virtual method from Random (stub for testing)
        uint32_t GetRandom() override
        {
            return mockRandomValue;
        }
    };

    class RandomTest : public ::testing::Test
    {
    protected:
        void SetUp() override
        {
            // No actions required.
        }

        void TearDown() override
        {
            // No actions required.
        }

        TestableRandom random;
    };

    // Test GetNext8 masks correctly
    TEST_F(RandomTest, GetNext8MasksToByte)
    {
        random.mockRandomValue = 0x12345678;
        EXPECT_EQ(random.GetNext8(), 0x78);
    }

    // Test GetNext16 masks correctly
    TEST_F(RandomTest, GetNext16MasksToWord)
    {
        random.mockRandomValue = 0x12345678;
        EXPECT_EQ(random.GetNext16(), 0x5678);
    }

    // Test GetNext returns full 32-bit value
    TEST_F(RandomTest, GetNextReturnsFullValue)
    {
        random.mockRandomValue = 0x12345678;
        EXPECT_EQ(random.GetNext(), 0x12345678);
    }

    // Test GetNext with max limit
    TEST_F(RandomTest, GetNextWithMaxLimit)
    {
        random.mockRandomValue = 105;
        EXPECT_EQ(random.GetNext(10), 5); // 105 % 10 = 5
    }

    // Test GetNext with max equal to zero returns zero
    TEST_F(RandomTest, GetNextWithZeroMaxReturnsZero)
    {
        random.mockRandomValue = 105;
        EXPECT_EQ(random.GetNext(0), 0);
    }

    // Test GetNextBetween within valid range
    TEST_F(RandomTest, GetNextBetweenValidRange)
    {
        random.mockRandomValue = 2; // range = max - min + 1 = 10 - 5 + 1 = 6. 2 % 6 = 2
        EXPECT_EQ(random.GetNextBetween(5, 10), 7); // 5 + 2 = 7
    }

    // Test GetNextBetween when min >= max returns min
    TEST_F(RandomTest, GetNextBetweenInvalidRangeReturnsMin)
    {
        random.mockRandomValue = 50;
        EXPECT_EQ(random.GetNextBetween(10, 5), 10);
        EXPECT_EQ(random.GetNextBetween(5, 5), 5);
    }
}
