#include "SevenSegmentsDisplaysTaskDeviceDriversDelegate.hpp"
#include "../../M50_DeviceModels/Tm1637/Tm1637DeviceModel.hpp"
#include "../../M60_DeviceDrivers/SevenSegmentsDisplays/Tm1637DeviceDriver.hpp"
#include "../../M90_Utilities/Assert/IAssert.hpp"
#include "../../M90_Utilities/Time/TimeUtilities.hpp"
#include <array>

namespace M60::SevenSegmentsDisplays
{
    SevenSegmentsDisplaysTaskDeviceDriversDelegate::
        SevenSegmentsDisplaysTaskDeviceDriversDelegate(
            Tm1637DeviceDriver& tm1637DeviceDriverCentralPanel,
            Tm1637DeviceDriver& tm1637DeviceDriverPlayer1,
            Tm1637DeviceDriver& tm1637DeviceDriverPlayer2,
            M90::Assert::IAssert& assert,
            M90::Log::ILog& log,
            M90::Time::ITimeUtilities& timeUtilities)
    : 
        TaskDeviceDriversDelegate(assert, log),
        _tm1637DeviceDriverCentralPanel(tm1637DeviceDriverCentralPanel),
        _tm1637DeviceDriverPlayer1(tm1637DeviceDriverPlayer1),
        _tm1637DeviceDriverPlayer2(tm1637DeviceDriverPlayer2),
        _assert(assert),
        _timeUtilities(timeUtilities),
        _lastTm1637WriteUs(0),
        _nextTm1637IdToUpdate(Types::ETm1637Id::CentralPanel)
    {
        // No functionality required.
    }

    void SevenSegmentsDisplaysTaskDeviceDriversDelegate::Initialize() // NOSONAR: no const
    {
        // No actions required.
    }


    void SevenSegmentsDisplaysTaskDeviceDriversDelegate::Run()
    {
        std::chrono::microseconds nowUs = _timeUtilities.GetCurrentTimeInUs();
        std::chrono::microseconds tm1637IntervalUs =
            _timeUtilities.FrequencyToIntervalUs(TM1637_WRITE_DISPLAY_FREQUENCY);
        
        if (nowUs - _lastTm1637WriteUs >= tm1637IntervalUs)
        {

            auto& deviceDriver = GetTm1637DeviceDriverId(_nextTm1637IdToUpdate);
            deviceDriver.SendToDisplay();
            _nextTm1637IdToUpdate =
                static_cast<Types::ETm1637Id>((static_cast<uint8_t>(_nextTm1637IdToUpdate) + 1) % 3);
            _lastTm1637WriteUs = nowUs;
        }
    }

    M60::SevenSegmentsDisplays::Tm1637DeviceDriver& 
        SevenSegmentsDisplaysTaskDeviceDriversDelegate::GetTm1637DeviceDriverId(
            Types::ETm1637Id tm1637id)
    {
        using enum Types::ETm1637Id;

        M60::SevenSegmentsDisplays::Tm1637DeviceDriver* deviceDriver = nullptr;

        switch (tm1637id)
        {
        case CentralPanel: 
            deviceDriver = &_tm1637DeviceDriverCentralPanel;
            break;

        case Player1:  
            deviceDriver = &_tm1637DeviceDriverPlayer1;
            break;

        case Player2:    
            deviceDriver = &_tm1637DeviceDriverPlayer2;
            break;

        default:
            _assert.Fail(Types::ETaskId::System, "Illegal TM1637 ID");
        }

        return *deviceDriver;
    }
}
