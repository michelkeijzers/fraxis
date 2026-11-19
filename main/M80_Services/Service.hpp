#pragma once

#include "IService.hpp"

namespace M90::Assert
{
    class IAssert;
}

namespace M80
{
    class Service : virtual public IService
    {
    public:
        // Do not make =default in .hpp file because of unique_ptr needing complete (sub) types.
        Service(
            M90::Assert::IAssert& assert);

        Service(
            const Service&) = delete;

        Service& operator=(
            const Service&) = delete;

        Service(
            Service&&) = delete;

        Service& operator=(
            Service&&) = delete;

        // Do not make =default in .hpp file because of unique_ptr needing complete (sub) types.
        virtual ~Service() override;

        M90::Assert::IAssert& GetAssert() const;

    private:
        M90::Assert::IAssert& _assert;
    };
}
