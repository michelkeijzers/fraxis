#include "DeviceModel.hpp"

DeviceModel::DeviceModel(
    M90::Assert::IAssert& assert,
    M90::Log::ILog& log,
    M90::String::IStringUtilities& stringUtilities)
:
    _assert(assert),
    _log(log),
    _stringUtilities(stringUtilities)
{
    // No actions required.
}

M90::Assert::IAssert& DeviceModel::GetAssert() const
{
    return _assert;
}

M90::Log::ILog& DeviceModel::GetLog() const
{
    return _log;
}

M90::String::IStringUtilities& DeviceModel::GetStringUtilities() const
{
    return _stringUtilities;
}
