set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_EXTENSIONS OFF)

idf_component_register(
    SRCS
        "main.cpp"

        "Core/Components/AtariJoystick.cpp"
        "Core/Components/Lcd1602Display.cpp"

        "Core/Menu/MenuInput.cpp"
        "Core/Menu/MenuRenderer.cpp"
        "Core/Menu/MenuSimulator.cpp"
        "Core/Menu/MenuStates.cpp"

        "ESP32/Components/EspLcd1602Display.cpp"
        "ESP32/EspI2c.cpp"
    INCLUDE_DIRS "."
)