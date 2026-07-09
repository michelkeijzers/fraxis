#pragma once

class DirtyFlag
{
public:
    void MarkDirty()     { _dirty = true; }
    void ClearDirty()    { _dirty = false; }
    bool IsDirty() const { return _dirty; }

private:
    bool _dirty = false;
};
