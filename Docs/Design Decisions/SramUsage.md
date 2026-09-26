# SRAM usage

## Components

Below is a list for SRAM usage

- 4 KB, Metadata file from Micro SD
- 15-20 KB, RTOS framework
- 10-50 KB for RTOS tasks
- 3 KB, led strip buffers, 5x72 leds, double buffer
- 1-2 KB, NVS support
- 1 KB, SPI support
- 1 KB, I2C support, with mcp23017 and 2004 LCD display
- 0.5 KB, tm1637
- 4-8 KB, micro SD support
- 4-8 KB, I2S buffers, 16 bit, 16 kHz, mono for inmp1441 microphone and MAX53987 amp
  50-80 KB, WiFi support
- 40-50 KB, Bluetooth support for keyboard

## Conclusion

- Around 250 KB SRAM needed
- No PSRAM needed
