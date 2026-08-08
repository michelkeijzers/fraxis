#pragma once

#include "Rmt.hpp"

class WindowsRmt : public Rmt
{
public:
    WindowsRmt() = default;
    ~WindowsRmt() = default;

private:
    bool DelEncoder() override;
    bool DelChannel() override;

    bool NewTxChannel(
        uint8_t pin) override;
    bool Enable() override;
    bool NewSimpleEncoder() override;

    bool Transmit(
        const void* payload,
        size_t payload_bytes) override;
    bool TxWaitAllDone() override;
};
