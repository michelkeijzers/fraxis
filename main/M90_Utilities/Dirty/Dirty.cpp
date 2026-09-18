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
    return _isDirty;
}

void Dirty::MarkDirty()
{
    _isDirty = true;
}

void Dirty::ClearDirty()
{
    _isDirty = false;
}
