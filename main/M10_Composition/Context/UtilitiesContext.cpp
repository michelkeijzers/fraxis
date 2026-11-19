#include "../../M90_Utilities/Algorithm/IAlgorithm.hpp"
#include "../../M90_Utilities/Assert/IAssert.hpp"
#include "../../M90_Utilities/String/IStringUtilities.hpp"
#include "UtilitiesContext.hpp"

UtilitiesContext::UtilitiesContext()
:
    _algorithm(nullptr),
    _assert(nullptr)
{
}

UtilitiesContext::~UtilitiesContext() // NOSONAR S3490: no isdefault
{
    // No actions needed. Do not make = default.
}

void UtilitiesContext::SetAlgorithm(
    std::unique_ptr<M90::Algorithm::IAlgorithm> algorithm)
{
    _algorithm = std::move(algorithm);
}

void UtilitiesContext::SetAssert(
    std::unique_ptr<M90::Assert::IAssert> assert)
{
    _assert = std::move(assert);
}

void UtilitiesContext::SetStringUtilities(
    std::unique_ptr<M90::String::IStringUtilities> stringUtilities)
{
    _stringUtilities = std::move(stringUtilities);
}

M90::Algorithm::IAlgorithm& UtilitiesContext::GetAlgorithm()
{
    return *_algorithm;
}

M90::Assert::IAssert &UtilitiesContext::GetAssert()
{
    return *_assert;
}

M90::String::IStringUtilities& UtilitiesContext::GetStringUtilities()
{
    return *_stringUtilities;
}
