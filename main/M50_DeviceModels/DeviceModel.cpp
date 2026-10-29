#include "DeviceModel.hpp"

DeviceModel::DeviceModel() 
{
}

// Do not make =default in .hpp file because of unique_ptr needing complete (sub) types.
DeviceModel::~DeviceModel() = default;
