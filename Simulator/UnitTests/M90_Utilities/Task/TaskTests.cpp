#include <gtest/gtest.h>
#include "../../../../main/M90_Utilities/Task/Task.hpp"

namespace M90::TaskTests
{
    class MockRtosTask : public M81::RtosTask::RtosTask
    {
    public:
        void Start() override
        {
            // No actions required.
        };
        bool DelayTask(uint32_t microSeconds) override { return false; }
        uint32_t GetTaskTickCount() override { return 0; }
    };

    class TestTask : public M90::Task::Task
    {
    public:
        void Initialize() override
        {
            // No actions required.
        };

        void Run() override
        {
            // No actions required.
        };
    };

    class TaskTest : public ::testing::Test
    {
    protected:
        void SetUp() override
        {
            // No actions required.
        };

        void TearDown() override
        {
            // No actions required.
        };
    };

    TEST_F(TaskTest, SetAndGetRtosTaskReturnsCorrectReference)
    {
        TestTask task;
        MockRtosTask rtosTaskInstance;

        task.SetRtosTask(rtosTaskInstance);

        // Verify that GetRtosTask returns a reference to the exact object set
        EXPECT_EQ(&task.GetRtosTask(), &rtosTaskInstance);
    }
}
