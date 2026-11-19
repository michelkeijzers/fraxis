#pragma once

#include <memory>

namespace M90
{
    namespace Algorithm
    {
        class IAlgorithm;
    }

    namespace Assert
    {
        class IAssert;
    }

    namespace Container
    {
        class IContainerUtilities;
    }

    namespace String
    {
        class IStringUtilities;
    }
}

class UtilitiesContext
{
public:
    // Do not make = default.
    UtilitiesContext();
    
    UtilitiesContext(
        const UtilitiesContext&) = default;

    UtilitiesContext &operator=(
        const UtilitiesContext&) = default;

    UtilitiesContext(
        UtilitiesContext&&) = default;

    UtilitiesContext &operator=(
        UtilitiesContext&&) = default;
    
    // Do not make = default.
    ~UtilitiesContext();

    /// @name Utility setters
    /// @brief Set methods. Some of these methods need e.g. assert or other utilities, so a single
    /// Set methods setting all (just created) instances is not possible.
    /// Also depending on the dependencies, the order of calling Set methods is
    /// important.
    /// @{

    void SetAlgorithm(
        std::unique_ptr<M90::Algorithm::IAlgorithm> algorithm);

    void SetAssert(
        std::unique_ptr<M90::Assert::IAssert> assert);

    void SetContainerUtilities(
        std::unique_ptr<M90::Container::IContainerUtilities> containerUtilities);

    void SetStringUtilities(
        std::unique_ptr<M90::String::IStringUtilities> stringUtilities);

    /// @}

    M90::Algorithm::IAlgorithm& GetAlgorithm();
    
    M90::Assert::IAssert &GetAssert();

    M90::Container::IContainerUtilities& GetContainerUtilities();

    M90::String::IStringUtilities& GetStringUtilities();
      
private:
    std::unique_ptr<M90::Algorithm::IAlgorithm> _algorithm;

    std::unique_ptr<M90::Assert::IAssert> _assert;

    std::unique_ptr<M90::Container::IContainerUtilities> _containerUtilities;

    std::unique_ptr<M90::String::IStringUtilities> _stringUtilities;
};
