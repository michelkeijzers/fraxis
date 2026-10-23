#pragma once

#include <cstdint>
#include <cstddef>

class Application;

class AppArena
{
public:
    void* GetMemory();

    // template<typename T>
    // T* Construct(auto&&... args);

    // template<typename T>
    // void Destroy(T* app);

private:
    static constexpr size_t MAX_APP_SIZE = 4096;

    alignas(16)
    uint8_t _memory[MAX_APP_SIZE];
};
