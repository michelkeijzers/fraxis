#pragma once

#include "../../M30_Messages/QueueProcessor.hpp"
#include "../../M30_Messages/Types.hpp"
#include "../../M40_DomainModels/I2s/I2sDac/I2sDac.hpp"
#include "../../M40_DomainModels/I2s/I2sMicrophone/I2sMicrophone.hpp"
#include "../../M60_DeviceDrivers/I2s/Inmp1441/Inmp1441DeviceDriver.hpp"
#include "../../M60_DeviceDrivers/I2s/Max53987a/Max53987aDeviceDriver.hpp"
#include <cstdint>
#include <string>
#include <array>

namespace M90::Assert
{
    class IAssert;
}

namespace M90::String
{
    class IStringUtilities;
}

class I2sOutputQueue;
class ApplicationsManager;

class I2sOutputQueueWriter : public QueueProcessor
{
public:
    I2sOutputQueueWriter(
        M90::Assert::IAssert& assert,
        M90::Log::ILog& log,
        M90::String::IStringUtilities& stringUtilities,
        I2sOutputQueue& i2sOutputQueue,
        ApplicationsManager& applicationsManager);

    I2sOutputQueueWriter(
        const I2sOutputQueueWriter&) = delete;

    I2sOutputQueueWriter& operator=(
        const I2sOutputQueueWriter&) = delete;

    I2sOutputQueueWriter(
        I2sOutputQueueWriter&&) = delete;

    I2sOutputQueueWriter& operator=(
        I2sOutputQueueWriter&&) = delete;

    ~I2sOutputQueueWriter() override = default;

private:
    I2sOutputQueue& GetI2sOutputQueue();

    ApplicationsManager& _applicationsManager;
};
