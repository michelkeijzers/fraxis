#ifdef ESP_PLATFORM

#pragma once

#include "Rmt.hpp"
#include "driver/rmt_tx.h"

class EspRmt : public Rmt
{
public:
    EspRmt();
    ~EspRmt();

private:
    bool DelEncoder() override;
    bool DelChannel() override;

    bool NewTxChannel(uint8_t pin) override;
    bool Enable() override;
    bool NewSimpleEncoder() override;

    bool Transmit(const void* payload, size_t payload_bytes) override;
    bool TxWaitAllDone() override;

private:
    rmt_channel_handle_t _channel;
    rmt_encoder_handle_t _encoder;
};

#endif
