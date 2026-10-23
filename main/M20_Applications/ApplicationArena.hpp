#pragma once

#include <cstdint>
#include <cstddef>
#include <new>
#include <utility>

class Application;

class ApplicationArena
{
public:
    void* GetMemory();

    template<typename T, typename... Args>
    T* Construct(Args&&... args)
    {
        static_assert(sizeof(T) <= MAX_APPLICATION_SIZE, "Applicatie is groter dan MAX_APPLICATION_SIZE!");
        static_assert(alignof(T) <= 16, "Applicatie alignment overschrijdt de arena alignment!");

        // Placement new in de vooraf gereserveerde buffer
        return ::new (static_cast<void*>(_memory)) T(std::forward<Args>(args)...);
    }

    template<typename T>
    void Destroy(T* application)
    {
        if (application)
        {
            application->~T(); // Handmatig de destructor aanroepen
        }
    }

private:
    static constexpr size_t MAX_APPLICATION_SIZE = 4096;

    alignas(16)
        uint8_t _memory[MAX_APPLICATION_SIZE];
};