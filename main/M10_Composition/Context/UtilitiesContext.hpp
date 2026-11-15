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
}

class UtilitiesContext
{
public:
    // Do not make = default.
    UtilitiesContext();
    
    UtilitiesContext(
        const UtilitiesContext&) = delete;

    UtilitiesContext &operator=(
        const UtilitiesContext&) = delete;

    UtilitiesContext(
        UtilitiesContext&&) = delete;

    UtilitiesContext &operator=(
        UtilitiesContext&&) = delete;
    
    // Do not make = default.
    ~UtilitiesContext();

    void SetAlgorithm(
        std::unique_ptr<M90::Algorithm::IAlgorithm> algorithm);

    void SetAssert(
        std::unique_ptr<M90::Assert::IAssert> assert);

    M90::Algorithm::IAlgorithm& GetAlgorithm();
    
    M90::Assert::IAssert &GetAssert();
      
private:
    std::unique_ptr<M90::Algorithm::IAlgorithm> _algorithm;

    std::unique_ptr<M90::Assert::IAssert> _assert;
};
