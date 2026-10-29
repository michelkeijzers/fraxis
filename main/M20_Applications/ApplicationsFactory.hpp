#pragma once

#include "Applications/Application.hpp"
#include "Applications/ApplicationIds.hpp"
#include <cstddef>

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
        ApplicationsManager& applicationsManager);

    template<typename T>
    static void DestroyApplication(
        Application* application)
    {
        static_cast<T*>(application)->~T();
    }
};