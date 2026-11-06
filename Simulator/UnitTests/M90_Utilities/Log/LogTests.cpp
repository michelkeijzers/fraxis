#include <gtest/gtest.h>
#include "../../../../main/M90_Utilities/Log/Log.hpp"
#include "../../../../main/M30_Messages/Types.hpp"
#include "../../../../main/M30_Messages/Diagnostics/DiagnosticsQueue.hpp"
#include "../../../../main/M00_System/Queues/DiagnosticsQueueWriter.hpp"

// Forward declaration or mock stub for DiagnosticsQueue / DiagnosticsQueueWriter if needed
// (Assuming standard instantiation or mock references can be passed to Log::Initialize)

class LogTest : public ::testing::Test
{
protected:
    void SetUp() override
    {
        // Reset log levels to default state before each test
        Log::SetLogLevels(0xFFFFFFFF);
    }

    void TearDown() override
    {
        // Clean up state if necessary
    }
};

TEST_F(LogTest, GetAndSetLogLevels)
{
    Log::SetLogLevels(0x12345678);
    EXPECT_EQ(Log::GetLogLevels(), 0x12345678);

    Log::SetLogLevels(0x00000000);
    EXPECT_EQ(Log::GetLogLevels(), 0x00000000);
}

TEST_F(LogTest, InitializeExecutesSuccessfully)
{
    // If DiagnosticsQueue and DiagnosticsQueueWriter require concrete instances or mocks:
    DiagnosticsQueue mockQueue;
    DiagnosticsQueueWriter mockWriter(mockQueue);

    // Verify initialization does not crash
    EXPECT_NO_THROW({
        Log::Initialize(mockQueue, mockWriter);
        });
}

TEST_F(LogTest, IntLoggingExecutesWithoutError)
{
    EXPECT_NO_THROW({
        Log::Int(Types::ETaskId::System, "TestInt", 42);
        Log::Int(Types::ETaskId::System, "TestNegative", -100);
        });
}

TEST_F(LogTest, UIntLoggingExecutesWithoutError)
{
    EXPECT_NO_THROW({
        Log::UInt(Types::ETaskId::System, "TestUInt", 12345);
        });
}

TEST_F(LogTest, CharLoggingExecutesWithoutError)
{
    EXPECT_NO_THROW({
        Log::Char(Types::ETaskId::System, "TestChar", 'A');
        });
}

TEST_F(LogTest, StringLoggingExecutesWithoutError)
{
    EXPECT_NO_THROW({
        Log::String(Types::ETaskId::System, "TestString", "Hello ESP");
        });
}

TEST_F(LogTest, PointerLoggingExecutesWithoutError)
{
    int dummyVar = 10;
    EXPECT_NO_THROW({
        Log::Pointer(Types::ETaskId::System, "TestPtr", &dummyVar);
        Log::Pointer(Types::ETaskId::System, "NullPtr", nullptr);
        });
}

TEST_F(LogTest, IntAsBitsLoggingExecutesWithoutError)
{
    EXPECT_NO_THROW({
        Log::IntAsBits(Types::ETaskId::System, "TestBits", 0x0F0F);
        });
}

TEST_F(LogTest, TextLoggingExecutesWithoutError)
{
    EXPECT_NO_THROW({
        Log::Text(Types::ETaskId::System, "Direct log message", Types::ELogLevel::Info);
        });
}

TEST_F(LogTest, EntryAndExitIndentationFlow)
{
    EXPECT_NO_THROW({
        Log::Entry(Types::ETaskId::System, "MyFunction");
        Log::Int(Types::ETaskId::System, "InsideFunc", 1);
        Log::Exit(Types::ETaskId::System, "MyFunction");
        });
}