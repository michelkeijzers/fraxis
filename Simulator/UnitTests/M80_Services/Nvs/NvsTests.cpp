// @file Nvs_Test.cpp
// Copyright (c) 2026 Michel Keijzers
// SPDX-License-Identifier: GPL-3.0-only

#include <gtest/gtest.h>
#include "../../../../main/M80_Services/Nvs/Nvs.hpp"

namespace M80::NvsTests
{
    class TestableNvs : public M80::Nvs::Nvs {
    public:
        // Expose the protected enum for unit testing
        using ReadWriteMode = Nvs::EReadWriteMode;

        // Expose protected methods for unit testing
        using Nvs::Nvs::GetReadWriteMode;
        using Nvs::SetReadWriteMode;
        using Nvs::SetPartition;
        using Nvs::SetNamespace;
        using Nvs::GetPartition;
        using Nvs::GetNamespace;
        using Nvs::GoingFromReadOnlyToReadWrite;

        // Implement pure virtual methods from Nvs (stubs for testing)
        esp_err_t FlashInit() override
        {
            return ESP_OK;
        }

        esp_err_t FlashErase() override
        {
            return ESP_OK;
        }

        esp_err_t Open(EReadWriteMode mode) override
        {
            SetReadWriteMode(mode);
            return ESP_OK;
        }

        esp_err_t EraseKey(std::string_view key) override
        {
            return ESP_OK;
        }

        esp_err_t EraseNamespace() override
        {
            return ESP_OK;
        }

        esp_err_t Close() override
        {
            return ESP_OK;
        }

        esp_err_t CommitAndClose() override { return ESP_OK; }

        // Add stubs for any other pure virtual methods your Nvs class defines:
        // Read/Write worker stubs...
        esp_err_t ReadStringWhileInReadOnlyMode(std::string_view, std::string&) override
        {
            return ESP_OK;
        }

        esp_err_t WriteStringWhileInReadWriteMode(std::string_view, std::string_view) override
        {
            return ESP_OK;
        }

        esp_err_t ReadUint8WhileInReadOnlyMode(std::string_view, uint8_t&) override
        {
            return ESP_OK;
        }

        esp_err_t WriteUint8WhileInReadWriteMode(std::string_view, uint8_t) override
        {
            return ESP_OK;
        }

        esp_err_t ReadUint16WhileInReadOnlyMode(std::string_view, uint16_t&) override
        {
            return ESP_OK;
        }

        esp_err_t WriteUint16WhileInReadWriteMode(std::string_view, uint16_t) override
        {
            return ESP_OK;
        }

        esp_err_t ReadUint32WhileInReadOnlyMode(std::string_view, uint32_t&) override
        {
            return ESP_OK;
        }

        esp_err_t WriteUint32WhileInReadWriteMode(std::string_view, uint32_t) override
        {
            return ESP_OK;
        }

        esp_err_t ReadBlobWhileInReadOnlyMode(std::string_view, uint8_t*, size_t&) override
        {
            return ESP_OK;
        }

        esp_err_t WriteBlobWhileInReadWriteMode(std::string_view, const uint8_t*, size_t) override
        {
            return ESP_OK;
        }
    };

    class NvsTest : public ::testing::Test {
    protected:
        void SetUp() override
        {
            // No actions required.
        }

        void TearDown() override
        {
            // No actions required.
        }

        TestableNvs nvs;
    };

    // Test initial default state
    TEST_F(NvsTest, InitialState) {
        EXPECT_EQ(nvs.GetReadWriteMode(), TestableNvs::ReadWriteMode::ReadOnly);
        EXPECT_TRUE(nvs.GetPartition().empty());
        EXPECT_TRUE(nvs.GetNamespace().empty());
    }

    // Test partition getters and setters
    TEST_F(NvsTest, SetAndGetPartition) {
        std::string_view testPartition = "storage_partition";
        nvs.SetPartition(testPartition);
        EXPECT_EQ(nvs.GetPartition(), testPartition);
    }

    // Test namespace getters and setters
    TEST_F(NvsTest, SetAndGetNamespace) {
        std::string_view testNamespace = "settings";
        nvs.SetNamespace(testNamespace);
        EXPECT_EQ(nvs.GetNamespace(), testNamespace);
    }

    // Test read/write mode getters and setters
    TEST_F(NvsTest, SetAndGetReadWriteMode) {
        nvs.SetReadWriteMode(TestableNvs::ReadWriteMode::ReadWrite);
        EXPECT_EQ(nvs.GetReadWriteMode(), TestableNvs::ReadWriteMode::ReadWrite);

        nvs.SetReadWriteMode(TestableNvs::ReadWriteMode::ReadOnly);
        EXPECT_EQ(nvs.GetReadWriteMode(), TestableNvs::ReadWriteMode::ReadOnly);
    }

    // Test transition check: GoingFromReadOnlyToReadWrite
    TEST_F(NvsTest, GoingFromReadOnlyToReadWriteTransition) {
        // Default is ReadOnly
        EXPECT_EQ(nvs.GetReadWriteMode(), TestableNvs::ReadWriteMode::ReadOnly);

        // Transition from ReadOnly to ReadWrite should return true
        EXPECT_TRUE(nvs.GoingFromReadOnlyToReadWrite(TestableNvs::ReadWriteMode::ReadWrite));

        // Transition from ReadOnly to ReadOnly should return false
        EXPECT_FALSE(nvs.GoingFromReadOnlyToReadWrite(TestableNvs::ReadWriteMode::ReadOnly));

        // Change current state to ReadWrite
        nvs.SetReadWriteMode(TestableNvs::ReadWriteMode::ReadWrite);

        // Transition from ReadWrite to ReadWrite should return false
        EXPECT_FALSE(nvs.GoingFromReadOnlyToReadWrite(TestableNvs::ReadWriteMode::ReadWrite));

        // Transition from ReadWrite to ReadOnly should return false
        EXPECT_FALSE(nvs.GoingFromReadOnlyToReadWrite(TestableNvs::ReadWriteMode::ReadOnly));
    }
}
