#pragma once

/// @brief Dirty class
/// @details This class can be used either in conjunction with the Dirty class so an instance can be used or directly 
/// derive it as base class, or only the interface can be used for a more specific dirty algorithm.
class IDirty
{
public:
    IDirty();
    virtual ~IDirty();

    virtual bool IsDirty() const = 0;
    virtual void MarkDirty() = 0;
    virtual void ClearDirty() = 0;
};
