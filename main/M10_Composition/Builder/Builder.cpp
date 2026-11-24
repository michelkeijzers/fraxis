#include "Builder.hpp"
#include "TasksBuilder.hpp"
#include "../../M00_System/Tasks/DiagnosticsTask.hpp"
#include "../../M00_System/Tasks/I2cTask.hpp"
#include "../../M00_System/Tasks/I2sTask.hpp"
#include "../../M00_System/Tasks/LedStripsTask.hpp"
#include "../../M00_System/Tasks/PassiveBuzzerTask.hpp"
#include "../../M00_System/Tasks/SevenSegmentsDisplaysTask.hpp"
#include "../../M00_System/Tasks/SpiTask.hpp"
#include "../../M00_System/Queues/DiagnosticsQueueWriter.hpp"
#include "../../M20_Applications/ApplicationsTask.hpp"
#include "../../M30_Messages/Diagnostics/DiagnosticsQueue.hpp"
#include "../../M30_Messages/I2c/I2cInputQueue.hpp"
#include "../../M30_Messages/I2c/I2cOutputQueue.hpp"
#include "../../M30_Messages/LedStrips/LedStripsQueue.hpp"
#include "../../M30_Messages/Spi/SpiInputQueue.hpp"
#include "../../M30_Messages/Spi/SpiOutputQueue.hpp"
#include "../../M30_Messages/I2s/I2sInputQueue.hpp"
#include "../../M30_Messages/I2s/I2sOutputQueue.hpp"
#include "../../M30_Messages/PassiveBuzzer/PassiveBuzzerQueue.hpp"
#include "../../M30_Messages/SevenSegmentsDisplays/SevenSegmentsDisplaysQueue.hpp"
#include "../../M40_DomainModels/SevenSegmentsDisplays/Tm1637.hpp"
#include "../../M40_DomainModels/I2c/IoPins/IoPins.hpp"
#include "../../M40_DomainModels/LedStrips/LedStrips.hpp"
#include "../../M40_DomainModels/Spi/MicroSdCard/MicroSdCard.hpp"
#include "../../M40_DomainModels/I2s/I2sMicrophone/I2sMicrophone.hpp"
#include "../../M40_DomainModels/I2s/I2sDac/I2sDac.hpp"
#include "../../M40_DomainModels/PassiveBuzzer/PassiveBuzzer.hpp"
#include "../../M40_DomainModels/SevenSegmentsDisplays/Tm1637.hpp"
#include "../../M50_DeviceModels/Lcd2004/Lcd2004DeviceModel.hpp"
#include "../../M50_DeviceModels/Mcp23017/Mcp23017DeviceModel.hpp"
#include "../../M50_DeviceModels/Tm1637/Tm1637DeviceModel.hpp"
#include "../../M50_DeviceModels/Ws28xx/Ws28xxDeviceModel.hpp"
#include "../../M50_DeviceModels/MicroSdCard/MicroSdCardDeviceModel.hpp"
#include "../../M50_DeviceModels/I2s/I2sDeviceModel.hpp"
#include "../../M50_DeviceModels/I2s/Inmp1441/Inmp1441DeviceModel.hpp"
#include "../../M50_DeviceModels/I2s/Max53987a/Max53987aDeviceModel.hpp"
#include "../../M50_DeviceModels/PassiveBuzzer/PassiveBuzzerDeviceModel.hpp"
#include "../../M60_DeviceDrivers/Ws28xx/Ws2812Rmt.hpp"
#include "../../M50_DeviceModels/Tm1637/Tm1637DeviceModel.hpp"
#include "../../M81_RtosServices/Rtos/Rtos.hpp"
#include "../../M81_RtosServices/RtosTask/RtosTask.hpp"
#include "../../M90_Utilities/Algorithm/Algorithm.hpp"
#include "../../M90_Utilities/Assert/Assert.hpp"
#include "../../M90_Utilities/Container/ContainerUtilities.hpp"
#include "../../M90_Utilities/Log/Log.hpp"
#include "../../M90_Utilities/String/StringUtilities.hpp"
#include "../../M90_Utilities/Time/TimeUtilities.hpp"
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

    namespace Container
    {
        class IContainerUtilities;
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
    M90::Container::IContainerUtilities& containerUtilities = utilities.GetContainerUtilities();
    M90::Log::ILog& log = utilities.GetLog();
    M90::Math::IMathUtilities& mathUtilities = utilities.GetMathUtilities();
    M90::String::IStringUtilities& stringUtilities = utilities.GetStringUtilities();
    M90::Time::ITimeUtilities& timeUtilities = utilities.GetTimeUtilities();

    BuildServicesContext();

    auto& servicesContext = GetContext().GetServices();
    M80::Random::IRandom& random = servicesContext.GetRandom();

    BuildDeviceDriversContext(assert, stringUtilities);

    auto& deviceDriversContext = GetContext().GetDeviceDrivers();
    M60::Ws28xx::IWs28xxDeviceDriver& ws28xxDeviceDriver =
        deviceDriversContext.GetSpecificTypedWs28xxDeviceDriver();
    M60::I2c::Lcd2004DeviceDriver& lcd2004DeviceDriver = 
        deviceDriversContext.GetLcd2004DeviceDriver();
    M60::I2c::Mcp23017DeviceDriver& mcp23017DeviceDriver =
        deviceDriversContext.GetMcp23017DeviceDriver();
    M60::SevenSegmentsDisplays::Tm1637DeviceDriver& tm1637DeviceDriverCentralPanel =
        deviceDriversContext.GetTm1637DeviceDriverCentralPanel();
    M60::SevenSegmentsDisplays::Tm1637DeviceDriver& tm1637DeviceDriverPlayer1 =
        deviceDriversContext.GetTm1637DeviceDriverPlayer1();
    M60::SevenSegmentsDisplays::Tm1637DeviceDriver& tm1637DeviceDriverPlayer2 =
        deviceDriversContext.GetTm1637DeviceDriverPlayer2();

    BuildDeviceModelsContext(assert, log, containerUtilities, stringUtilities);

    BuildDomainModelsContext(assert, log, algorithm);

    BuildQueuesContext(assert, log, stringUtilities);

    BuildTasksContext(
        ws28xxDeviceDriver,
        lcd2004DeviceDriver,
        mcp23017DeviceDriver,
        tm1637DeviceDriverCentralPanel,
        tm1637DeviceDriverPlayer1,
        tm1637DeviceDriverPlayer2,
        random,
        assert,
        containerUtilities,
        log,
        mathUtilities,
        stringUtilities,
        timeUtilities);
}

void Builder::BuildUtilitiesContext()
{
    auto& utilities = GetContext().GetUtilities();
    utilities.SetAlgorithm(
        std::make_unique<M90::Algorithm::Algorithm>());

    // TimeUtilities needs to be made before Log as it is an input parameter for Assert.
    utilities.SetTimeUtilities(
        std::make_unique<M90::Time::TimeUtilities>());

    // Log needs to be made before Assert as it is an input parameter for Assert.
    utilities.SetLog(
        std::make_unique<M90::Log::Log>(utilities.GetTimeUtilities()));
    utilities.SetAssert(
        std::make_unique<M90::Assert::Assert>(utilities.GetLog()));

    utilities.SetContainerUtilities(
        std::make_unique<M90::Container::ContainerUtilities>());
    utilities.SetStringUtilities(
        std::make_unique<M90::String::StringUtilities>(utilities.GetAssert()));
}

void Builder::BuildDomainModelsContext(
    M90::Assert::IAssert& assert,
    M90::Log::ILog& log,
    M90::Algorithm::IAlgorithm& algorithm)
{
    GetContext().GetDomainModels().Set(
        std::make_unique<Lcd2004>(assert, log),
        std::make_unique<Tm1637>(assert, log), // Central Panel
        std::make_unique<Tm1637>(assert, log), // Player 1
        std::make_unique<Tm1637>(assert, log), // Player 2
        std::make_unique<IoPins>(assert, log),
        std::make_unique<LedStrips>(assert, log, algorithm),
        std::make_unique<MicroSdCard>(assert, log),
        std::make_unique<I2sMicrophone>(assert, log),
        std::make_unique<I2sDac>(assert, log),
        std::make_unique<PassiveBuzzer>(assert, log));
}

void Builder::BuildDeviceModelsContext(
    M90::Assert::IAssert& assert,
    M90::Log::ILog& log,
    M90::Container::IContainerUtilities& containerUtilities,
    M90::String::IStringUtilities& stringUtilities)
{
    GetContext().GetDeviceModels().Set(
        std::make_unique<Lcd2004DeviceModel>(assert, log, containerUtilities, stringUtilities),
        std::make_unique<Mcp23017DeviceModel>(assert, log, stringUtilities),
        std::make_unique<Tm1637DeviceModel>(assert, log, stringUtilities),
        std::make_unique<Tm1637DeviceModel>(assert, log, stringUtilities),
        std::make_unique<Tm1637DeviceModel>(assert, log, stringUtilities),
        std::make_unique<Ws28xxDeviceModel>(assert, log, stringUtilities),
        std::make_unique<MicroSdCardDeviceModel>(assert, log, stringUtilities),
        std::make_unique<I2sDeviceModel>(assert, log, stringUtilities),
        std::make_unique<Inmp1441DeviceModel>(assert, log, stringUtilities),
        std::make_unique<Max53987aDeviceModel>(assert, log, stringUtilities),
        std::make_unique<PassiveBuzzerDeviceModel>(assert, log, stringUtilities));
}

void Builder::BuildDeviceDriversContext(
    M90::Assert::IAssert& assert,
    M90::String::IStringUtilities& stringUtilities)
{
    auto& deviceDriversContext = GetContext().GetDeviceDrivers();

    // I2C.
    deviceDriversContext.SetI2cDeviceDriver(
        std::make_unique<M60::I2c::I2cDeviceDriver>(
            DeviceSettings::I2C_PORT, 
            DeviceSettings::PIN_I2C_SDA,
            DeviceSettings::PIN_I2C_SCL,
            DeviceSettings::I2C_FREQUENCY,
            GetContext().GetServices().GetI2c(),
            assert,
            stringUtilities));

    auto& i2cDeviceDriver = GetContext().GetDeviceDrivers().GetI2cDeviceDriver();
    deviceDriversContext.SetLcd2004DeviceDriver(
        std::make_unique<M60::I2c::Lcd2004DeviceDriver>(
            i2cDeviceDriver,
            assert, 
            stringUtilities));

    deviceDriversContext.SetMcp23017DeviceDriver(
        std::make_unique<M60::I2c::Mcp23017DeviceDriver>(
            i2cDeviceDriver,
            true,
            DeviceSettings::PIN_MCP23017_INTERRUPT, 
            GetContext().GetServices().GetGpio(), 
            assert, 
            stringUtilities));

    // Seven Segments Displays.
    M80::Gpio::IGpio& gpio = GetContext().GetServices().GetGpio();
    deviceDriversContext.SetTm1637CentralPanelDeviceDriver(
        std::make_unique<M60::SevenSegmentsDisplays::Tm1637DeviceDriver>(
            DeviceSettings::PIN_TM1637_CENTRAL_PANEL_DATA, 
            DeviceSettings::PIN_TM1637_CLOCK,
            gpio, 
            assert,
            stringUtilities));
    
    deviceDriversContext.SetTm1637Player1DeviceDriver(
        std::make_unique<M60::SevenSegmentsDisplays::Tm1637DeviceDriver>(
            DeviceSettings::PIN_TM1637_PLAYER_1_DATA,
            DeviceSettings::PIN_TM1637_CLOCK,
            gpio,
            assert,
            stringUtilities));
    
    deviceDriversContext.SetTm1637Player2DeviceDriver(
        std::make_unique<M60::SevenSegmentsDisplays::Tm1637DeviceDriver>(
            DeviceSettings::PIN_TM1637_PLAYER_2_DATA,
            DeviceSettings::PIN_TM1637_CLOCK,
            gpio,
            assert,
            stringUtilities));

    // WS28xx.
    uint16_t numberOfLeds = LedStrips::NUMBER_OF_LEDS;
    
    deviceDriversContext.SetWs2812Rmt(
        std::make_unique<M60::Ws28xx::Ws2812Rmt>(
            assert,
            DeviceSettings::PIN_WS2812_DATA,
            numberOfLeds,
            GetContext().GetServices().GetRmt()));
    
    deviceDriversContext.SetWs28xxDeviceDriver(
        std::make_unique<M60::Ws28xx::Ws28xxDeviceDriver>(
            numberOfLeds, 
            GetContext().GetDeviceDrivers().GetWs2812Rmt(),
            assert,
            stringUtilities));

    // SPI.
    deviceDriversContext.SetSpiDeviceDriver(
        std::make_unique<M60::Spi::SpiDeviceDriver>(
            DeviceSettings::SPI_PORT,
            DeviceSettings::SPI_MOSI_PIN,
            DeviceSettings::SPI_MISO_PIN,
            DeviceSettings::SPI_SCLK_PIN,
            DeviceSettings::SPI_FREQUENCY,
            GetContext().GetServices().GetSpi(),
            assert,
            stringUtilities));

    deviceDriversContext.SetMicroSdCardDeviceDriver(
        std::make_unique<M60::Spi::MicroSdCardDeviceDriver>(
            GetContext().GetDeviceDrivers().GetSpiDeviceDriver(),
            assert, 
            stringUtilities));
    
    // I2S.
    deviceDriversContext.SetI2sDeviceDriver(
        std::make_unique<M60::I2s::I2sDeviceDriver>(assert, stringUtilities));
    
    deviceDriversContext.SetInmp1441DeviceDriver(
        std::make_unique<M60::I2s::Inmp1441DeviceDriver>(assert, stringUtilities));
    
    deviceDriversContext.SetMax53987aDeviceDriver(
        std::make_unique<M60::I2s::Max53987aDeviceDriver>(assert, stringUtilities));
    
    // Passive buzzer.
    deviceDriversContext.SetPassiveBuzzerDeviceDriver(
        std::make_unique<M60::I2s::PassiveBuzzerDeviceDriver>(assert, stringUtilities));
}

void Builder::BuildQueuesContext(
    M90::Assert::IAssert& assert,
    M90::Log::ILog& log,
    M90::String::IStringUtilities& stringUtilities)
{
    auto i2cInputQueue = std::make_unique<I2cInputQueue>();
    auto i2cOutputQueue = std::make_unique<I2cOutputQueue>();
    auto spiInputQueue = std::make_unique<SpiInputQueue>();
    auto spiOutputQueue = std::make_unique<SpiOutputQueue>();
    auto ledStripsQueue = std::make_unique<LedStripsQueue>();
    auto diagnosticsQueue = std::make_unique<DiagnosticsQueue>();
    auto i2sInputQueue = std::make_unique<I2sInputQueue>();
    auto i2sOutputQueue = std::make_unique<I2sOutputQueue>();
    auto passiveBuzzerQueue = std::make_unique<PassiveBuzzerQueue>();
    auto sevenSegmentsDisplaysQueue = std::make_unique<SevenSegmentsDisplaysQueue>();

    ServicesContext& servicesContext = GetContext().GetServices();
    auto* i2cInputRtosQueue  = servicesContext.GetRtos().CreateQueue(
        I2cInputQueue::MESSAGE_QUEUE_LENGTH,
        I2cInputQueue::MESSAGE_QUEUE_ITEM_SIZE);
    auto* i2cOutputRtosQueue = servicesContext.GetRtos().CreateQueue(
        I2cOutputQueue::MESSAGE_QUEUE_LENGTH, 
        I2cOutputQueue::MESSAGE_QUEUE_ITEM_SIZE);
    auto* spiInputRtosQueue = servicesContext.GetRtos().CreateQueue(
        SpiInputQueue::MESSAGE_QUEUE_LENGTH, 
        SpiInputQueue::MESSAGE_QUEUE_ITEM_SIZE);
    auto* spiOutputRtosQueue = servicesContext.GetRtos().CreateQueue(
        SpiOutputQueue::MESSAGE_QUEUE_LENGTH, 
        SpiOutputQueue::MESSAGE_QUEUE_ITEM_SIZE);
    auto* ledStripsRtosQueue = servicesContext.GetRtos().CreateQueue(
        LedStripsQueue::MESSAGE_QUEUE_LENGTH, 
        LedStripsQueue::MESSAGE_QUEUE_ITEM_SIZE);
    auto* diagnosticsRtosQueue = servicesContext.GetRtos().CreateQueue(
        DiagnosticsQueue::MESSAGE_QUEUE_LENGTH,
        DiagnosticsQueue::MESSAGE_QUEUE_ITEM_SIZE);
    auto* i2sInputRtosQueue = servicesContext.GetRtos().CreateQueue(
        I2sInputQueue::MESSAGE_QUEUE_LENGTH, 
        I2sInputQueue::MESSAGE_QUEUE_ITEM_SIZE);
    auto* i2sOutputRtosQueue = servicesContext.GetRtos().CreateQueue(
        I2sOutputQueue::MESSAGE_QUEUE_LENGTH, 
        I2sOutputQueue::MESSAGE_QUEUE_ITEM_SIZE);
    auto* passiveBuzzerRtosQueue = servicesContext.GetRtos().CreateQueue(
        I2sOutputQueue::MESSAGE_QUEUE_LENGTH, 
        PassiveBuzzerQueue::MESSAGE_QUEUE_ITEM_SIZE);
    auto* sevenSegmentsDisplaysRtosQueue = servicesContext.GetRtos().CreateQueue(
        I2sOutputQueue::MESSAGE_QUEUE_LENGTH, 
        SevenSegmentsDisplaysQueue::MESSAGE_QUEUE_ITEM_SIZE);

    i2cInputQueue->SetRtosQueue(*i2cInputRtosQueue);
    i2cOutputQueue->SetRtosQueue(*i2cOutputRtosQueue);
    spiInputQueue->SetRtosQueue(*spiInputRtosQueue);
    spiOutputQueue->SetRtosQueue(*spiOutputRtosQueue);
    ledStripsQueue->SetRtosQueue(*ledStripsRtosQueue);
    diagnosticsQueue->SetRtosQueue(*diagnosticsRtosQueue);
    i2sInputQueue->SetRtosQueue(*i2sInputRtosQueue);
    i2sOutputQueue->SetRtosQueue(*i2sOutputRtosQueue);
    passiveBuzzerQueue->SetRtosQueue(*passiveBuzzerRtosQueue);
    sevenSegmentsDisplaysQueue->SetRtosQueue(*sevenSegmentsDisplaysRtosQueue);

    auto diagnosticsQueueWriter = std::make_unique<DiagnosticsQueueWriter>(
        *diagnosticsQueue, assert, log, stringUtilities);

    GetContext().GetQueues().Set(
        std::move(i2cInputQueue),
        std::move(i2cOutputQueue),
        std::move(spiInputQueue),
        std::move(spiOutputQueue),
        std::move(ledStripsQueue),
        std::move(diagnosticsQueue),
        std::move(diagnosticsQueueWriter),
        std::move(i2sInputQueue),
        std::move(i2sOutputQueue),
        std::move(passiveBuzzerQueue),
        std::move(sevenSegmentsDisplaysQueue));
}

void Builder::BuildTasksContext(
    M60::Ws28xx::IWs28xxDeviceDriver& ws28xxDeviceDriver,
    M60::I2c::Lcd2004DeviceDriver& lcd2004DeviceDriver,
    M60::I2c::Mcp23017DeviceDriver& mcp23017DeviceDriver,
    M60::SevenSegmentsDisplays::Tm1637DeviceDriver& tm1637DeviceDriverCentralPanel,
    M60::SevenSegmentsDisplays::Tm1637DeviceDriver& tm1637DeviceDriverPlayer1,
    M60::SevenSegmentsDisplays::Tm1637DeviceDriver& tm1637DeviceDriverPlayer2,
    M80::Random::IRandom& random,
    M90::Assert::IAssert& assert,
    M90::Container::IContainerUtilities& containerUtilities,
    M90::Log::ILog& log,
    M90::Math::IMathUtilities& mathUtilities,
    M90::String::IStringUtilities& stringUtilities,
    M90::Time::ITimeUtilities& timeUtilities)
{
    TasksBuilder tasksBuilder(GetContext());
    tasksBuilder.BuildTasksContext(
        ws28xxDeviceDriver,
        lcd2004DeviceDriver,
        mcp23017DeviceDriver,
        tm1637DeviceDriverCentralPanel,
        tm1637DeviceDriverPlayer1,
        tm1637DeviceDriverPlayer2,
        random,
        assert,
        containerUtilities,
        log,
        mathUtilities,
        stringUtilities,
        timeUtilities);
}
