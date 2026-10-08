#pragma once

class Context;
class I2cOutputQueueWriter;
class LedStripsQueueWriter;

class NvsSettings
{
public:
    NvsSettings(
        Context& context, 
        I2cOutputQueueWriter& i2cOutputQueueWriter, 
        LedStripsQueueWriter& ledStripsQueueWriter );
    ~NvsSettings() = default;

    void ReadNvsSettings();

private:
    Context& _context;
    I2cOutputQueueWriter& _i2cOutputQueueWriter;
    LedStripsQueueWriter& _ledStripsQueueWriter;

    void ProcessNvsVersion();
    void ProcessNvs7SegmentsBrightness();
    void ProcessNvsLedStripsBrightness();
};
