#include <gtest/gtest.h>
#include "../../../../main/M80_Services/Gpio/Gpio.hpp"

// Subclass to expose/test Gpio while satisfying abstract methods
class MockGpio : public Gpio
{
public:
    bool ConfigAsOutput(uint8_t pin) override { return true; }
    bool ConfigAsInterruptInput(uint8_t pin) override { return true; }
    bool SetLevel(uint8_t pin, bool level) override { return true; }
    bool AddInterruptHandler(
        int pin, void (*interruptCallbackFunction)(void*), void* arg) override { return true; }
    void DelayUs(uint32_t microSeconds) override 
    {
        // No action needed.
    }

    bool InstallIsrServiceWhenNotInstalledYetCalled = false;
    bool ShouldInstallationSucceed = true;

protected:
    bool InstallIsrServiceWhenNotInstalledYet() override
    {
        InstallIsrServiceWhenNotInstalledYetCalled = true;
        return ShouldInstallationSucceed;
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
    bool firstResult = gpio1.InstallIsrService();
    EXPECT_TRUE(firstResult);
    EXPECT_TRUE(gpio1.InstallIsrServiceWhenNotInstalledYetCalled);

    // 2. Second call (using a fresh mock instance, but static flag is now true):
    MockGpio gpio2;
    gpio2.InstallIsrServiceWhenNotInstalledYetCalled = false;

    bool secondResult = gpio2.InstallIsrService();
    EXPECT_TRUE(secondResult);
    // Since static _isIsrServiceInstalled is now true, it should bypass installation
    EXPECT_FALSE(gpio2.InstallIsrServiceWhenNotInstalledYetCalled);
}