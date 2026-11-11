#pragma warning(push)
#pragma warning(disable : 26495) // Variable unitilized
#include <gtest/gtest.h>
#pragma warning(pop)

#include "../../../../main/M90_Utilities/Algorithm/Algorithm.hpp"
#include <string>

namespace M90::Algorithm
{
    // Test fixture for Algorithm tests
    class AlgorithmTest : public ::testing::Test {
    protected:
        void SetUp() override {
            // Initialization before each test if needed
        }

        void TearDown() override {
            // Cleanup after each test if needed
        }
    };

    // Test swapping integers
    TEST_F(AlgorithmTest, SwapIntegers) {
        int a = 5;
        int b = 10;

        M90::Algorithm::Algorithm::Swap(a, b);

        EXPECT_EQ(a, 10);
        EXPECT_EQ(b, 5);
    }

    // Test swapping doubles
    TEST_F(AlgorithmTest, SwapDoubles) {
        double x = 3.17;
        double y = 2.71;

        M90::Algorithm::Algorithm::Swap(x, y);

        EXPECT_DOUBLE_EQ(x, 2.71);
        EXPECT_DOUBLE_EQ(y, 3.17);
    }

    // Test swapping std::string
    TEST_F(AlgorithmTest, SwapStrings) {
        std::string str1 = "Hello";
        std::string str2 = "World";

        M90::Algorithm::Algorithm::Swap(str1, str2);

        EXPECT_EQ(str1, "World");
        EXPECT_EQ(str2, "Hello");
    }

    // Test swapping custom structs / objects
    struct Point {
        int x;
        int y;

        // Equality operator to make EXPECT_EQ work seamlessly with Point
        bool operator==(const Point& other) const = default;
    };

    TEST_F(AlgorithmTest, SwapCustomStruct) {
        Point p1{ 1, 2 };
        Point p2{ 3, 4 };

        M90::Algorithm::Algorithm::Swap(p1, p2);

        EXPECT_EQ(p1, (Point{ 3, 4 }));
        EXPECT_EQ(p2, (Point{ 1, 2 }));
    }
}
