#pragma once

#include "../../M40_DomainModels/Audio/I2sMicrophone/I2sMicrophone.hpp"
#include "../../M40_DomainModels/Audio/I2sDac/I2sDac.hpp"
#include "../../M40_DomainModels/Audio/PassiveBuzzer/PassiveBuzzer.hpp"
#include "../../M30_Messages/Types.hpp"

#include <cstdint>

class Context;

namespace M60::Audio
{
    class AudioTaskDeviceDriversDelegate
    {
    public:
        explicit AudioTaskDeviceDriversDelegate(
            Context& context);

        AudioTaskDeviceDriversDelegate(
            const AudioTaskDeviceDriversDelegate&) = delete;

        AudioTaskDeviceDriversDelegate& operator=(
            const AudioTaskDeviceDriversDelegate&) = delete;
        
        AudioTaskDeviceDriversDelegate(
            AudioTaskDeviceDriversDelegate&&) = delete;
        
        AudioTaskDeviceDriversDelegate& operator=(
            AudioTaskDeviceDriversDelegate&&) = delete;

        ~AudioTaskDeviceDriversDelegate() = default;

        void Initialize();

        void Run();

    private:
        Context& _context;
    };
}
