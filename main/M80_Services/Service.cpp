#pragma once

#include "Service.hpp"

namespace M80
{
    Service::Service(
        M90::Assert::IAssert& assert)
        :
        _assert(assert)
    {
        // No actions required.
    }

    Service::~Service()
    {
        // No actions required.
    }

    M90::Assert::IAssert& Service::GetAssert() const
    {
        return _assert;
    }
}
