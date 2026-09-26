#include "Nvs.hpp"

Nvs::Nvs()
{
}

Nvs::~Nvs()
{
}

void Nvs::SetPartition(
    const std::string_view partition)
{
    _partition = partition;
}

std::string Nvs::GetPartition() const
{
    return _partition;
}

void Nvs::SetNamespace(
    const std::string_view namespaceName)
{
    _namespaceName = namespaceName;
}

std::string Nvs::GetNamespaceName() const
{
    return _namespaceName;
}
