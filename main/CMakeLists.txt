set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_EXTENSIONS OFF)

idf_component_register(
    SRCS
        "main.cpp"

        "Common/Components/LedStrip/LedStripModel.cpp"
        "Common/Components/LedStrip/EspLedStripDriver.cpp"
        "Common/Components/LedStrip/Ws2812Rmt.cpp"
        "Common/Components/LedStrip/LedStripsCurrentLimiter.cpp"

        "Common/Services/Rtos/EspRtos.cpp"
        "Common/Services/RtosQueue/EspRtosQueue.cpp"
        "Common/Services/RtosTask/EspRtosTask.cpp"
        "Common/Services/Debug/Debug.cpp"

        "Tasks/LedStripsTask/LedStripsTask.cpp"
        "Tasks/SystemTask/SystemTask.cpp"

        "Core/TaskManager/TaskManager.cpp"
        "Core/Menu/MenuRenderer.cpp"
        "Core/Menu/MenuStates.cpp"

        "Core/Components/ComponentsBuilder.cpp"
        "Core/Components/LedStrips.cpp"
        "Core/Components/Lcd1602Display.cpp"
        "Core/Components/Tm1637.cpp"
        "Core/Components/Mcp23017.cpp"
        "Core/Components/PinIo.cpp"
        "Core/Components/PinIoMappings.cpp"

        "ESP32/Components/EspComponentsBuilder.cpp"
        "ESP32/Components/EspLcd1602Display.cpp"
        "ESP32/Components/EspTm1637.cpp"
        "ESP32/Components/EspMcp23017.cpp"
        "ESP32/EspI2c.cpp"

    INCLUDE_DIRS "."
)