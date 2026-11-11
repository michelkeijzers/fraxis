#include <gtest/gtest.h>
#include "../../../../main/M90_Utilities/Time/TimeUtilities.hpp"
#include <thread>

namespace M90::TimeTests
{
    class TimeUtilitiesTest : public ::testing::Test
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
    };

    TEST_F(TimeUtilitiesTest, GetCurrentTimeInUsReturnsNonZero)
    {
        auto now = M90::Time::TimeUtilities::GetCurrentTimeInUs();
        EXPECT_GT(now.count(), 0);
    }

    TEST_F(TimeUtilitiesTest, GetUsBetweenCalculatesCorrectDifference)
    {
        std::chrono::microseconds from(1000);
        std::chrono::microseconds to(2500);

        auto diff = M90::Time::TimeUtilities::GetUsBetween(from, to);
        EXPECT_EQ(diff.count(), 1500);
    }

    TEST_F(TimeUtilitiesTest, GetUsSinceReturnsElapsedDuration)
    {
        auto start = M90::Time::TimeUtilities::GetCurrentTimeInUs();

        // Brief sleep to ensure time elapses
        std::this_thread::sleep_for(std::chrono::milliseconds(2));

        auto elapsed = M90::Time::TimeUtilities::GetUsSince(start);
        EXPECT_GE(elapsed.count(), 0);
    }

    TEST_F(TimeUtilitiesTest, FrequencyToIntervalUsCalculatesCorrectInterval)
    {
        // 1000 Hz -> 1000 microseconds (1 ms)
        EXPECT_EQ(M90::Time::TimeUtilities::FrequencyToIntervalUs(1000).count(), 1000);

        // 100 Hz -> 10000 microseconds (10 ms)
        EXPECT_EQ(M90::Time::TimeUtilities::FrequencyToIntervalUs(100).count(), 10000);

        // 1,000,000 Hz -> 1 microsecond
        EXPECT_EQ(M90::Time::TimeUtilities::FrequencyToIntervalUs(1'000'000).count(), 1);
    }
}