#pragma once

#include <cstdint>

namespace M81::RtosQueue
{
    class RtosQueue
    {
    public:
        RtosQueue() = default;

        RtosQueue(const RtosQueue&) = delete;
        RtosQueue& operator=(const RtosQueue&) = delete;
        RtosQueue(RtosQueue&&) = delete;
        RtosQueue& operator=(RtosQueue&&) = delete;

        virtual ~RtosQueue() = default;

        virtual bool Send(
            const void* itemToQueue,
            uint32_t msToWait) = 0;
        virtual bool Receive(
            void* item,
            uint32_t
            msToWait) = 0;

        virtual bool Peek(
            void* item,
            uint32_t ticksToWait) = 0;
        [[nodiscard]] virtual uint32_t MessagesWaiting() const = 0;
        [[nodiscard]] virtual uint32_t SpacesAvailable() const = 0;

    };
}
