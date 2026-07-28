#pragma once

class IDirty
{
public:
    IDirty();
    ~IDirty();

    virtual bool IsDirty() const;;
    void MarkDirty();
    void ClearDirty();

private:
    bool _dirty = false;
};
