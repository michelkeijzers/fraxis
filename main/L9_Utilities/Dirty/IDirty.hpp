#pragma once

/// @brief Dirty class
/// @details This class can be used either in conjunction with the Dirty class so an instance can be used or directly 
/// derive it as base class, or only the interface can be used for a more specific dirty algorithm.
class IDirty
{
public:
    IDirty();
    ~IDirty();

    virtual bool IsDirty() const;;
    void MarkDirty();
    virtual void ClearDirty();

private:
    bool _dirty = false;
};
