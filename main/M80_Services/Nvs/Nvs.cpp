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

const std::string_view Nvs::GetPartition() const
{
    return _partition;
}

void Nvs::SetNamespace(
    const std::string_view namespaceName)
{
    _namespaceName = namespaceName;
}

const std::string_view Nvs::GetNamespace() const
{
    return _namespaceName;
}
