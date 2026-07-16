set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_EXTENSIONS OFF)

idf_component_register(
    SRCS
        "main.cpp"

        "Common/Components/LedStrip/LedStripModel.cpp"
        "Common/Components/LedStrip/EspLedStripDriver.cpp"
        "Common/Components/LedStrip/LedStripsCurrentLimiter.cpp"
        "Common/Components/LedStrip/Ws2812Rmt.cpp"

        "Common/Components/I2c/EspI2c.cpp"
        "Common/Components/I2c/I2c.cpp"
        "Common/Components/Lcd1602Display/Lcd1602DisplayDriver.cpp"
        "Common/Components/Lcd1602Display/Lcd1602DisplayModel.cpp"
        "Common/Components/Lcd1602Display/EspLcd1602DisplayDriver.cpp"
        "Common/Components/Lcd1602Display/Lcd1602DisplayDriver.cpp"

        "Common/Services/Rtos/EspRtos.cpp"
        "Common/Services/RtosQueue/EspRtosQueue.cpp"
        "Common/Services/RtosTask/EspRtosTask.cpp"
        "Common/Services/Random/EspRandom.cpp"
        "Common/Services/Debug/Debug.cpp"

        "Tasks/SystemTask/SystemTask.cpp"
        "Tasks/LedStripsTask/LedStripsTask.cpp"
        "Tasks/I2cTask/I2cTask.cpp"

        "Core/TaskManager/TaskManager.cpp"
        "Core/Menu/MenuRenderer.cpp"
        "Core/Menu/MenuStates.cpp"

        "Core/Components/ComponentsBuilder.cpp"
        "Core/Components/LedStrips.cpp"
        "Core/Components/Tm1637.cpp"
        "Core/Components/Mcp23017.cpp"
        "Core/Components/PinIo.cpp"
        "Core/Components/PinIoMappings.cpp"

        "ESP32/Components/EspComponentsBuilder.cpp"
        "ESP32/Components/EspTm1637.cpp"
        "ESP32/Components/EspMcp23017.cpp"

    INCLUDE_DIRS "."
)