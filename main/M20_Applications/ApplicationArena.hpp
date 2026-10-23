#pragma once

#include <cstdint>
#include <cstddef>

class Application;

class ApplicationArena
{
public:
    void* GetMemory();

    // template<typename T>
    // T* Construct(auto&&... args);

    // template<typename T>
    // void Destroy(T* application);

private:
    static constexpr size_t MAX_APPLICATION_SIZE = 4096;

    alignas(16)
    uint8_t _memory[MAX_APPLICATION_SIZE];
};
