#pragma once

class ComponentModel
{
public:
    virtual ~ComponentModel() = 0;

    void MarkDirty()     { _dirty = true; }
    void ClearDirty()    { _dirty = false; }
    bool IsDirty() const { return _dirty; }

private:
    bool _dirty = false;
};

inline ComponentModel::~ComponentModel() = default;
