#pragma once

#include <string>

class Context;
class MenuApplication;
class ApplicationsManager;
class I2cOutputQueueWriter;
class LedStripsQueueWriter;

class NvsSettings
{
public:
    static const std::string NVS_VERSION_KEY;
    static const std::string LOG_LEVELS_KEY;
    static const std::string SEVEN_SEGMENT_BRIGHTNESS_KEY;
    static const std::string LED_STRIPS_BRIGHTNESS_KEY;
    static const std::string LAST_SELECTED_APP_INDEX_KEY;
    static const std::string LAST_SELECTED_VIEW_MODE_INDEX_KEY;
    static const std::string LAST_SELECTED_APP_TYPE_INDEX_KEY;
    static const std::string LAST_SELECTED_TAG_INDEX_KEY;

    NvsSettings(
        Context& context, 
        ApplicationsManager& applicationsManager,
        I2cOutputQueueWriter& i2cOutputQueueWriter, 
        LedStripsQueueWriter& ledStripsQueueWriter);
    ~NvsSettings() = default;

    void Read();

    uint8_t GetNvsVersion() const;

    uint32_t GetLogLevels() const;
    void SetLogLevels(
        uint32_t logLevels);

    uint8_t Get7SegmentsBrightness() const;
    void Set7SegmentsBrightness(
        uint8_t brightness);

    uint8_t GetLedStripsBrightness() const;
    void SetLedStripsBrightness(
        uint8_t brightness);

    uint16_t GetLastSelectedAppIndex() const;
    void SetLastSelectedAppIndex(
        uint16_t lastSelectedAppIndex);

    uint8_t GetLastSelectedViewModeIndex() const;
    void SetLastSelectedViewModeIndex(
        uint8_t lastSelectedViewModeIndex);

    uint8_t GetLastSelectedAppTypeIndex() const;
    void SetLastSelectedAppTypeIndex(
        uint8_t lastSelectedAppTypeIndex);

    uint8_t GetLastSelectedTagIndex() const;
    void SetLastSelectedTagIndex(
        uint8_t lastSelectedTagIndex);

    /// @brief Sync settings.
    void Sync();

private:
    Context& _context;
    ApplicationsManager& _applicationsManager;
    I2cOutputQueueWriter& _i2cOutputQueueWriter;
    LedStripsQueueWriter& _ledStripsQueueWriter;

    void ReadNvsVersion();
    void ReadLogLevels();
    void Read7SegmentsBrightness();
    void ReadLedStripsBrightness();
    void ReadAppSettings();
    void ReadLastSelectedAppIndex();
    void ReadLastSelectedViewModeIndex();
    void ReadLastSelectedAppTypeIndex();
    void ReadLastSelectedTagIndex();

    void SyncLogLevelsToNvs();
    void Sync7SegmentsBrightnessToNvs();
    void SyncLedStripsBrightnessToNvs();
    void SyncAppSettingsToNvs();
    void SyncLastSelectedAppIndexToNvs();
    void SyncLastSelectedViewModeIndexToNvs();
    void SyncLastSelectedAppTypeIndexToNvs();
    void SyncLastSelectedTagIndexToNvs();

    MenuApplication* GetMenuApplication();

    uint8_t _nvsVersion;
    uint32_t _logLevels;
    uint8_t _sevenSegmentsBrightness;
    uint8_t _ledStripsBrightness;
    uint16_t _lastSelectedAppIndex;
    uint8_t _lastSelectedViewModeIndex;
    uint8_t _lastSelectedAppTypeIndex;
    uint8_t _lastSelectedTagIndex;
};
