#pragma warning(push)
#pragma warning(disable : 26495) // Variable unitilized
#include <gtest/gtest.h>
#pragma warning(pop)

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}