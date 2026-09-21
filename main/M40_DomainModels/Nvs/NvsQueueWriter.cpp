#include "NvsQueueWriter.hpp"
#include "../../M80_Services/Nvs/Nvs.hpp"
#include "../../M90_Utilities/Assert/Assert.hpp"
#include <string.h>

NvsQueueWriter::NvsQueueWriter(
    NvsQueue& nvsQueue,
    Nvs& nvs)
: QueueProcessor(),
  _nvsQueue(nvsQueue),
  _nvs(nvs)
{
    SetQueue(_nvsQueue);
}

bool NvsQueueWriter::ProcessMessage(
    void* message)
{
    auto* nvsMessage = static_cast<NvsQueue::Message*>(message);
    
    switch (nvsMessage->type)
    {
        case NvsQueue::Message::EType::WriteString:
        {
            bool result = _nvs.WriteString(
                nvsMessage->writeString.partition,
                nvsMessage->writeString.namespaceName,
                nvsMessage->writeString.key,
                nvsMessage->writeString.value);
            nvsMessage->result = result;
            return true;
        }

        case NvsQueue::Message::EType::WriteUint8:
        {
            bool result = _nvs.WriteUint8(
                nvsMessage->writeUint8.partition,
                nvsMessage->writeUint8.namespaceName,
                nvsMessage->writeUint8.key,
                nvsMessage->writeUint8.value);
            nvsMessage->result = result;
            return true;
        }

        case NvsQueue::Message::EType::WriteUint16:
        {
            bool result = _nvs.WriteUint16(
                nvsMessage->writeUint16.partition,
                nvsMessage->writeUint16.namespaceName,
                nvsMessage->writeUint16.key,
                nvsMessage->writeUint16.value);
            nvsMessage->result = result;
            return true;
        }

        case NvsQueue::Message::EType::WriteUint32:
        {
            bool result = _nvs.WriteUint32(
                nvsMessage->writeUint32.partition,
                nvsMessage->writeUint32.namespaceName,
                nvsMessage->writeUint32.key,
                nvsMessage->writeUint32.value);
            nvsMessage->result = result;
            return true;
        }

        case NvsQueue::Message::EType::WriteBlob:
        {
            bool result = _nvs.WriteBlob(
                nvsMessage->writeBlob.partition,
                nvsMessage->writeBlob.namespaceName,
                nvsMessage->writeBlob.key,
                nvsMessage->writeBlob.data,
                nvsMessage->writeBlob.length);
            nvsMessage->result = result;
            return true;
        }

        case NvsQueue::Message::EType::EraseKey:
        {
            bool result = _nvs.EraseKey(
                nvsMessage->eraseKey.partition,
                nvsMessage->eraseKey.namespaceName,
                nvsMessage->eraseKey.key);
            nvsMessage->result = result;
            return true;
        }

        case NvsQueue::Message::EType::EraseNamespace:
        {
            bool result = _nvs.EraseNamespace(
                nvsMessage->eraseNamespace.partition,
                nvsMessage->eraseNamespace.namespaceName);
            nvsMessage->result = result;
            return true;
        }

        default:
            return false;
    }
}
