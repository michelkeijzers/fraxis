#include "NvsSettings.hpp"

#include "../M00_System/DeviceSettings.hpp"
#include "../M10_Composition/Context/Context.hpp"
#include "../M80_Services/Nvs/Nvs.hpp"
#include "../M90_Utilities/Assert/Assert.hpp"

NvsSettings::NvsSettings(Context context)
:
    _context(context)
{
}

void NvsSettings::ReadNvsSettings()
{
    ProcessNvsVersion();
    ProcessNvs7SegmentsBrightness();
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

void NvsSettings::ProcessNvs7SegmentsBrightness()
{
    auto& nvs = _context.GetServices().GetNvs();

    uint8_t brightness = 0;
    if (nvs.ReadUint8("7SegBrightness", brightness))
    {
        
    }
    else
    {
        Assert::IsTrue(Types::ETaskId::System, 
            nvs.WriteUint8("7SegBrightness", DeviceSettings::NVS_7_SEGMENTS_BRIGHTNESS_DEFAULT),
            "Failed to write 7 segments brightness.");
    }
}