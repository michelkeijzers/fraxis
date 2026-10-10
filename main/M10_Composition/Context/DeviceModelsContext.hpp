#pragma once

#include <memory>

// Forward declarations of device models
class Lcd2004DeviceModel;
class Mcp23017DeviceModel;
class Tm1637DeviceModel;
class Ws28xxDeviceModel;
class MicroSdCardDeviceModel;
class AudioDeviceModel;
class MicrophoneDeviceModel;
class DacDeviceModel;
class BuzzerDeviceModel;

class DeviceModelsContext
{
public:
    DeviceModelsContext();
    ~DeviceModelsContext();

    void Set(
        std::unique_ptr<Lcd2004DeviceModel> lcd2004DeviceModel,
        std::unique_ptr<Mcp23017DeviceModel> mcp23017DeviceModel,
        std::unique_ptr<Tm1637DeviceModel> tm1637DeviceModelCentralPanel,
        std::unique_ptr<Tm1637DeviceModel> tm1637DeviceModelPlayer1,
        std::unique_ptr<Tm1637DeviceModel> tm1637DeviceModelPlayer2,
        std::unique_ptr<Ws28xxDeviceModel> ws28xxDeviceModel,
        std::unique_ptr<MicroSdCardDeviceModel> microSdCardDeviceModel,
        std::unique_ptr<AudioDeviceModel> audioDeviceModel,
        std::unique_ptr<MicrophoneDeviceModel> microphoneDeviceModel,
        std::unique_ptr<DacDeviceModel> dacDeviceModel,
        std::unique_ptr<BuzzerDeviceModel> buzzerDeviceModel
    );

    Lcd2004DeviceModel& GetLcd2004DeviceModel();
    Mcp23017DeviceModel& GetMcp23017DeviceModel();
    Tm1637DeviceModel& GetTm1637DeviceModelCentralPanel();
    Tm1637DeviceModel& GetTm1637DeviceModelPlayer1();
    Tm1637DeviceModel& GetTm1637DeviceModelPlayer2();
    Ws28xxDeviceModel& GetWs28xxDeviceModel();
    MicroSdCardDeviceModel& GetMicroSdCardDeviceModel();
    AudioDeviceModel& GetAudioDeviceModel();
    MicrophoneDeviceModel& GetMicrophoneDeviceModel();
    DacDeviceModel& GetDacDeviceModel();
    BuzzerDeviceModel& GetBuzzerDeviceModel();

private:
    std::unique_ptr<Lcd2004DeviceModel> _lcd2004DeviceModel;
    std::unique_ptr<Mcp23017DeviceModel> _mcp23017DeviceModel;
    std::unique_ptr<Tm1637DeviceModel> _tm1637DeviceModelCentralPanel;
    std::unique_ptr<Tm1637DeviceModel> _tm1637DeviceModelPlayer1;
    std::unique_ptr<Tm1637DeviceModel> _tm1637DeviceModelPlayer2;
    std::unique_ptr<Ws28xxDeviceModel> _ws28xxDeviceModel;
    std::unique_ptr<MicroSdCardDeviceModel> _microSdCardDeviceModel;
    std::unique_ptr<AudioDeviceModel> _audioDeviceModel;
    std::unique_ptr<MicrophoneDeviceModel> _microphoneDeviceModel;
    std::unique_ptr<DacDeviceModel> _dacDeviceModel;
    std::unique_ptr<BuzzerDeviceModel> _buzzerDeviceModel;
};
