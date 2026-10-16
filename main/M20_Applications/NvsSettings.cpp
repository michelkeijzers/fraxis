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

const std::string NvsSettings::NVS_VERSION_KEY = "nvs_version";
const std::string NvsSettings::LOG_LEVELS_KEY = "log_levels";
const std::string NvsSettings::SEVEN_SEGMENT_BRIGHTNESS_KEY = "7_segments_bri";
const std::string NvsSettings::LED_STRIPS_BRIGHTNESS_KEY = "led_strips_bri";
const std::string NvsSettings::LAST_SELECTED_APP_INDEX_KEY = "last_app_index";
const std::string NvsSettings::LAST_SELECTED_VIEW_MODE_INDEX_KEY = "last_view_mode";
const std::string NvsSettings::LAST_SELECTED_APP_TYPE_INDEX_KEY = "last_app_type";
const std::string NvsSettings::LAST_SELECTED_TAG_INDEX_KEY = "last_tag_index";

NvsSettings::NvsSettings(    
    Context& context, 
    ApplicationsManager& applicationsManager,
    I2cOutputQueueWriter& i2cOutputQueueWriter, 
    LedStripsQueueWriter& ledStripsQueueWriter)
:
    _context(context),
    _applicationsManager(applicationsManager),
    _i2cOutputQueueWriter(i2cOutputQueueWriter),
    _ledStripsQueueWriter(ledStripsQueueWriter),
    _nvsVersion(DeviceSettings::NVS_VERSION),
    _logLevels(0),
    _sevenSegmentsBrightness(DeviceSettings::NVS_7_SEGMENTS_BRIGHTNESS_DEFAULT),
    _ledStripsBrightness(DeviceSettings::NVS_LED_STRIPS_BRIGHTNESS_DEFAULT),
    _lastSelectedAppIndex(0),
    _lastSelectedViewModeIndex(0),
    _lastSelectedAppTypeIndex(0),
    _lastSelectedTagIndex(0)
{
}

void NvsSettings::Read()
{
    ReadNvsVersion();
    ReadLogLevels();
    Read7SegmentsBrightness();
    ReadLedStripsBrightness();
    ReadAppSettings();
}

void NvsSettings::ReadNvsVersion()
{
    auto& nvs = _context.GetServices().GetNvs();

    if (nvs.ReadUint8(NVS_VERSION_KEY, _nvsVersion))
    {
        // For future use, we can check the NVS version and perform migrations if needed.
    }
    else
    {
        _nvsVersion = DeviceSettings::NVS_VERSION;
        Assert::IsTrue(Types::ETaskId::System, 
            nvs.WriteUint8(NVS_VERSION_KEY, _nvsVersion),
            "Failed to write NVS version.");
    }
}

void NvsSettings::ReadLogLevels()
{
    auto& nvs = _context.GetServices().GetNvs();

    if (nvs.ReadUint32(LOG_LEVELS_KEY, _logLevels))
    {
        Log::SetLogLevels(_logLevels);
    }
    else
    {
        _logLevels = DeviceSettings::LOG_LEVELS_DEFAULT;
        Assert::IsTrue(Types::ETaskId::System, 
            nvs.WriteUint32(LOG_LEVELS_KEY, _logLevels),
            "Failed to write log levels.");
    }
}

void NvsSettings::Read7SegmentsBrightness()
{
    auto& nvs = _context.GetServices().GetNvs();

    if (nvs.ReadUint8(SEVEN_SEGMENT_BRIGHTNESS_KEY, _sevenSegmentsBrightness))
    {
        _i2cOutputQueueWriter.SendTm1637Brightness(
            Types::ETm1637Id::CentralPanel, _sevenSegmentsBrightness); 
    }
    else
    {
        _sevenSegmentsBrightness = DeviceSettings::NVS_7_SEGMENTS_BRIGHTNESS_DEFAULT;
        Assert::IsTrue(Types::ETaskId::System, 
            nvs.WriteUint8(SEVEN_SEGMENT_BRIGHTNESS_KEY, _sevenSegmentsBrightness),
            "Failed to write 7 segments brightness.");
    }
}

void NvsSettings::ReadLedStripsBrightness()
{
    auto& nvs = _context.GetServices().GetNvs();

    if (nvs.ReadUint8(LED_STRIPS_BRIGHTNESS_KEY, _ledStripsBrightness))
    {
        _ledStripsQueueWriter.SendLedStripsBrightness(_ledStripsBrightness);
    }
    else
    {
        _ledStripsBrightness = DeviceSettings::NVS_LED_STRIPS_BRIGHTNESS_DEFAULT;
        Assert::IsTrue(Types::ETaskId::System, 
            nvs.WriteUint8(LED_STRIPS_BRIGHTNESS_KEY, _ledStripsBrightness),
            "Failed to write led strips brightness.");
    }
}

void NvsSettings::ReadAppSettings()
{
    ReadLastSelectedAppIndex();
    ReadLastSelectedViewModeIndex();
    ReadLastSelectedAppTypeIndex();
    ReadLastSelectedTagIndex();
}

void NvsSettings::ReadLastSelectedAppIndex()
{
    auto& nvs = _context.GetServices().GetNvs();

    if (nvs.ReadUint16(LAST_SELECTED_APP_INDEX_KEY, _lastSelectedAppIndex))
    {
        auto* menu = static_cast<MenuApplication*>(
            _applicationsManager.GetApplications()[0].get()); // 0 = menu
        menu->GetStates().SetSelectedAppIndex(_lastSelectedAppIndex);
    }
    else
    {
        _lastSelectedAppIndex = 0;
        Assert::IsTrue(Types::ETaskId::System,
            nvs.WriteUint16(LAST_SELECTED_APP_INDEX_KEY, _lastSelectedAppIndex),
            "Failed to write last selected application index.");
    }
}

void NvsSettings::ReadLastSelectedViewModeIndex()
{
    auto& nvs = _context.GetServices().GetNvs();

    if (nvs.ReadUint8(LAST_SELECTED_VIEW_MODE_INDEX_KEY, _lastSelectedViewModeIndex))
    {
        auto* menu = static_cast<MenuApplication*>(
            _applicationsManager.GetApplications()[0].get()); // 0 = menu
        menu->GetStates().SetSelectedViewMode(
            static_cast<States::EViewMode>(_lastSelectedViewModeIndex));
    }
    else
    {
        _lastSelectedViewModeIndex = 0;
        Assert::IsTrue(Types::ETaskId::System,
            nvs.WriteUint8(LAST_SELECTED_VIEW_MODE_INDEX_KEY, _lastSelectedViewModeIndex),
            "Failed to write last selected view mode index.");
    }
}

void NvsSettings::ReadLastSelectedAppTypeIndex()
{
    auto& nvs = _context.GetServices().GetNvs();

    if (nvs.ReadUint8(LAST_SELECTED_APP_TYPE_INDEX_KEY, _lastSelectedAppTypeIndex))
    {
        auto* menu = static_cast<MenuApplication*>(
            _applicationsManager.GetApplications()[0].get()); // 0 = menu
        menu->GetStates().SetSelectedAppType(
            static_cast<Application::EType>(_lastSelectedAppTypeIndex));
    }
    else
    {
        _lastSelectedAppTypeIndex = 0;
        Assert::IsTrue(Types::ETaskId::System,
            nvs.WriteUint8(LAST_SELECTED_APP_TYPE_INDEX_KEY, _lastSelectedAppTypeIndex),
            "Failed to write last selected application type index.");
    }
}

void NvsSettings::ReadLastSelectedTagIndex()
{
    auto& nvs = _context.GetServices().GetNvs();

    if (nvs.ReadUint8(LAST_SELECTED_TAG_INDEX_KEY, _lastSelectedTagIndex))
    {
        auto* menu = static_cast<MenuApplication*>(
            _applicationsManager.GetApplications()[0].get()); // 0 = menu
        menu->GetStates().SetSelectedTagIndex(_lastSelectedTagIndex);
    }
    else
    {
        _lastSelectedTagIndex = 0;
        Assert::IsTrue(Types::ETaskId::System, 
            nvs.WriteUint8(LAST_SELECTED_TAG_INDEX_KEY, _lastSelectedTagIndex),
            "Failed to write last selected tag index.");
    }
}

uint8_t NvsSettings::GetNvsVersion() const
{
    return _nvsVersion;
}

uint32_t NvsSettings::GetLogLevels() const
{
    return _logLevels;
}

void NvsSettings::SetLogLevels(
    uint32_t logLevels)
{
    _logLevels = logLevels;
}

uint8_t NvsSettings::Get7SegmentsBrightness() const
{
    return _sevenSegmentsBrightness;
}

void NvsSettings::Set7SegmentsBrightness(
    uint8_t brightness)
{
    _sevenSegmentsBrightness = brightness;
}

uint8_t NvsSettings::GetLedStripsBrightness() const
{
    return _ledStripsBrightness;
}

void NvsSettings::SetLedStripsBrightness(
    uint8_t brightness)
{
    _ledStripsBrightness = brightness;
}

uint16_t NvsSettings::GetLastSelectedAppIndex() const
{
    return _lastSelectedAppIndex;
}

void NvsSettings::SetLastSelectedAppIndex(
    uint16_t lastSelectedAppIndex)
{
    _lastSelectedAppIndex = lastSelectedAppIndex;
}

uint8_t NvsSettings::GetLastSelectedViewModeIndex() const
{
    return _lastSelectedViewModeIndex;
}

void NvsSettings::SetLastSelectedViewModeIndex(
    uint8_t lastSelectedViewModeIndex)
{
    _lastSelectedViewModeIndex = lastSelectedViewModeIndex;
}

uint8_t NvsSettings::GetLastSelectedAppTypeIndex() const
{
    return _lastSelectedAppTypeIndex;
}

void NvsSettings::SetLastSelectedAppTypeIndex(
    uint8_t lastSelectedAppTypeIndex)
{
    _lastSelectedAppTypeIndex = lastSelectedAppTypeIndex;
}

uint8_t NvsSettings::GetLastSelectedTagIndex() const
{
    return _lastSelectedTagIndex;
}

void NvsSettings::SetLastSelectedTagIndex(
    uint8_t lastSelectedTagIndex)
{
    _lastSelectedTagIndex = lastSelectedTagIndex;
}

void NvsSettings::Sync()
{
    SyncLogLevelsToNvs();
}

void NvsSettings::SyncLogLevelsToNvs()
{
    auto& nvs = _context.GetServices().GetNvs();
    uint32_t nvsLogLevels;
    Assert::IsTrue(Types::ETaskId::System, nvs.ReadUint32(LOG_LEVELS_KEY, nvsLogLevels));
    uint32_t logLevels = Log::GetLogLevels();
    if (nvsLogLevels != logLevels)
    {
        Assert::IsTrue(Types::ETaskId::System, nvs.WriteUint32(LOG_LEVELS_KEY, logLevels), 
            "Failed to sync log levels.");
    }
}

void NvsSettings::Sync7SegmentsBrightnessToNvs()
{
    auto& nvs = _context.GetServices().GetNvs();
    uint8_t nvsBrightness;
    Assert::IsTrue(Types::ETaskId::System, nvs.ReadUint8(
        SEVEN_SEGMENT_BRIGHTNESS_KEY, nvsBrightness));
    if (nvsBrightness != _sevenSegmentsBrightness)
    {
        Assert::IsTrue(Types::ETaskId::System,
            nvs.WriteUint8(SEVEN_SEGMENT_BRIGHTNESS_KEY, _sevenSegmentsBrightness),
            "Failed to sync 7 segments brightness.");
    }
}

void NvsSettings::SyncLedStripsBrightnessToNvs()
{
    auto& nvs = _context.GetServices().GetNvs();
    uint8_t nvsBrightness;
    Assert::IsTrue(Types::ETaskId::System, nvs.ReadUint8(
        LED_STRIPS_BRIGHTNESS_KEY, nvsBrightness));
    if (nvsBrightness != _ledStripsBrightness)
    {
        Assert::IsTrue(Types::ETaskId::System,
            nvs.WriteUint8(LED_STRIPS_BRIGHTNESS_KEY, _ledStripsBrightness),
            "Failed to sync led strips brightness.");
    }
}

void NvsSettings::SyncAppSettingsToNvs()
{
    SyncLastSelectedAppIndexToNvs();
    SyncLastSelectedViewModeIndexToNvs();
    SyncLastSelectedAppTypeIndexToNvs();
    SyncLastSelectedTagIndexToNvs();
}

void NvsSettings::SyncLastSelectedAppIndexToNvs()
{
    auto& nvs = _context.GetServices().GetNvs();
    uint16_t nvsLastSelectedAppIndex;
    Assert::IsTrue(Types::ETaskId::System, nvs.ReadUint16(
        LAST_SELECTED_APP_INDEX_KEY, nvsLastSelectedAppIndex));
    if (nvsLastSelectedAppIndex != _lastSelectedAppIndex)
    {
        Assert::IsTrue(Types::ETaskId::System,
            nvs.WriteUint16(LAST_SELECTED_APP_INDEX_KEY, _lastSelectedAppIndex),
            "Failed to sync last selected application index.");
    }
}

void NvsSettings::SyncLastSelectedViewModeIndexToNvs()
{
    auto& nvs = _context.GetServices().GetNvs();
    uint8_t nvsLastSelectedViewModeIndex;
    Assert::IsTrue(Types::ETaskId::System, nvs.ReadUint8(LAST_SELECTED_VIEW_MODE_INDEX_KEY, 
        nvsLastSelectedViewModeIndex));
    if (nvsLastSelectedViewModeIndex != _lastSelectedViewModeIndex)
    {
        Assert::IsTrue(Types::ETaskId::System,
            nvs.WriteUint8(LAST_SELECTED_VIEW_MODE_INDEX_KEY, _lastSelectedViewModeIndex),
            "Failed to sync last selected view mode index.");
    }
}

void NvsSettings::SyncLastSelectedAppTypeIndexToNvs()
{
    auto& nvs = _context.GetServices().GetNvs();
    uint8_t nvsLastSelectedAppTypeIndex;
    Assert::IsTrue(Types::ETaskId::System, nvs.ReadUint8(LAST_SELECTED_APP_TYPE_INDEX_KEY, 
        nvsLastSelectedAppTypeIndex));
    if (nvsLastSelectedAppTypeIndex != _lastSelectedAppTypeIndex)
    {
        Assert::IsTrue(Types::ETaskId::System,
            nvs.WriteUint8(LAST_SELECTED_APP_TYPE_INDEX_KEY, _lastSelectedAppTypeIndex),
            "Failed to sync last selected application type index.");
    }
}

void NvsSettings::SyncLastSelectedTagIndexToNvs()
{
    auto& nvs = _context.GetServices().GetNvs();
    uint8_t nvsLastSelectedTag;
    Assert::IsTrue(Types::ETaskId::System, nvs.ReadUint8(LAST_SELECTED_TAG_INDEX_KEY, 
        nvsLastSelectedTag));
    if (nvsLastSelectedTag != _lastSelectedTagIndex)
    {
        Assert::IsTrue(Types::ETaskId::System,
            nvs.WriteUint8(LAST_SELECTED_TAG_INDEX_KEY, _lastSelectedTagIndex),
            "Failed to sync last selected tag index.");
    }
}
