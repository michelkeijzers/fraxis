#include "Initializable.hpp"

Initializable::Initializable()
: IInitializable()
{
}

Initializable::~Initializable()
{
}

bool Initializable::IsInitialized() const
{
    return _isInitialized;
}

void Initializable::MarkInitialized()
{
    _isInitialized = true;
}
