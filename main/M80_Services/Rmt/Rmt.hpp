
#pragma once

#include <cstdint>
#include <stddef.h>

class Rmt
{
public:
    Rmt();

    Rmt(const Rmt&) = delete;
    Rmt& operator=(const Rmt&) = delete;
    Rmt(Rmt&&) = delete;
    Rmt& operator=(Rmt&&) = delete;

    virtual ~Rmt();

    virtual bool DelEncoder() = 0;

    virtual bool DelChannel() = 0;
    
    virtual bool NewTxChannel(
        uint8_t pin) = 0;

    virtual bool Enable() = 0;

    virtual bool NewSimpleEncoder() = 0;

    virtual bool Transmit(
        const void* payload,
        size_t payload_bytes) = 0;

        virtual bool TxWaitAllDone() = 0;
};
