#pragma once

    // MCP23017 register map
namespace M60::Mcp23017
{
    // MCP23017 register map
    constexpr uint8_t MCP23017_IODIRA = 0x00;
    constexpr uint8_t MCP23017_IODIRB = 0x01;
    constexpr uint8_t MCP23017_IPOLA = 0x02;
    constexpr uint8_t MCP23017_IPOLB = 0x03;
    constexpr uint8_t MCP23017_GPINTENA = 0x04;
    constexpr uint8_t MCP23017_GPINTENB = 0x05;
    constexpr uint8_t MCP23017_DEFVALA = 0x06;
    constexpr uint8_t MCP23017_DEFVALB = 0x07;
    constexpr uint8_t MCP23017_INTCONA = 0x08;
    constexpr uint8_t MCP23017_INTCONB = 0x09;
    constexpr uint8_t MCP23017_IOCON = 0x0A;
    constexpr uint8_t MCP23017_GPPUA = 0x0C;
    constexpr uint8_t MCP23017_GPPUB = 0x0D;
    constexpr uint8_t MCP23017_INTFA = 0x0E;
    constexpr uint8_t MCP23017_INTFB = 0x0F;
    constexpr uint8_t MCP23017_INTCAPA = 0x10;
    constexpr uint8_t MCP23017_INTCAPB = 0x11;
    constexpr uint8_t MCP23017_GPIOA = 0x12;
    constexpr uint8_t MCP23017_GPIOB = 0x13;
    constexpr uint8_t MCP23017_OLATA = 0x14;
    constexpr uint8_t MCP23017_OLATB = 0x15;
}
