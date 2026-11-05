#pragma warning(push)
#pragma warning(disable : 26495) // Variable unitilized
#include <gtest/gtest.h>
#pragma warning(pop)

#include "../../../../main/M90_Utilities/Assert/Assert.hpp"

// Test fixture for Assert tests
class AssertTest : public ::testing::Test {
protected:
    void SetUp() override {
        // Initialization before each test if needed
    }

    void TearDown() override {
        // Cleanup after each test if needed
    }
};

// Test that Assert::Fail always triggers an abort/halt
TEST_F(AssertTest, FailTriggersAbort) {
    // Assuming Types::ETaskId has a valid default or test value (e.g., 0 or a designated enum value)
    Types::ETaskId testTaskId = static_cast<Types::ETaskId>(0);

    EXPECT_DEATH(Assert::Fail(testTaskId, "Intentional failure test"), ".*");
}

// Test Assert::IsTrue with valid and invalid conditions
TEST_F(AssertTest, IsTrueBehavior) {
    Types::ETaskId testTaskId = static_cast<Types::ETaskId>(0);

    // True condition should pass without halting
    EXPECT_NO_FATAL_FAILURE(Assert::IsTrue(testTaskId, true, "This should pass"));

    // False condition should trigger a halt/abort
    EXPECT_DEATH(Assert::IsTrue(testTaskId, false, "This should fail"), ".*");
}

// Test Assert::IsFalse with valid and invalid conditions
TEST_F(AssertTest, IsFalseBehavior) {
    Types::ETaskId testTaskId = static_cast<Types::ETaskId>(0);

    // False condition should pass without halting
    EXPECT_NO_FATAL_FAILURE(Assert::IsFalse(testTaskId, false, "This should pass"));

    // True condition should trigger a halt/abort
    EXPECT_DEATH(Assert::IsFalse(testTaskId, true, "This should fail"), ".*");
}

// Test Assert::IsNotNullptr with both void* and const void* overloads
TEST_F(AssertTest, IsNotNullptrBehavior) {
    Types::ETaskId testTaskId = static_cast<Types::ETaskId>(0);
    int dummy = 42;
    void* validPtr = &dummy;
    const void* validConstPtr = &dummy;
    void* nullPtr = nullptr;

    // Non-null pointers should pass
    EXPECT_NO_FATAL_FAILURE(Assert::IsNotNullptr(testTaskId, validPtr, "validPtr"));
    EXPECT_NO_FATAL_FAILURE(Assert::IsNotNullptr(testTaskId, validConstPtr, "validConstPtr"));

    // Null pointer should trigger a halt/abort
    EXPECT_DEATH(Assert::IsNotNullptr(testTaskId, nullPtr, "nullPtr"), ".*");
}

// Test Assert::IsEsp32Pin validation rules for ESP32-S3
TEST_F(AssertTest, IsEsp32PinValidation) {
    Types::ETaskId testTaskId = static_cast<Types::ETaskId>(0);

    // Valid pins according to the pin mask rules in Assert.cpp:
    // Ranges: [1, 2], 3, [4, 8], [15, 18], [38, 42], [45, 46], >=47, 48
    uint8_t validPins[] = { 1, 2, 3, 4, 8, 15, 18, 38, 42, 45, 46, 47, 48, 50 };
    for (uint8_t pin : validPins) {
        EXPECT_NO_FATAL_FAILURE(Assert::IsEsp32Pin(testTaskId, pin, "Valid pin test"))
            << "Pin " << (int)pin << " should be valid.";
    }

    // Invalid pins (e.g., pins 9, 10, 14, 22, 25, 30 omitted by the logic)
    uint8_t invalidPins[] = { 9, 10, 14, 22, 25, 30, 35, 44 };
    for (uint8_t pin : invalidPins) {
        EXPECT_DEATH(Assert::IsEsp32Pin(testTaskId, pin, "Invalid pin test"), ".*")
            << "Pin " << (int)pin << " should be invalid and trigger abort.";
    }
}