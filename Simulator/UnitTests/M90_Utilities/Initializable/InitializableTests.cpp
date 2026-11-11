#include <gtest/gtest.h>
#include "../../../../main/M90_Utilities/Initializable/Initializable.hpp"

namespace M90::InitializableTests
{
    // Concrete test subclass matching the void Initialize() signature from IInitializable
    class TestInitializable : public M90::Initializable::Initializable
    {
    public:
        void Initialize() override
        {
            MarkInitialized();
        }
    };

    class InitializableTest : public ::testing::Test
    {
    protected:
        void SetUp() override
        {
            // No specific setup required for these tests
        }

        void TearDown() override
        {
            // No specific teardown required for these tests
        }
    };

    TEST_F(InitializableTest, InitialStateIsNotInitialized)
    {
        TestInitializable initObj;
        EXPECT_FALSE(initObj.IsInitialized());
    }

    TEST_F(InitializableTest, MarkInitializedSetsStateToInitialized)
    {
        TestInitializable initObj;

        initObj.MarkInitialized();

        EXPECT_TRUE(initObj.IsInitialized());
    }
}