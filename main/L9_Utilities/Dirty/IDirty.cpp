#include "IDirty.hpp"

IDirty::IDirty()
: _dirty(true)
{
}

IDirty::~IDirty()
{
}

bool IDirty::IsDirty() const
{
    return _dirty;
}

void IDirty::MarkDirty()
{
    _dirty = true;
}

void IDirty::ClearDirty()
{
    _dirty = false;
}
