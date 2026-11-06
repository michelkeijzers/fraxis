#include <gtest/gtest.h>
#include "../../../../main/M90_Utilities/Math/BitUtilities.hpp"

class BitUtilitiesTest : public ::testing::Test
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

TEST_F(BitUtilitiesTest, SetBitTurnsBitOn)
{
    uint32_t value = 0x00000000;
    uint32_t result = BitUtilities::SetBit(value, 3, true);
    EXPECT_EQ(result, 0x00000008); // Bit 3 set (2^3 = 8)
}

TEST_F(BitUtilitiesTest, SetBitTurnsBitOff)
{
    uint32_t value = 0x00000008;
    uint32_t result = BitUtilities::SetBit(value, 3, false);
    EXPECT_EQ(result, 0x00000000); // Bit 3 cleared
}

TEST_F(BitUtilitiesTest, SetBitLeavesOtherBitsUntouched)
{
    uint32_t value = 0x000000F0;

    uint32_t resultOn = BitUtilities::SetBit(value, 0, true);
    EXPECT_EQ(resultOn, 0x000000F1);

    uint32_t resultOff = BitUtilities::SetBit(value, 4, false);
    EXPECT_EQ(resultOff, 0x000000E0);
}

TEST_F(BitUtilitiesTest, IsBitSetReturnsCorrectState)
{
    uint32_t value = 0b00001010; // Bits 1 and 3 are set

    EXPECT_TRUE(BitUtilities::IsBitSet(value, 1));
    EXPECT_TRUE(BitUtilities::IsBitSet(value, 3));
    EXPECT_FALSE(BitUtilities::IsBitSet(value, 0));
    EXPECT_FALSE(BitUtilities::IsBitSet(value, 2));
}

TEST_F(BitUtilitiesTest, WorksWithDifferentTypes)
{
    // Test with uint8_t
    uint8_t val8 = 0x00;
    val8 = BitUtilities::SetBit(val8, 7, true);
    EXPECT_TRUE(BitUtilities::IsBitSet(val8, 7));
    EXPECT_EQ(val8, 0x80);

    // Test with wider types (uint64_t)
    uint64_t val64 = 0;
    val64 = BitUtilities::SetBit(val64, 40, true);
    EXPECT_TRUE(BitUtilities::IsBitSet(val64, 40));
}

TEST_F(BitUtilitiesTest, IsBitSetIsConstexpr)
{
    // Verify compile-time evaluation capability of IsBitSet
    static_assert(BitUtilities::IsBitSet(0x04, 2), "Constexpr check failed for set bit");
    static_assert(!BitUtilities::IsBitSet(0x04, 0), "Constexpr check failed for unset bit");
    SUCCEED();
}
