#pragma once

#include "Applications/Application.hpp"
#include "Applications/ApplicationIds.hpp"
#include <cstddef>

namespace M90::Assert
{
    class IAssert;
}

class ApplicationArena;

class ApplicationsFactory
{
public:
    struct Result
    {
        Application* application = nullptr;
        void (*destroyFunction)(Application*) = nullptr;
    };

    static Result Create(
        EApplicationId applicationId,
        ApplicationArena& arena,
        Context& context,
        M90::Assert::IAssert& assert,
        ApplicationsManager& applicationsManager);

    template<typename T>
    static void DestroyApplication(
        Application* application)
    {
        static_cast<T*>(application)->~T();
    }
};