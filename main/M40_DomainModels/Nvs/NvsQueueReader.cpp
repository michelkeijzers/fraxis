#include "NvsQueueReader.hpp"
#include "../../M80_Services/Nvs/Nvs.hpp"
#include "../../M90_Utilities/Assert/Assert.hpp"
#include <string.h>

NvsQueueReader::NvsQueueReader(
    NvsQueue& nvsQueue,
    Nvs& nvs)
: QueueProcessor(),
  _nvsQueue(nvsQueue),
  _nvs(nvs)
{
    SetQueue(_nvsQueue);
}

bool NvsQueueReader::ProcessMessage(
    void* message)
{
    auto* nvsMessage = static_cast<NvsQueue::Message*>(message);
    
    switch (nvsMessage->type)
    {
        case NvsQueue::Message::EType::ReadString:
        {
            std::string value;
            bool result = _nvs.ReadString(
                nvsMessage->readString.partition,
                nvsMessage->readString.namespaceName,
                nvsMessage->readString.key,
                value);
            nvsMessage->result = result;
            if (result)
            {
                strncpy(nvsMessage->stringValue, value.c_str(), sizeof(nvsMessage->stringValue) - 1);
                nvsMessage->stringValue[sizeof(nvsMessage->stringValue) - 1] = '\0';
            }
            else
            {
                nvsMessage->stringValue[0] = '\0';
            }
            return true;
        }

        case NvsQueue::Message::EType::ReadUint8:
        {
            uint8_t value;
            bool result = _nvs.ReadUint8(
                nvsMessage->readUint8.partition,
                nvsMessage->readUint8.namespaceName,
                nvsMessage->readUint8.key,
                value);
            nvsMessage->result = result;
            nvsMessage->uint8Value = value;
            return true;
        }

        case NvsQueue::Message::EType::ReadUint16:
        {
            uint16_t value;
            bool result = _nvs.ReadUint16(
                nvsMessage->readUint16.partition,
                nvsMessage->readUint16.namespaceName,
                nvsMessage->readUint16.key,
                value);
            nvsMessage->result = result;
            nvsMessage->uint16Value = value;
            return true;
        }

        case NvsQueue::Message::EType::ReadUint32:
        {
            uint32_t value;
            bool result = _nvs.ReadUint32(
                nvsMessage->readUint32.partition,
                nvsMessage->readUint32.namespaceName,
                nvsMessage->readUint32.key,
                value);
            nvsMessage->result = result;
            nvsMessage->uint32Value = value;
            return true;
        }

        case NvsQueue::Message::EType::ReadBlob:
        {
            uint8_t data[64];
            size_t length = nvsMessage->readBlob.maxLength;
            bool result = _nvs.ReadBlob(
                nvsMessage->readBlob.partition,
                nvsMessage->readBlob.namespaceName,
                nvsMessage->readBlob.key,
                data,
                length);
            nvsMessage->result = result;
            if (result)
            {
                nvsMessage->blobValue.length = static_cast<uint16_t>(length);
                memcpy(nvsMessage->blobValue.data, data, length);
            }
            else
            {
                nvsMessage->blobValue.length = 0;
            }
            return true;
        }

        default:
            return false;
    }
}
