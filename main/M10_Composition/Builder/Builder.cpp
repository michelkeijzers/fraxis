#include "Builder.hpp"
#include "../../M00_System/I2cTask.hpp"
#include "../../M00_System/SpiTask.hpp"
#include "../../M00_System/LedStripsTask.hpp"
#include "../../M00_System/DiagnosticsTask.hpp"
#include "../../M00_System/AudioTask.hpp"
#include "../../M00_System/Queues/DiagnosticsQueueWriter.hpp"
#include "../../M20_Applications/ApplicationsTask.hpp"
#include "../../M30_Messages/Diagnostics/DiagnosticsQueue.hpp"
#include "../../M30_Messages/I2c/I2cInputQueue.hpp"
#include "../../M30_Messages/I2c/I2cOutputQueue.hpp"
#include "../../M30_Messages/LedStrips/LedStripsQueue.hpp"
#include "../../M30_Messages/Spi/SpiInputQueue.hpp"
#include "../../M30_Messages/Spi/SpiOutputQueue.hpp"
#include "../../M30_Messages/Audio/AudioInputQueue.hpp"
#include "../../M30_Messages/Audio/AudioOutputQueue.hpp"
#include "../../M40_DomainModels/I2c/Displays/Tm1637/Tm1637.hpp"
#include "../../M40_DomainModels/I2c/IoPins/IoPins.hpp"
#include "../../M40_DomainModels/LedStrips/LedStrips.hpp"
#include "../../M40_DomainModels/Spi/MicroSdCard/MicroSdCard.hpp"
#include "../../M40_DomainModels/Audio/I2sMicrophone/I2sMicrophone.hpp"
#include "../../M40_DomainModels/Audio/I2sDac/I2sDac.hpp"
#include "../../M40_DomainModels/Audio/PassiveBuzzer/PassiveBuzzer.hpp"
#include "../../M50_DeviceModels/Lcd2004/Lcd2004DeviceModel.hpp"
#include "../../M50_DeviceModels/Mcp23017/Mcp23017DeviceModel.hpp"
#include "../../M50_DeviceModels/Tm1637/Tm1637DeviceModel.hpp"
#include "../../M50_DeviceModels/Ws28xx/Ws28xxDeviceModel.hpp"
#include "../../M50_DeviceModels/MicroSdCard/MicroSdCardDeviceModel.hpp"
#include "../../M50_DeviceModels/Audio/AudioDeviceModel.hpp"
#include "../../M50_DeviceModels/Audio/Inmp1441/Inmp1441DeviceModel.hpp"
#include "../../M50_DeviceModels/Audio/Max53987a/Max53987aDeviceModel.hpp"
#include "../../M50_DeviceModels/Audio/Buzzer/BuzzerDeviceModel.hpp"
#include "../../M81_RtosServices/Rtos/Rtos.hpp"
#include "../../M81_RtosServices/RtosTask/RtosTask.hpp"
#include "../../M90_Utilities/Algorithm/Algorithm.hpp"
#include "../../M90_Utilities/Assert/Assert.hpp"
#include "../../M90_Utilities/String/StringUtilities.hpp"
#include <memory>

namespace M80
{
    namespace Random
    {
        class IRandom;
    }
}

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

Builder::Builder()
: 
    _context(nullptr) 
{
}

Context& Builder::GetContext() 
{
    return *_context; 
}

void Builder::Build()
{
    _context = std::make_unique<Context>();

    BuildUtilitiesContext();

    auto& utilities = GetContext().GetUtilities();
    M90::Algorithm::IAlgorithm& algorithm = utilities.GetAlgorithm();
    M90::Assert::IAssert& assert = utilities.GetAssert();
    M90::String::IStringUtilities& stringUtilities = utilities.GetStringUtilities();

    BuildServicesContext();

    auto& servicesContext = GetContext().GetServices();
    M80::Random::IRandom& random = servicesContext.GetRandom();

    BuildDeviceDriversContext(assert, stringUtilities);

    auto& deviceDriversContext = GetContext().GetDeviceDrivers();
    M60::Ws28xx::Ws28xxDeviceDriver& ws28xxDeviceDriver =
        deviceDriversContext.GetWs28xxDeviceDriver();
    M60::I2c::Lcd2004DeviceDriver& lcd2004DeviceDriver = 
        deviceDriversContext.GetLcd2004DeviceDriver();
    M60::I2c::Mcp23017DeviceDriver& mcp23017DeviceDriver =
        deviceDriversContext.GetMcp23017DeviceDriver();
    M60::I2c::Tm1637DeviceDriver& tm1637DeviceDriverCentralPanel =
        deviceDriversContext.GetTm1637DeviceDriverCentralPanel();
    M60::I2c::Tm1637DeviceDriver& tm1637DeviceDriverPlayer1 =
        deviceDriversContext.GetTm1637DeviceDriverPlayer1();
    M60::I2c::Tm1637DeviceDriver& tm1637DeviceDriverPlayer2 =
        deviceDriversContext.GetTm1637DeviceDriverPlayer2();

    BuildDeviceModelsContext(assert, stringUtilities);

    BuildDomainModelsContext(assert, algorithm);

    BuildQueuesContext(assert, stringUtilities);

    BuildTasksContext(
        ws28xxDeviceDriver,
        lcd2004DeviceDriver,
        mcp23017DeviceDriver,
        tm1637DeviceDriverCentralPanel,
        tm1637DeviceDriverPlayer1,
        tm1637DeviceDriverPlayer2,
        random,
        assert,
        stringUtilities);
}

void Builder::BuildUtilitiesContext()
{
    auto& utilities = GetContext().GetUtilities();
    utilities.SetAlgorithm(
        std::make_unique<M90::Algorithm::Algorithm>());
    utilities.SetAssert(
        std::make_unique<M90::Assert::Assert>());
    utilities.SetStringUtilities(
        std::make_unique<M90::String::StringUtilities>(utilities.GetAssert()));
}

void Builder::BuildDomainModelsContext(
    M90::Assert::IAssert& assert,
    M90::Algorithm::IAlgorithm& algorithm)
{
    GetContext().GetDomainModels().Set(
        std::make_unique<Lcd2004>(assert),
        std::make_unique<Tm1637>(),
        std::make_unique<Tm1637>(),
        std::make_unique<Tm1637>(),
        std::make_unique<IoPins>(assert),
        std::make_unique<LedStrips>(algorithm),
        std::make_unique<MicroSdCard>(),
        std::make_unique<I2sMicrophone>(),
        std::make_unique<I2sDac>(),
        std::make_unique<PassiveBuzzer>()
    );
}

void Builder::BuildDeviceModelsContext(
    M90::Assert::IAssert& assert,
    M90::String::IStringUtilities& stringUtilities)
{
    GetContext().GetDeviceModels().Set(
        std::make_unique<Lcd2004DeviceModel>(assert, stringUtilities),
        std::make_unique<Mcp23017DeviceModel>(assert, stringUtilities),
        std::make_unique<Tm1637DeviceModel>(assert, stringUtilities),
        std::make_unique<Tm1637DeviceModel>(assert, stringUtilities),
        std::make_unique<Tm1637DeviceModel>(assert, stringUtilities),
        std::make_unique<Ws28xxDeviceModel>(assert, stringUtilities),
        std::make_unique<MicroSdCardDeviceModel>(assert, stringUtilities),
        std::make_unique<AudioDeviceModel>(assert, stringUtilities),
        std::make_unique<Inmp1441DeviceModel>(assert, stringUtilities),
        std::make_unique<Max53987aDeviceModel>(assert, stringUtilities),
        std::make_unique<BuzzerDeviceModel>(assert, stringUtilities)
    );
}

void Builder::BuildDeviceDriversContext(
    M90::Assert::IAssert& assert,
    M90::String::IStringUtilities& stringUtilities)
{
    auto& deviceDriversContext = GetContext().GetDeviceDrivers();

    deviceDriversContext.SetI2cDeviceDriver(
        std::make_unique<M60::I2c::I2cDeviceDriver>(assert, stringUtilities));
    deviceDriversContext.SetSpiDeviceDriver(
        std::make_unique<M60::Spi::SpiDeviceDriver>(assert, stringUtilities));
    deviceDriversContext.SetLcd2004DeviceDriver(
        std::make_unique<M60::I2c::Lcd2004DeviceDriver>(assert, stringUtilities));
    deviceDriversContext.SetMcp23017DeviceDriver(
        std::make_unique<M60::I2c::Mcp23017DeviceDriver>(assert, stringUtilities));
    deviceDriversContext.SetTm1637CentralPanelDeviceDriver(
        std::make_unique<M60::I2c::Tm1637DeviceDriver>(assert, stringUtilities));
    deviceDriversContext.SetTm1637Player1DeviceDriver(
        std::make_unique<M60::I2c::Tm1637DeviceDriver>(assert, stringUtilities));
    deviceDriversContext.SetTm1637Player2DeviceDriver(
        std::make_unique<M60::I2c::Tm1637DeviceDriver>(assert, stringUtilities));
    deviceDriversContext.SetWs28xxDeviceDriver(
        std::make_unique<M60::Ws28xx::Ws28xxDeviceDriver>(assert, stringUtilities));
    deviceDriversContext.SetMicroSdCardDeviceDriver(
        std::make_unique<M60::Spi::MicroSdCardDeviceDriver>(assert, stringUtilities));
    deviceDriversContext.SetAudioDeviceDriver(
        std::make_unique<M60::Audio::AudioDeviceDriver>(assert, stringUtilities));
    deviceDriversContext.SetInmp1441DeviceDriver(
        std::make_unique<M60::Audio::Inmp1441DeviceDriver>(assert, stringUtilities));
    deviceDriversContext.SetMax53987aDeviceDriver(
        std::make_unique<M60::Audio::Max53987aDeviceDriver>(assert, stringUtilities));
    deviceDriversContext.SetBuzzerDeviceDriver(
        std::make_unique<M60::Audio::BuzzerDeviceDriver>(assert, stringUtilities));
}

void Builder::BuildQueuesContext(
    M90::Assert::IAssert& assert,
    M90::String::IStringUtilities& stringUtilities)
{
    auto i2cInputQueue = std::make_unique<I2cInputQueue>();
    auto i2cOutputQueue = std::make_unique<I2cOutputQueue>();
    auto spiInputQueue = std::make_unique<SpiInputQueue>();
    auto spiOutputQueue = std::make_unique<SpiOutputQueue>();
    auto ledStripsQueue = std::make_unique<LedStripsQueue>();
    auto diagnosticsQueue = std::make_unique<DiagnosticsQueue>();
    auto audioInputQueue = std::make_unique<AudioInputQueue>();
    auto audioOutputQueue = std::make_unique<AudioOutputQueue>();

    ServicesContext& servicesContext = GetContext().GetServices();
    auto* i2cInputRtosQueue  = servicesContext.GetRtos().CreateQueue(
        I2cInputQueue::MESSAGE_QUEUE_LENGTH, I2cInputQueue::MESSAGE_QUEUE_ITEM_SIZE);
    auto* i2cOutputRtosQueue = servicesContext.GetRtos().CreateQueue(
        I2cOutputQueue::MESSAGE_QUEUE_LENGTH, I2cOutputQueue::MESSAGE_QUEUE_ITEM_SIZE);
    auto* spiInputRtosQueue = servicesContext.GetRtos().CreateQueue(
        SpiInputQueue::MESSAGE_QUEUE_LENGTH, SpiInputQueue::MESSAGE_QUEUE_ITEM_SIZE);
    auto* spiOutputRtosQueue = servicesContext.GetRtos().CreateQueue(
        SpiOutputQueue::MESSAGE_QUEUE_LENGTH, SpiOutputQueue::MESSAGE_QUEUE_ITEM_SIZE);
    auto* ledStripsRtosQueue = servicesContext.GetRtos().CreateQueue(
        LedStripsQueue::MESSAGE_QUEUE_LENGTH, LedStripsQueue::MESSAGE_QUEUE_ITEM_SIZE);
    auto* diagnosticsRtosQueue = servicesContext.GetRtos().CreateQueue(
        DiagnosticsQueue::MESSAGE_QUEUE_LENGTH, DiagnosticsQueue::MESSAGE_QUEUE_ITEM_SIZE);
    auto* audioInputRtosQueue = servicesContext.GetRtos().CreateQueue(
        AudioInputQueue::MESSAGE_QUEUE_LENGTH, AudioInputQueue::MESSAGE_QUEUE_ITEM_SIZE);
    auto* audioOutputRtosQueue = servicesContext.GetRtos().CreateQueue(
        AudioOutputQueue::MESSAGE_QUEUE_LENGTH, AudioOutputQueue::MESSAGE_QUEUE_ITEM_SIZE);

    i2cInputQueue->SetRtosQueue(*i2cInputRtosQueue);
    i2cOutputQueue->SetRtosQueue(*i2cOutputRtosQueue);
    spiInputQueue->SetRtosQueue(*spiInputRtosQueue);
    spiOutputQueue->SetRtosQueue(*spiOutputRtosQueue);
    ledStripsQueue->SetRtosQueue(*ledStripsRtosQueue);
    diagnosticsQueue->SetRtosQueue(*diagnosticsRtosQueue);
    audioInputQueue->SetRtosQueue(*audioInputRtosQueue);
    audioOutputQueue->SetRtosQueue(*audioOutputRtosQueue);

    auto diagnosticsQueueWriter = std::make_unique<DiagnosticsQueueWriter>(
        *diagnosticsQueue, assert, stringUtilities);

    GetContext().GetQueues().Set(
        std::move(i2cInputQueue),
        std::move(i2cOutputQueue),
        std::move(spiInputQueue),
        std::move(spiOutputQueue),
        std::move(ledStripsQueue),
        std::move(diagnosticsQueue),
        std::move(diagnosticsQueueWriter),
        std::move(audioInputQueue),
        std::move(audioOutputQueue)
    );
}

void Builder::BuildTasksContext(
    M60::Ws28xx::Ws28xxDeviceDriver& ws28xxDeviceDriver,
    M60::I2c::Lcd2004DeviceDriver& lcd2004DeviceDriver,
    M60::I2c::Mcp23017DeviceDriver& mcp23017DeviceDriver,
    M60::I2c::Tm1637DeviceDriver& tm1637DeviceDriverCentralPanel,
    M60::I2c::Tm1637DeviceDriver& tm1637DeviceDriverPlayer1,
    M60::I2c::Tm1637DeviceDriver& tm1637DeviceDriverPlayer2,
    M80::Random::IRandom& random,
    M90::Assert::IAssert& assert,
    M90::String::IStringUtilities& stringUtilities)
{
    const char * APPLICATIONS_TASK_NAME = "Applications";
    const uint16_t APPLICATIONS_TASK_STACK_SIZE = 16384;
    const uint8_t APPLICATIONS_TASK_PRIORITY = 3;
    const uint8_t APPLICATIONS_TASK_CORE = 1;

    const char * I2C_TASK_NAME = "I2C";
    const uint16_t I2C_TASK_STACK_SIZE = 4096;
    const uint8_t I2C_TASK_PRIORITY = 3;
    const uint8_t I2C_TASK_CORE = 1;

    const char * SPI_TASK_NAME = "SPI";
    const uint16_t SPI_TASK_STACK_SIZE = 4096;
    const uint8_t SPI_TASK_PRIORITY = 3;
    const uint8_t SPI_TASK_CORE = 1;

    const char * LED_STRIPS_TASK_NAME = "LedStrips";
    const uint16_t LED_STRIPS_TASK_STACK_SIZE = 4096;
    const uint8_t LED_STRIPS_TASK_PRIORITY = 3;
    const uint8_t LED_STRIPS_TASK_CORE = 1;

    const char * AUDIO_TASK_NAME = "Audio";
    const uint16_t AUDIO_TASK_STACK_SIZE = 4096;
    const uint8_t AUDIO_TASK_PRIORITY = 3;
    const uint8_t AUDIO_TASK_CORE = 1;

    const char * DIAGNOSTICS_TASK_NAME = "Diagnostics";
    const uint16_t DIAGNOSTICS_TASK_STACK_SIZE = 4096;
    const uint8_t DIAGNOSTICS_TASK_PRIORITY = 3;
    const uint8_t DIAGNOSTICS_TASK_CORE = 1;

    auto applicationsTask = std::make_unique<ApplicationsTask>(
        *_context, random, assert, stringUtilities);
    auto& applicationsTaskRef = *applicationsTask;
    
    // Declare 16KB stack, because NVS keeps arrays of favorites/nr of starts/last start times and 
    // checks against them.
    // This alone is twice: (4 + 2 + 1) * nr of applications.

    ServicesContext& servicesContext = GetContext().GetServices();
    M81::RtosTask::IRtosTask* applicationsRtosTask = servicesContext.GetRtos().CreateTask(
        ApplicationsTask::TaskEntry, 
        APPLICATIONS_TASK_NAME,
        APPLICATIONS_TASK_STACK_SIZE,
        APPLICATIONS_TASK_PRIORITY, // Priority
        APPLICATIONS_TASK_CORE, // Core
        applicationsTask.get(),
        assert); 
    applicationsTaskRef.SetRtosTask(*applicationsRtosTask);

    auto i2cTask = std::make_unique<I2cTask>(
        *_context, 
        lcd2004DeviceDriver,
        mcp23017DeviceDriver,
        tm1637DeviceDriverCentralPanel,
        tm1637DeviceDriverPlayer1,
        tm1637DeviceDriverPlayer2,
        assert, 
        stringUtilities);
    auto& i2cTaskRef = *i2cTask;
    M81::RtosTask::IRtosTask* i2cRtosTask = servicesContext.GetRtos().CreateTask(
        I2cTask::TaskEntry, 
        I2C_TASK_NAME,
        I2C_TASK_STACK_SIZE,
        I2C_TASK_PRIORITY,
        I2C_TASK_CORE,
        i2cTask.get(),
        assert); 
    i2cTaskRef.SetRtosTask(*i2cRtosTask);

    auto spiTask = std::make_unique<SpiTask>(*_context, assert, stringUtilities);
    auto& spiTaskRef = *spiTask;
    M81::RtosTask::IRtosTask* spiRtosTask = servicesContext.GetRtos().CreateTask(
        SpiTask::TaskEntry, 
        SPI_TASK_NAME,
        SPI_TASK_STACK_SIZE,
        SPI_TASK_PRIORITY,
        SPI_TASK_CORE,
        spiTask.get(),
        assert); 
    spiTaskRef.SetRtosTask(*spiRtosTask);

    auto ledStripsTask = std::make_unique<LedStripsTask>(
        *_context, ws28xxDeviceDriver, assert, stringUtilities);
    auto& ledStripsTaskRef = *ledStripsTask;
    M81::RtosTask::IRtosTask* ledStripsRtosTask = servicesContext.GetRtos().CreateTask(
        LedStripsTask::TaskEntry, 
        LED_STRIPS_TASK_NAME, 
        LED_STRIPS_TASK_STACK_SIZE,
        LED_STRIPS_TASK_PRIORITY,
        LED_STRIPS_TASK_CORE,
        ledStripsTask.get(),
        assert); 
    ledStripsTaskRef.SetRtosTask(*ledStripsRtosTask);

    auto diagnosticsTask = std::make_unique<DiagnosticsTask>(*_context, assert, stringUtilities);
    auto& diagnosticsTaskRef = *diagnosticsTask;
    M81::RtosTask::IRtosTask* diagnosticsRtosTask = servicesContext.GetRtos().CreateTask(
        DiagnosticsTask::TaskEntry, 
        DIAGNOSTICS_TASK_NAME,
        DIAGNOSTICS_TASK_STACK_SIZE,
        DIAGNOSTICS_TASK_PRIORITY,
        DIAGNOSTICS_TASK_CORE,
        diagnosticsTask.get(),
        assert); 
    diagnosticsTaskRef.SetRtosTask(*diagnosticsRtosTask);

    auto audioTask = std::make_unique<AudioTask>(*_context, assert, stringUtilities);
    auto& audioTaskRef = *audioTask;
    M81::RtosTask::IRtosTask* audioRtosTask = servicesContext.GetRtos().CreateTask(
        AudioTask::TaskEntry, 
        AUDIO_TASK_NAME,
        AUDIO_TASK_STACK_SIZE,
        AUDIO_TASK_PRIORITY,
        AUDIO_TASK_CORE,
        audioTask.get(),
        assert); 
    audioTaskRef.SetRtosTask(*audioRtosTask);

    GetContext().GetTasks().Set(
        std::move(applicationsTask),
        std::move(i2cTask),
        std::move(spiTask),
        std::move(ledStripsTask),
        std::move(diagnosticsTask),
        std::move(audioTask));
}
