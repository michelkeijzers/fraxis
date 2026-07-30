#include "Dirty.hpp"

Dirty::Dirty()
: IDirty()
{
}

Dirty::~Dirty()
{
}

bool Dirty::IsDirty() const
{
    return _dirty;
}

void Dirty::MarkDirty()
{
    _dirty = true;
}

void Dirty::ClearDirty()
{
    _dirty = false;
}
