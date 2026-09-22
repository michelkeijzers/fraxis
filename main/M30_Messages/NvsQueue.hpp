#pragma once

#include "Queue.hpp"
#include "../M81_RtosServices/RtosQueue/RtosQueue.hpp"

class NvsQueue : public Queue
{
public:
    NvsQueue();
    ~NvsQueue();

    struct Message
    {
        enum class EType
        {
            WriteString,
            ReadString,
            WriteUint8,
            ReadUint8,
            WriteUint16,
            ReadUint16,
            WriteUint32,
            ReadUint32,
            WriteBlob,
            ReadBlob,
            EraseKey,
            EraseNamespace
        };

        EType type;

        union
        {
            struct
            {
                char partition[32];
                char namespaceName[32];
                char key[32];
                char value[256];
            } writeString;

            struct
            {
                char partition[32];
                char namespaceName[32];
                char key[32];
            } readString;

            struct
            {
                char partition[32];
                char namespaceName[32];
                char key[32];
                uint8_t value;
            } writeUint8;

            struct
            {
                char partition[32];
                char namespaceName[32];
                char key[32];
            } readUint8;

            struct
            {
                char partition[32];
                char namespaceName[32];
                char key[32];
                uint16_t value;
            } writeUint16;

            struct
            {
                char partition[32];
                char namespaceName[32];
                char key[32];
            } readUint16;

            struct
            {
                char partition[32];
                char namespaceName[32];
                char key[32];
                uint32_t value;
            } writeUint32;

            struct
            {
                char partition[32];
                char namespaceName[32];
                char key[32];
            } readUint32;

            struct
            {
                char partition[32];
                char namespaceName[32];
                char key[32];
                uint8_t data[64];
                uint16_t length;
            } writeBlob;

            struct
            {
                char partition[32];
                char namespaceName[32];
                char key[32];
                uint16_t maxLength;
            } readBlob;

            struct
            {
                char partition[32];
                char namespaceName[32];
                char key[32];
            } eraseKey;

            struct
            {
                char partition[32];
                char namespaceName[32];
            } eraseNamespace;
        };

        bool result;
        union
        {
            char stringValue[256];
            uint8_t uint8Value;
            uint16_t uint16Value;
            uint32_t uint32Value;
            struct
            {
                uint8_t data[64];
                uint16_t length;
            } blobValue;
        };
    };

    constexpr static uint32_t MESSAGE_QUEUE_LENGTH = 25;
    constexpr static uint32_t MESSAGE_QUEUE_ITEM_SIZE = sizeof(Message);
};
