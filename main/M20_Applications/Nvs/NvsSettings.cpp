#include "NvsSettings.hpp"
#include "../ApplicationsManager.hpp"
#include "../Queues/I2cOutputQueueWriter.hpp"
#include "../Queues/LedStripsQueueWriter.hpp"
#include "../../M00_System/DeviceSettings.hpp"
#include "../../M10_Composition/Context/Context.hpp"
#include "../../M25_Menu/MenuApplication.hpp"
#include "../../M40_DomainModels/I2c/Displays/Tm1637/Tm1637.hpp"
#include "../../M40_DomainModels/LedStrips/LedStrips.hpp"
#include "../../M80_Services/Nvs/Nvs.hpp"
#include "../../M90_Utilities/Assert/Assert.hpp"
#include "../../M90_Utilities/Log/Log.hpp"

const std::string NvsSettings::NAMESPACE = "settings";

const std::string NvsSettings::NVS_VERSION_KEY = "nvs_version";
const std::string NvsSettings::LOG_LEVELS_KEY = "log_levels";
const std::string NvsSettings::SEVEN_SEGMENT_BRIGHTNESS_KEY = "7_segments_bri";
const std::string NvsSettings::LED_STRIPS_BRIGHTNESS_KEY = "led_strips_bri";
const std::string NvsSettings::LAST_SELECTED_APPLICATION_INDEX_KEY = "last_app_index";
const std::string NvsSettings::LAST_SELECTED_VIEW_MODE_INDEX_KEY = "last_view_mode";
const std::string NvsSettings::LAST_SELECTED_APPLICATION_TYPE_INDEX_KEY = "last_app_type";
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
    _lastSelectedApplicationIndex(0),
    _lastSelectedViewModeIndex(0),
    _lastSelectedApplicationTypeIndex(0),
    _lastSelectedTagIndex(0)
{
}

void NvsSettings::Read()
{
    auto& nvs = _context.GetServices().GetNvs();
    nvs.SetNamespace(NAMESPACE);

    ReadNvsVersion();
    ReadLogLevels();
    Read7SegmentsBrightness();
    ReadLedStripsBrightness();
    ReadApplicationSettings();

    nvs.Close();
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

void NvsSettings::ReadApplicationSettings()
{
    ReadLastSelectedApplicationIndex();
    ReadLastSelectedViewModeIndex();
    ReadLastSelectedApplicationTypeIndex();
    ReadLastSelectedTagIndex();
}

void NvsSettings::ReadLastSelectedApplicationIndex()
{
    auto& nvs = _context.GetServices().GetNvs();

    if (nvs.ReadUint16(LAST_SELECTED_APPLICATION_INDEX_KEY, _lastSelectedApplicationIndex))
    {
        GetMenuApplication()->GetStates().GetApplicationSelectionStates().
            SetSelectedApplicationIndex(_lastSelectedApplicationIndex);
    }
    else
    {
        _lastSelectedApplicationIndex = 0;
        Assert::IsTrue(Types::ETaskId::System,
            nvs.WriteUint16(LAST_SELECTED_APPLICATION_INDEX_KEY, _lastSelectedApplicationIndex),
            "Failed to write last selected application index.");
    }
}

void NvsSettings::ReadLastSelectedViewModeIndex()
{
    auto& nvs = _context.GetServices().GetNvs();

    if (nvs.ReadUint8(LAST_SELECTED_VIEW_MODE_INDEX_KEY, _lastSelectedViewModeIndex))
    {
        GetMenuApplication()->GetStates().GetApplicationSelectionStates().SetSelectedViewMode(
            static_cast<ApplicationSelectionStates::EViewMode>(_lastSelectedViewModeIndex));
    }
    else
    {
        _lastSelectedViewModeIndex = 0;
        Assert::IsTrue(Types::ETaskId::System,
            nvs.WriteUint8(LAST_SELECTED_VIEW_MODE_INDEX_KEY, _lastSelectedViewModeIndex),
            "Failed to write last selected view mode index.");
    }
}

void NvsSettings::ReadLastSelectedApplicationTypeIndex()
{
    auto& nvs = _context.GetServices().GetNvs();

    if (nvs.ReadUint8(LAST_SELECTED_APPLICATION_TYPE_INDEX_KEY, _lastSelectedApplicationTypeIndex))
    {
        GetMenuApplication()->GetStates().GetApplicationSelectionStates().
            SetSelectedApplicationType(
                static_cast<Application::EType>(_lastSelectedApplicationTypeIndex));
    }
    else
    {
        _lastSelectedApplicationTypeIndex = 0;
        Assert::IsTrue(Types::ETaskId::System,
            nvs.WriteUint8(
                LAST_SELECTED_APPLICATION_TYPE_INDEX_KEY, _lastSelectedApplicationTypeIndex),
            "Failed to write last selected application type index.");
    }
}

void NvsSettings::ReadLastSelectedTagIndex()
{
    auto& nvs = _context.GetServices().GetNvs();

    if (nvs.ReadUint8(LAST_SELECTED_TAG_INDEX_KEY, _lastSelectedTagIndex))
    {
        GetMenuApplication()->GetStates().GetApplicationSelectionStates().SetSelectedTagIndex(
            _lastSelectedTagIndex);
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

uint16_t NvsSettings::GetLastSelectedApplicationIndex() const
{
    return _lastSelectedApplicationIndex;
}

void NvsSettings::SetLastSelectedApplicationIndex(
    uint16_t lastSelectedApplicationIndex)
{
    _lastSelectedApplicationIndex = lastSelectedApplicationIndex;
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

uint8_t NvsSettings::GetLastSelectedApplicationTypeIndex() const
{
    return _lastSelectedApplicationTypeIndex;
}

void NvsSettings::SetLastSelectedApplicationTypeIndex(
    uint8_t lastSelectedApplicationTypeIndex)
{
    _lastSelectedApplicationTypeIndex = lastSelectedApplicationTypeIndex;
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
    auto& nvs = _context.GetServices().GetNvs();
    nvs.SetNamespace(NAMESPACE);

    SyncLogLevelsToNvs();
    Sync7SegmentsBrightnessToNvs();
    SyncLedStripsBrightnessToNvs();
    SyncApplicationSettingsToNvs();

    Assert::IsTrue(Types::ETaskId::System, nvs.CommitAndClose(), "Failed to commit NVS settings.");
}


void NvsSettings::SyncLogLevelsToNvs()
{
    auto& nvs = _context.GetServices().GetNvs();
    uint32_t nvsLogLevels;
    // Do not check read, the key can not exist (during first boot).
    nvs.ReadUint32(LOG_LEVELS_KEY, nvsLogLevels);
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
    // Do not check read, the key can not exist (during first boot).
    uint8_t nvsBrightness;
    nvs.ReadUint8(SEVEN_SEGMENT_BRIGHTNESS_KEY, nvsBrightness);
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
    // Do not check read, the key can not exist (during first boot).
    nvs.ReadUint8(LED_STRIPS_BRIGHTNESS_KEY, nvsBrightness);
    if (nvsBrightness != _ledStripsBrightness)
    {
        Assert::IsTrue(Types::ETaskId::System,
            nvs.WriteUint8(LED_STRIPS_BRIGHTNESS_KEY, _ledStripsBrightness),
            "Failed to sync led strips brightness.");
    }
}

void NvsSettings::SyncApplicationSettingsToNvs()
{
    SyncLastSelectedApplicationIndexToNvs();
    SyncLastSelectedViewModeIndexToNvs();
    SyncLastSelectedApplicationTypeIndexToNvs();
    SyncLastSelectedTagIndexToNvs();
}

void NvsSettings::SyncLastSelectedApplicationIndexToNvs()
{
    auto& nvs = _context.GetServices().GetNvs();
    // Do not check read, the key can not exist (during first boot).
    uint16_t nvsLastSelectedApplicationIndex;
    nvs.ReadUint16(LAST_SELECTED_APPLICATION_INDEX_KEY, nvsLastSelectedApplicationIndex);
    if (nvsLastSelectedApplicationIndex != _lastSelectedApplicationIndex)
    {
        Assert::IsTrue(Types::ETaskId::System,
            nvs.WriteUint16(LAST_SELECTED_APPLICATION_INDEX_KEY, _lastSelectedApplicationIndex),
            "Failed to sync last selected application index.");
    }
}

void NvsSettings::SyncLastSelectedViewModeIndexToNvs()
{
    auto& nvs = _context.GetServices().GetNvs();
    uint8_t nvsLastSelectedViewModeIndex;
    // Do not check read, the key can not exist (during first boot).
    nvs.ReadUint8(LAST_SELECTED_VIEW_MODE_INDEX_KEY, nvsLastSelectedViewModeIndex);
    if (nvsLastSelectedViewModeIndex != _lastSelectedViewModeIndex)
    {
        Assert::IsTrue(Types::ETaskId::System,
            nvs.WriteUint8(LAST_SELECTED_VIEW_MODE_INDEX_KEY, _lastSelectedViewModeIndex),
            "Failed to sync last selected view mode index.");
    }
}

void NvsSettings::SyncLastSelectedApplicationTypeIndexToNvs()
{
    auto& nvs = _context.GetServices().GetNvs();
    uint8_t nvsLastSelectedApplicationTypeIndex;
    // Do not check read, the key can not exist (during first boot).
    nvs.ReadUint8(LAST_SELECTED_APPLICATION_TYPE_INDEX_KEY, nvsLastSelectedApplicationTypeIndex);
    if (nvsLastSelectedApplicationTypeIndex != _lastSelectedApplicationTypeIndex)
    {
        Assert::IsTrue(
            Types::ETaskId::System,
            nvs.WriteUint8(LAST_SELECTED_APPLICATION_TYPE_INDEX_KEY, 
                _lastSelectedApplicationTypeIndex),
            "Failed to sync last selected application type index.");
    }
}

void NvsSettings::SyncLastSelectedTagIndexToNvs()
{
    auto& nvs = _context.GetServices().GetNvs();
    uint8_t nvsLastSelectedTag;
    // Do not check read, the key can not exist (during first boot).
    nvs.ReadUint8(LAST_SELECTED_TAG_INDEX_KEY, nvsLastSelectedTag);
    if (nvsLastSelectedTag != _lastSelectedTagIndex)
    {
        Assert::IsTrue(Types::ETaskId::System,
            nvs.WriteUint8(LAST_SELECTED_TAG_INDEX_KEY, _lastSelectedTagIndex),
            "Failed to sync last selected tag index.");
    }
}

MenuApplication* NvsSettings::GetMenuApplication()
{
    return static_cast<MenuApplication*>(_applicationsManager.GetMenuApplication());
}