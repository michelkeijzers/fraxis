#ifdef ESP_PLATFORM

#include "EspSpi.hpp"
#include "driver/spi_master.h"
#include "esp_err.h"

EspSpi::EspSpi() 
{
}

EspSpi::~EspSpi() 
{
}

bool EspSpi::IsValidPort(
    uint8_t port)
{
    return (port == SPI2_HOST) || (port == SPI3_HOST) || (port == HSPI_HOST) || (port == VSPI_HOST);
}

bool EspSpi::ParamConfig(
    uint8_t port,
    uint8_t mosiPin,
    uint8_t misoPin,
    uint8_t sclkPin,
    uint8_t csPin,
    uint32_t frequency)
{
    spi_bus_config_t buscfg;
    memset(&buscfg, 0, sizeof(buscfg));
    buscfg.miso_io_num = misoPin;
    buscfg.mosi_io_num = mosiPin;
    buscfg.sclk_io_num = sclkPin;
    buscfg.quadwp_io_num = -1;
    buscfg.quadhd_io_num = -1;
    buscfg.max_transfer_sz = 32;

    spi_device_interface_config_t devcfg;
    memset(&devcfg, 0, sizeof(devcfg));
    devcfg.clock_speed_hz = frequency;
    devcfg.mode = 0;
    devcfg.spics_io_num = csPin;
    devcfg.queue_size = 7;
    devcfg.cs_ena_pretrans = 3;

    esp_err_t result = spi_bus_initialize(static_cast<spi_host_device_t>(port), &buscfg, SPI_DMA_CH_AUTO);
    if (result != ESP_OK) return false;

    return (spi_bus_add_device(static_cast<spi_host_device_t>(port), &devcfg, nullptr) == ESP_OK);
}

bool EspSpi::DriverInstall(
    uint8_t port)
{
    return true;
}

bool EspSpi::Transfer(
    uint8_t port,
    const uint8_t* dataOut,
    uint8_t* dataIn,
    size_t length,
    uint32_t timeoutInMs)
{
    spi_transaction_t t;
    memset(&t, 0, sizeof(t));
    t.length = length * 8;
    t.tx_buffer = dataOut;
    t.rx_buffer = dataIn;

    return (spi_device_transmit(static_cast<spi_device_handle_t>(nullptr), &t) == ESP_OK);
}

bool EspSpi::Write(
    uint8_t port,
    const uint8_t* data,
    size_t length,
    uint32_t timeoutInMs)
{
    spi_transaction_t t;
    memset(&t, 0, sizeof(t));
    t.length = length * 8;
    t.tx_buffer = data;

    return (spi_device_transmit(static_cast<spi_device_handle_t>(nullptr), &t) == ESP_OK);
}

bool EspSpi::Read(
    uint8_t port,
    uint8_t* data,
    size_t length,
    uint32_t timeoutInMs)
{
    spi_transaction_t t;
    memset(&t, 0, sizeof(t));
    t.length = length * 8;
    t.rx_buffer = data;

    return (spi_device_transmit(static_cast<spi_device_handle_t>(nullptr), &t) == ESP_OK);
}

void* EspSpi::TransactionCreate(
    uint8_t port,
    size_t length)
{
    spi_transaction_t* transaction = new spi_transaction_t();
    memset(transaction, 0, sizeof(spi_transaction_t));
    transaction->length = length * 8;
    return transaction;
}

void EspSpi::TransactionDelete(
    void* transaction)
{
    spi_transaction_t* t = static_cast<spi_transaction_t*>(transaction);
    delete t;
}

bool EspSpi::TransactionAddCommand(
    void* transaction,
    uint16_t command,
    size_t bits)
{
    return false;
}

bool EspSpi::TransactionAddData(
    void* transaction,
    const uint8_t* data,
    size_t length,
    bool isRead)
{
    spi_transaction_t* t = static_cast<spi_transaction_t*>(transaction);
    if (isRead)
    {
        t->rx_buffer = const_cast<uint8_t*>(data);
    }
    else
    {
        t->tx_buffer = data;
    }
    t->length = length * 8;
    return true;
}

bool EspSpi::TransactionExecute(
    void* transaction,
    uint32_t timeoutInMs)
{
    spi_transaction_t* t = static_cast<spi_transaction_t*>(transaction);
    return (spi_device_transmit(static_cast<spi_device_handle_t>(nullptr), t) == ESP_OK);
}

#endif // ESP_PLATFORM
