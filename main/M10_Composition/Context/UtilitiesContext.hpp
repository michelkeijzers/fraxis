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

    void Set(
        std::unique_ptr<M90::Algorithm::IAlgorithm> algorithm,
        std::unique_ptr<M90::Assert::IAssert> assert);

    M90::Algorithm::IAlgorithm& GetAlgorithm();
    
    M90::Assert::IAssert &GetAssert();

    M90::String::IStringUtilities& GetStringUtilities();
      
private:
    std::unique_ptr<M90::Algorithm::IAlgorithm> _algorithm;

    std::unique_ptr<M90::Assert::IAssert> _assert;

    std::unique_ptr<M90::String::IStringUtilities> _stringUtilities;
};
