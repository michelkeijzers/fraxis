#include "NvsQueueReader.hpp"
#include "../../M30_Messages/NvsQueue.hpp"
#include "../../M80_Services/Nvs/Nvs.hpp"
#include "../../M90_Utilities/Assert/Assert.hpp"
#include "../../M90_Utilities/String/StringUtilities.hpp"
#include <string.h>

NvsQueueReader::NvsQueueReader(
    NvsQueue& nvsQueue,
    Nvs& nvs)
: 
    QueueProcessor(),
    _nvsQueue(nvsQueue),
    _nvs(nvs)
{
    SetQueue(_nvsQueue);
}

NvsQueue& NvsQueueReader::GetNvsQueue()
{
    return static_cast<NvsQueue&>(GetQueue());
}

bool NvsQueueReader::HandleMessage()
{
    bool handled = false;

    NvsQueue::Message message = {};
    auto& queue = GetNvsQueue();
    if (auto& rtosQueue = queue.GetRtosQueue(); rtosQueue.Receive(&message, 0))
    {
        switch (message.type)
        {
        case NvsQueue::Message::EType::ReadString:
        {
            std::string value;
            bool result = _nvs.ReadString(
                message.readString.partition,
                message.readString.namespaceName,
                message.readString.key,
                value);
            message.result = result;
            if (result)
            {
                StringUtilities::CopyToBuffer(value, message.stringValue, sizeof(message.stringValue) - 1);
                message.stringValue[sizeof(message.stringValue) - 1] = '\0';
            }
            else
            {
                message.stringValue[0] = '\0';
            }
            return true;
        }

        case NvsQueue::Message::EType::ReadUint8:
        {
            uint8_t value;
            bool result = _nvs.ReadUint8(
                message.readUint8.partition,
                message.readUint8.namespaceName,
                message.readUint8.key,
                value);
            message.result = result;
            message.uint8Value = value;
            return true;
        }

        case NvsQueue::Message::EType::ReadUint16:
        {
            uint16_t value;
            bool result = _nvs.ReadUint16(
                message.readUint16.partition,
                message.readUint16.namespaceName,
                message.readUint16.key,
                value);
            message.result = result;
            message.uint16Value = value;
            return true;
        }

        case NvsQueue::Message::EType::ReadUint32:
        {
            uint32_t value;
            bool result = _nvs.ReadUint32(
                message.readUint32.partition,
                message.readUint32.namespaceName,
                message.readUint32.key,
                value);
            message.result = result;
            message.uint32Value = value;
            return true;
        }

        case NvsQueue::Message::EType::ReadBlob:
        {
            uint8_t data[64];
            size_t length = message.readBlob.maxLength;
            bool result = _nvs.ReadBlob(
                message.readBlob.partition,
                message.readBlob.namespaceName,
                message.readBlob.key,
                data,
                length);
            message.result = result;
            if (result)
            {
                message.blobValue.length = static_cast<uint16_t>(length);
                memcpy(message.blobValue.data, data, length);
            }
            else
            {
                message.blobValue.length = 0;
            }
            return true;
        }

        default:
            return false;
        }
    }
    
    return handled;
}
