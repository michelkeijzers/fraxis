#pragma once

class IInitializable
{
public:
    IInitializable();
    ~IInitializable();

    virtual bool IsInitialized() const;;
    void MarkDirty();
    virtual void ClearDirty();

private:
    bool _dirty = false;
};
