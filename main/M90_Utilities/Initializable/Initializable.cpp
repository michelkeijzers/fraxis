#include "Initializable.hpp"

namespace M90::Initializable
{
    Initializable::Initializable()
        : IInitializable()
    {}

    Initializable::~Initializable() = default;

    bool Initializable::IsInitialized() const
    {
        return _isInitialized;
    }

    void Initializable::MarkInitialized()
    {
        _isInitialized = true;
    }
}
