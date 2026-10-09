#include "NvsSettings.hpp"
#include "ApplicationsManager.hpp"
#include "Menu/MenuApplication.hpp"
#include "Queues/I2cOutputQueueWriter.hpp"
#include "Queues/LedStripsQueueWriter.hpp"
#include "../M00_System/DeviceSettings.hpp"
#include "../M10_Composition/Context/Context.hpp"
#include "../M40_DomainModels/I2c/Displays/Tm1637/Tm1637.hpp"
#include "../M40_DomainModels/LedStrips/LedStrips.hpp"
#include "../M80_Services/Nvs/Nvs.hpp"
#include "../M90_Utilities/Assert/Assert.hpp"
#include "../M90_Utilities/Log/Log.hpp"

NvsSettings::NvsSettings(    
    Context& context, 
    ApplicationsManager& applicationsManager,
    I2cOutputQueueWriter& i2cOutputQueueWriter, 
    LedStripsQueueWriter& ledStripsQueueWriter)
:
    _context(context),
    _applicationsManager(applicationsManager),
    _i2cOutputQueueWriter(i2cOutputQueueWriter),
    _ledStripsQueueWriter(ledStripsQueueWriter)
{
}

void NvsSettings::ReadNvsSettings()
{
    ProcessNvsVersion();
    ProcessLogLevels();
    Process7SegmentsBrightness();
    ProcessLedStripsBrightness();
    ProcessAppSettings();
}

void NvsSettings::ProcessNvsVersion()
{
    auto& nvs = _context.GetServices().GetNvs();

    uint8_t nvsVersion = 0;
    if (nvs.ReadUint8("NvsVersion", nvsVersion))
    {
        // For future use, we can check the NVS version and perform migrations if needed.
    }
    else
    {
        Assert::IsTrue(Types::ETaskId::System, 
            nvs.WriteUint8("NvsVersion", DeviceSettings::NVS_VERSION),
            "Failed to write NVS version.");
    }
}

void NvsSettings::ProcessLogLevels()
{
    auto& nvs = _context.GetServices().GetNvs();

    uint32_t logLevels = 0;
    if (nvs.ReadUint32("LogLevels", logLevels))
    {
        Log::SetLogLevels(logLevels);
    }
    else
    {
        Assert::IsTrue(Types::ETaskId::System, 
            nvs.WriteUint32("LogLevels", DeviceSettings::LOG_LEVELS_DEFAULT),
            "Failed to write log levels.");
    }
}

void NvsSettings::Process7SegmentsBrightness()
{
    auto& nvs = _context.GetServices().GetNvs();

    uint8_t brightness = 0;
    if (nvs.ReadUint8("7SegBrightness", brightness))
    {
        _i2cOutputQueueWriter.SendTm1637Brightness(Types::ETm1637Id::CentralPanel, brightness); 
    }
    else
    {
        Assert::IsTrue(Types::ETaskId::System, 
            nvs.WriteUint8("7SegBrightness", DeviceSettings::NVS_7_SEGMENTS_BRIGHTNESS_DEFAULT),
            "Failed to write 7 segments brightness.");
    }
}

void NvsSettings::ProcessLedStripsBrightness()
{
    auto& nvs = _context.GetServices().GetNvs();

    uint8_t brightness = 0;
    if (nvs.ReadUint8("LedStripsBright", brightness))
    {
        _ledStripsQueueWriter.SendLedStripsBrightness(brightness);
    }
    else
    {
        Assert::IsTrue(Types::ETaskId::System, 
            nvs.WriteUint8("LedStripsBright", 100),
            "Failed to write led strips brightness.");
    }
}

void NvsSettings::ProcessAppSettings()
{
    auto& nvs = _context.GetServices().GetNvs();

    uint16_t lastSelectedAppIndex = 0;
    if (nvs.ReadUint16("LastSelAppIndex", lastSelectedAppIndex))
    {
        MenuApplication* menu = static_cast<MenuApplication*>(
            _applicationsManager.GetApplications()[0].get()); // 0 = menu
        menu->GetStates().SetSelectedAppIndex(lastSelectedAppIndex);
    }
    else
    {
        Assert::IsTrue(Types::ETaskId::System, 
            nvs.WriteUint16("LastSelAppIndex", 0),
            "Failed to write last selected application index.");
    }

    uint8_t lastSelectedViewMode = 0;
    if (nvs.ReadUint8("LastSelViewMode", lastSelectedViewMode))
    {
        MenuApplication* menu = static_cast<MenuApplication*>(
            _applicationsManager.GetApplications()[0].get()); // 0 = menu
        menu->GetStates().SetSelectedViewModeIndex(static_cast<States::EViewMode>(lastSelectedViewMode));
    }
    else
    {
        Assert::IsTrue(Types::ETaskId::System, 
            nvs.WriteUint8("LastSelViewMode", 0),
            "Failed to write last selected view mode.");
    }

    uint8_t lastSelectedAppType = 0;
    if (nvs.ReadUint8("LastSelAppType", lastSelectedAppType))
    {
        MenuApplication* menu = static_cast<MenuApplication*>(
            _applicationsManager.GetApplications()[0].get()); // 0 = menu
        menu->GetStates().SetSelectedAppTypeIndex(static_cast<Application::EType>(lastSelectedAppType));
    }
    else
    {
        Assert::IsTrue(Types::ETaskId::System, 
            nvs.WriteUint8("LastSelAppType", 0),
            "Failed to write last selected application type.");
    }

    uint8_t lastSelectedTag = 0;
    if (nvs.ReadUint8("LastSelTag", lastSelectedTag))
    {
        MenuApplication* menu = static_cast<MenuApplication*>(
            _applicationsManager.GetApplications()[0].get()); // 0 = menu
        menu->GetStates().SetSelectedTagIndex(lastSelectedTag);
    }
    else
    {
        Assert::IsTrue(Types::ETaskId::System, 
            nvs.WriteUint8("LastSelTag", 0),
            "Failed to write last selected tag.");
    }
}
