#pragma once

#include <cstdint>
#include "../DirtyFlag.hpp"

class LedStripModel : DirtyFlag
{
public:
    struct Pixel
    {
        uint8_t red;
        uint8_t green;
        uint8_t blue;
    };

    LedStripModel(uint16_t numberOfLeds);
    virtual ~LedStripModel();

    void SetPixel(uint16_t index, uint8_t red, uint8_t green, uint8_t blue);
    void Fill(uint8_t red, uint8_t green, uint8_t blue);

    Pixel GetPixel(uint16_t index) const;

    Pixel* GetActiveBuffer() { return _activeBuffer; };
    Pixel* GetInactiveBuffer();
    uint32_t ComputeInactiveBufferCurrent();
    void ScaleInactiveBuffer(uint16_t scale);
    void SwapBuffers();

    DirtyFlag& GetDirtyFlag() { return _dirtyFlag; }
    const DirtyFlag& GetDirtyFlag() const { return _dirtyFlag; }

private:
    Pixel* _bufferA;
    Pixel* _bufferB;
    Pixel* _activeBuffer;

    uint16_t _numberOfLeds;
    
    DirtyFlag _dirtyFlag;
};
