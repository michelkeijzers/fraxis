#pragma once

#include <cstdint>
#include <cstddef>
#include <new>
#include <utility>
#include <array>

class Application;

class ApplicationArena
{
public:
    static constexpr uint16_t MAX_APPLICATION_SIZE = 4096;
    static constexpr size_t ARENA_ALIGNMENT = 16;

    std::array<uint8_t, MAX_APPLICATION_SIZE>& GetMemory()
    {
        return _memory;
    }

    // NOLINTBEGIN(cppcoreguidelines-missing-std-forward)
    template<typename T, typename... Args>
    T* Construct(Args&&... args)
    {
        static_assert(
            sizeof(T) <= MAX_APPLICATION_SIZE, 
            "Application is larger than MAX_APPLICATION_SIZE");
        static_assert(
            alignof(T) <= ARENA_ALIGNMENT, 
            "Applicationalignment is larger than the arena alignment");

        // NOLINTNEXTLINE(cppcoreguidelines-owning-memory)
        return ::new (static_cast<void*>(_memory.data())) T(std::forward<Args>(args)...);
    }
    // NOLINTEND(cppcoreguidelines-missing-std-forward)

    template<typename T>
    void Destroy(T* application) const
    {
        if (application)
        {
            application->~T();
        }
    }

private:

    alignas(ARENA_ALIGNMENT)
        std::array<uint8_t, MAX_APPLICATION_SIZE> _memory; 
};