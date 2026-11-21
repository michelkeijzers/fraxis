#pragma once

namespace M90::Assert
{
    class IAssert;
}

namespace M80
{
    class IService
    {
    public:
        virtual ~IService() = default;

        //virtual void SetIServicel(
        //    IService& service) = 0;

        //TODO [[nodiscard]] virtual IService& Service() const = 0;

        //[[nodiscard]] virtual M90::Assert::IAssert& GetAssert() const = 0;
    };
}
