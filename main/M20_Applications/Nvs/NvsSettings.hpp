#pragma once

#include <string>

namespace M90::Assert
{
    class IAssert;
}

namespace M90::Log
{
    class ILog;
}

class Context;
class MenuApplication;
class ApplicationsManager;
class I2cOutputQueueWriter;
class LedStripsQueueWriter;
class SevenSegmentsDisplaysQueueWriter;

class NvsSettings // NOSONAR TODO nvs: >35 methods
{
public:
    static const std::string NAMESPACE;

    static const std::string NVS_VERSION_KEY;

    static const std::string LOG_LEVELS_KEY;
    
    static const std::string SEVEN_SEGMENT_BRIGHTNESS_KEY;
    
    static const std::string LED_STRIPS_BRIGHTNESS_KEY;
    
    static const std::string LAST_SELECTED_APPLICATION_INDEX_KEY;
    
    static const std::string LAST_SELECTED_VIEW_MODE_INDEX_KEY;
    
    static const std::string LAST_SELECTED_APPLICATION_TYPE_INDEX_KEY;
    
    static const std::string LAST_SELECTED_TAG_INDEX_KEY;

    NvsSettings(
        Context& context, 
        M90::Assert::IAssert& assert,
        M90::Log::ILog& log,
        ApplicationsManager& applicationsManager,
        I2cOutputQueueWriter& i2cOutputQueueWriter, 
        LedStripsQueueWriter& ledStripsQueueWriter,
        SevenSegmentsDisplaysQueueWriter& sevenSegmentsDisplaysQueueWriter);

    NvsSettings(
        const NvsSettings&) = delete;
    
    NvsSettings& operator=(
        const NvsSettings&) = delete;
    
    NvsSettings(
        NvsSettings&&) = delete;
    
    NvsSettings& operator=(
        NvsSettings&&) = delete;

    ~NvsSettings() = default;

    void Read();

    [[nodiscard]] uint8_t GetNvsVersion() const;

    [[nodiscard]] uint32_t GetLogLevels() const;
    
    void SetLogLevels(
        uint32_t logLevels);

    [[nodiscard]] uint8_t Get7SegmentsBrightness() const;

    void Set7SegmentsBrightness(
        uint8_t brightness);

    [[nodiscard]] uint8_t GetLedStripsBrightness() const;
    
    void SetLedStripsBrightness(
        uint8_t brightness);

    [[nodiscard]] uint16_t GetLastSelectedApplicationIndex() const;
    
    void SetLastSelectedApplicationIndex(
        uint16_t lastSelectedApplicationIndex);

    [[nodiscard]] uint8_t GetLastSelectedViewModeIndex() const;
    
    void SetLastSelectedViewModeIndex(
        uint8_t lastSelectedViewModeIndex);

    [[nodiscard]] uint8_t GetLastSelectedApplicationTypeIndex() const;
    
    void SetLastSelectedApplicationTypeIndex(
        uint8_t lastSelectedApplicationTypeIndex);

    [[nodiscard]] uint8_t GetLastSelectedTagIndex() const;
    
    void SetLastSelectedTagIndex(
        uint8_t lastSelectedTagIndex);

    /// @brief Sync settings.
    void Sync();

private:
    void ReadNvsVersion();
    
    void ReadLogLevels();
    
    void Read7SegmentsBrightness();
    
    void ReadLedStripsBrightness();
    
    void ReadApplicationSettings();
    
    void ReadLastSelectedApplicationIndex();
    
    void ReadLastSelectedViewModeIndex();
    
    void ReadLastSelectedApplicationTypeIndex();
    
    void ReadLastSelectedTagIndex();

    void SyncLogLevelsToNvs();
    
    void Sync7SegmentsBrightnessToNvs();
    
    void SyncLedStripsBrightnessToNvs();
    
    void SyncApplicationSettingsToNvs();
    
    void SyncLastSelectedApplicationIndexToNvs();
    
    void SyncLastSelectedViewModeIndexToNvs();
    
    void SyncLastSelectedApplicationTypeIndexToNvs();
    
    void SyncLastSelectedTagIndexToNvs();

    Context &_context;

    M90::Assert::IAssert &_assert;

    M90::Log::ILog& _log;

    ApplicationsManager &_applicationsManager;

    I2cOutputQueueWriter &_i2cOutputQueueWriter;

    LedStripsQueueWriter &_ledStripsQueueWriter;

    SevenSegmentsDisplaysQueueWriter& _sevenSegmentsDisplaysQueueWriter;

    MenuApplication *GetMenuApplication();

    uint8_t _nvsVersion;
    
    uint32_t _logLevels;
    
    uint8_t _sevenSegmentsBrightness;
    
    uint8_t _ledStripsBrightness;
    
    uint16_t _lastSelectedApplicationIndex;
    
    uint8_t _lastSelectedViewModeIndex;
    
    uint8_t _lastSelectedApplicationTypeIndex;
    
    uint8_t _lastSelectedTagIndex;
};
