#include "Initializable.hpp"

Initializable::Initializable()
: IInitializable()
{
}

Initializable::~Initializable() = default;

bool Initializable::IsInitialized() const
{
    return _isInitialized;
}

void Initializable::MarkInitialized()
{
    _isInitialized = true;
}
