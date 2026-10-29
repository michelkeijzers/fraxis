#include "Nvs.hpp"

Nvs::Nvs()
{
}

Nvs::~Nvs()
{
}

void Nvs::SetPartition(
    std::string_view partition)
{
    _partition = partition;
}

std::string_view Nvs::GetPartition() const
{
    return _partition;
}

void Nvs::SetNamespace(
    std::string_view namespaceName)
{
    _namespaceName = namespaceName;
}

std::string_view Nvs::GetNamespace() const
{
    return _namespaceName;
}
