#pragma once

class Context;

class NvsSettings
{
public:
    NvsSettings(Context context);
    ~NvsSettings() = default;

    void ReadNvsSettings();

private:
    Context& _context;

    void ProcessNvsVersion();
    void ProcessNvs7SegmentsBrightness();
};
