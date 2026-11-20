#include "../M10_Composition/Context/Context.hpp"
#include "../M10_Composition/Context/DomainModelsContext.hpp"
#include "../M80_Services/Random/IRandom.hpp"
#include "../M81_RtosServices/RtosQueue/RtosQueue.hpp"
#include "../M90_Utilities/Assert/IAssert.hpp"
#include "../M90_Utilities/Log/Log.hpp"
#include "../M90_Utilities/Math/MathUtilities.hpp"
#include "ApplicationsTask.hpp"
#include <cstring>

ApplicationsTask::ApplicationsTask(
    Context& context,
    M80::Random::IRandom& random,
    M90::Assert::IAssert& assert,
    M90::Container::IContainerUtilities& containerUtilities,
    M90::Log::ILog& log,
    M90::Math::IMathUtilities& mathUtilities,
    M90::String::IStringUtilities& stringUtilities)
:   
    Task(log),
    _context(context),
    _assert(assert),
    _applicationsManager(
        _context, random, assert, containerUtilities, mathUtilities, stringUtilities),
    _i2cInputQueue(_context.GetQueues().GetI2cInputQueue()),
    _i2cInputQueueReader(assert, stringUtilities, _i2cInputQueue, _applicationsManager),
    _i2cOutputQueue(_context.GetQueues().GetI2cOutputQueue()),
    _i2cOutputQueueWriter(assert, stringUtilities, _i2cOutputQueue, _applicationsManager),
    _spiInputQueue(_context.GetQueues().GetSpiInputQueue()),
    _spiInputQueueReader(assert, stringUtilities, _spiInputQueue, _applicationsManager),
    _spiOutputQueue(_context.GetQueues().GetSpiOutputQueue()),
    _spiOutputQueueWriter(assert, stringUtilities, _spiOutputQueue, _applicationsManager),
    _ledStripsQueue(_context.GetQueues().GetLedStripsQueue()),
    _ledStripsQueueWriter(assert, stringUtilities, _ledStripsQueue, _applicationsManager),
    _queueWriters(_i2cOutputQueueWriter, _spiOutputQueueWriter, _ledStripsQueueWriter),
    _nvsSettings(
        _context, assert, log, _applicationsManager, _i2cOutputQueueWriter, _ledStripsQueueWriter),
    _nvsApplicationsInfo(_context, assert)
{
    _applicationsManager.SetQueueWriters(_queueWriters);
    _applicationsManager.SetNvsSettings(_nvsSettings);
    _applicationsManager.SetNvsApplicationsInfo(_nvsApplicationsInfo);
}

void ApplicationsTask::Initialize()
{
    _applicationsManager.Initialize();

}

void ApplicationsTask::Run()
{
    _nvsSettings.Read();
    _nvsApplicationsInfo.Read();
    
    while (true)
    {
        while (_i2cInputQueueReader.HandleMessage())
        {
            // Handle all messages.
        }

        while (_spiInputQueueReader.HandleMessage())
        {
            // Handle all messages.
        }

        _applicationsManager.Run();
        GetRtosTask().DelayTask(1);
    }
    GetLog().Exit(Types::ETaskId::ApplicationsTask, "ApplicationsTask::Run");
}

/* static */ void ApplicationsTask::TaskEntry(
    void* param) // NOSONAR: ESP32 expects void*
{
    auto& self = *static_cast<ApplicationsTask*>(param);
    self.Run();
}
