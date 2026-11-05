#include "Dirty.hpp"

Dirty::Dirty()
: IDirty()
{
}

Dirty::~Dirty() = default;

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
