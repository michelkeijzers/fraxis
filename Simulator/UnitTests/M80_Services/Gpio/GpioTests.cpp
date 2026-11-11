#include <gtest/gtest.h>
#include "../../../../main/M80_Services/Gpio/Gpio.hpp"
#include  "../../../../main/M80_Services/WindowsEspErr.hpp"

// Subclass to expose/test Gpio while satisfying abstract methods
class MockGpio : public Gpio
{
public:
    esp_err_t ConfigAsOutput(uint8_t pin) override { return ESP_OK; }
    esp_err_t ConfigAsInterruptInput(uint8_t pin) override { return ESP_OK; }
    esp_err_t SetLevel(uint8_t pin, bool level) override { return ESP_OK; }
    esp_err_t AddInterruptHandler(
        int pin, void (*interruptCallbackFunction)(void*), void* arg) override { return ESP_OK; }
    void DelayUs(uint32_t microSeconds) override 
    {
        // No action needed.
    }

    bool InstallIsrServiceWhenNotInstalledYetCalled = false;
    bool ShouldInstallationSucceed = true;

protected:
    esp_err_t InstallIsrServiceWhenNotInstalledYet() override
    {
        InstallIsrServiceWhenNotInstalledYetCalled = true;
        return ShouldInstallationSucceed ? ESP_OK : ESP_FAIL;
    }
};

class GpioTest : public ::testing::Test
{
protected:
    void SetUp() override
    {
        // Note: If _isIsrServiceInstalled is static, it persists across tests.
        // To ensure a clean slate, you can either add a friend test hook in Gpio.hpp 
        // to reset the static flag, or test the sequential behavior within a single test case.
    }

    void TearDown() override 
    {
        //  No actions required.
    }
};

// Combining the sequential state checks into a single test prevents 
// static cross-test contamination issues.
TEST_F(GpioTest, InstallIsrServiceSequentialBehavior)
{
    MockGpio gpio1;
    gpio1.ShouldInstallationSucceed = true;

    // 1. First call: service is not installed yet, should delegate and return true
    esp_err_t firstResult = gpio1.InstallIsrService();
    EXPECT_EQ(firstResult, ESP_OK);
    EXPECT_TRUE(gpio1.InstallIsrServiceWhenNotInstalledYetCalled);

    // 2. Second call (using a fresh mock instance, but static flag is now true):
    MockGpio gpio2;
    gpio2.InstallIsrServiceWhenNotInstalledYetCalled = false;

    esp_err_t secondResult = gpio2.InstallIsrService();
    EXPECT_EQ(secondResult, ESP_OK);
    // Since static _isIsrServiceInstalled is now true, it should bypass installation
    EXPECT_FALSE(gpio2.InstallIsrServiceWhenNotInstalledYetCalled);
}