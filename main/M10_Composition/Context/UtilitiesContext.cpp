#include "../../M90_Utilities/Algorithm/IAlgorithm.hpp"
#include "../../M90_Utilities/Assert/IAssert.hpp"
#include "../../M90_Utilities/Container/IContainerUtilities.hpp"
#include "../../M90_Utilities/String/IStringUtilities.hpp"
#include "UtilitiesContext.hpp"

UtilitiesContext::UtilitiesContext()
:
    _algorithm(nullptr),
    _assert(nullptr)
{
    // No functionality needed.
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

void UtilitiesContext::SetContainerUtilities(
    std::unique_ptr<M90::Container::IContainerUtilities> containerUtilities)
{
    _containerUtilities = std::move(containerUtilities);
}

void UtilitiesContext::SetLog(
    std::unique_ptr<M90::Log::ILog> log)
{
    _log = std::move(log);
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

M90::Container::IContainerUtilities& UtilitiesContext::GetContainerUtilities()
{
    return *_containerUtilities;
}

M90::Log::ILog& UtilitiesContext::GetLog()
{
    return *_log;
}

M90::String::IStringUtilities& UtilitiesContext::GetStringUtilities()
{
    return *_stringUtilities;
}
