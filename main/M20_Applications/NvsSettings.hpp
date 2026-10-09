#pragma once

class Context;
class ApplicationsManager;
class I2cOutputQueueWriter;
class LedStripsQueueWriter;

class NvsSettings
{
public:
    NvsSettings(
        Context& context, 
        ApplicationsManager& applicationsManager,
        I2cOutputQueueWriter& i2cOutputQueueWriter, 
        LedStripsQueueWriter& ledStripsQueueWriter);
    ~NvsSettings() = default;

    void ReadNvsSettings();

private:
    Context& _context;
    ApplicationsManager& _applicationsManager;
    I2cOutputQueueWriter& _i2cOutputQueueWriter;
    LedStripsQueueWriter& _ledStripsQueueWriter;

    void ProcessNvsVersion();
    void ProcessLogLevels();
    void Process7SegmentsBrightness();
    void ProcessLedStripsBrightness();
    void ProcessAppSettings();
};
