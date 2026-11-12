// @file StringUtilitiesTests.cpp
// Copyright (c) 2026 Michel Keijzers
// SPDX-License-Identifier: GPL-3.0-only

#include <gtest/gtest.h>
#include "../../../../main/M90_Utilities/String/StringUtilities.hpp"
#include <vector>
#include <cstring>

namespace M90::StringTests
{
    class StringUtilitiesTest : public ::testing::Test
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

    // --- Center Tests ---

    TEST_F(StringUtilitiesTest, CenterWithEvenPadding)
    {
        // Width 6, text size 2 ("AB") -> padding total = 4 -> left = 2, right = 2
        std::string result = M90::String::StringUtilities::Center("AB", 6);
        EXPECT_EQ(result, "  AB  ");
    }

    TEST_F(StringUtilitiesTest, CenterWithOddPadding)
    {
        // Width 5, text size 1 ("A") -> padding total = 4 -> left = 2, right = 2
        std::string result = M90::String::StringUtilities::Center("A", 5);
        EXPECT_EQ(result, "  A  ");

        // Width 6, text size 1 ("A") -> padding total = 5 -> left = 2, right = 3
        std::string resultOdd = M90::String::StringUtilities::Center("A", 6);
        EXPECT_EQ(resultOdd, "  A   ");
    }

    TEST_F(StringUtilitiesTest, CenterWhenTextSizeEqualsOrExceedsWidth)
    {
        // Equal size
        EXPECT_EQ(M90::String::StringUtilities::Center("Hello", 5), "Hello");

        // Text larger than width (should truncate to width)
        EXPECT_EQ(M90::String::StringUtilities::Center("HelloWorld", 5), "Hello");
    }

    // --- LeftAlign Tests ---

    TEST_F(StringUtilitiesTest, LeftAlignPadsWithSpaces)
    {
        std::string result = M90::String::StringUtilities::LeftAlign("Test", 8);
        EXPECT_EQ(result, "Test    ");
    }

    TEST_F(StringUtilitiesTest, LeftAlignWhenTextSizeEqualsOrExceedsWidth)
    {
        EXPECT_EQ(M90::String::StringUtilities::LeftAlign("Test", 4), "Test");
        EXPECT_EQ(M90::String::StringUtilities::LeftAlign("LongString", 4), "Long");
    }

    // --- CopyToBuffer Tests ---

    TEST_F(StringUtilitiesTest, CopyToBufferSuccessfullyCopiesAndNullTerminates)
    {
        char buffer[10] = { 0 }; // NOSONAR S5945 : std::string 
        M90::String::StringUtilities::CopyToBuffer("Hello", buffer, sizeof(buffer));

        EXPECT_STREQ(buffer, "Hello");
        // Verify null termination and trailing space safety
        EXPECT_EQ(buffer[5], '\0');
    }

    TEST_F(StringUtilitiesTest, CopyToBufferExactFitOmitsNullIfNoRoom)
    {
        // If source size equals bufferSize, loop copies all chars, but source.size() < bufferSize check is false (so no extra '\0' written via bracket)
        char buffer[3]; // NOSONAR S5945 : std::string 
        M90::String::StringUtilities::CopyToBuffer("Abc", buffer, 3);
        EXPECT_EQ(buffer[0], 'A');
        EXPECT_EQ(buffer[1], 'b');
        EXPECT_EQ(buffer[2], 'c');
    }

    // --- CountDifferentCharacters Tests ---

    TEST_F(StringUtilitiesTest, CountDifferentCharactersReturnsCorrectCount)
    {
        int diffs = M90::String::StringUtilities::CountDifferentCharacters("ABCDE", "ABXEY");
        // Index 2 ('C' vs 'X') and Index 4 ('E' vs 'Y') differ -> 2 differences
        EXPECT_EQ(diffs, 3);
    }

    TEST_F(StringUtilitiesTest, CountDifferentCharactersIdenticalStrings)
    {
        int diffs = M90::String::StringUtilities::CountDifferentCharacters("Fraxis", "Fraxis");
        EXPECT_EQ(diffs, 0);
    }
}