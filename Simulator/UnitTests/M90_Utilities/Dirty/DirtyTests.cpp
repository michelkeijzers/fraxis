#include <gtest/gtest.h>
#include "../../../../main/M90_Utilities/Dirty/Dirty.hpp"

namespace M90::DirtyTests
{
    class DirtyTest : public ::testing::Test
    {
    protected:
        // Setup can be used if common initialization is needed
        void SetUp() override
        {
            // No specific setup required for these tests
        }

        void TearDown() override
        {
            // No specific teardown required for these tests
        }
    };

    TEST_F(DirtyTest, InitialStateIsNotDirty)
    {
        M90::Dirty::Dirty dirtyObj;
        EXPECT_FALSE(dirtyObj.IsDirty());
    }

    TEST_F(DirtyTest, MarkDirtySetsStateToDirty)
    {
        M90::Dirty::Dirty dirtyObj;

        dirtyObj.MarkDirty();

        EXPECT_TRUE(dirtyObj.IsDirty());
    }

    TEST_F(DirtyTest, ClearDirtyResetsStateToNotDirty)
    {
        M90::Dirty::Dirty dirtyObj;

        dirtyObj.MarkDirty();
        ASSERT_TRUE(dirtyObj.IsDirty()); // Verify it was marked dirty first

        dirtyObj.ClearDirty();

        EXPECT_FALSE(dirtyObj.IsDirty());
    }

    TEST_F(DirtyTest, MultipleTransitionsWorkCorrectly)
    {
        M90::Dirty::Dirty dirtyObj;

        EXPECT_FALSE(dirtyObj.IsDirty());

        dirtyObj.MarkDirty();
        EXPECT_TRUE(dirtyObj.IsDirty());

        dirtyObj.ClearDirty();
        EXPECT_FALSE(dirtyObj.IsDirty());

        dirtyObj.MarkDirty();
        EXPECT_TRUE(dirtyObj.IsDirty());
    }
}