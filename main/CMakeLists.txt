set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_EXTENSIONS OFF)

idf_component_register(
    SRCS
        "L1_Composition/main.cpp"
        "L1_Composition/ComponentsBuilder/ComponentsBuilder.cpp"
        "L1_Composition/ComponentsBuilder/EspComponentsBuilder.cpp"
        "L1_Composition/Context/Context.cpp"
        "L1_Composition/Context/DomainModelsContext.cpp"
        "L1_Composition/Context/DeviceModelsContext.cpp"
        "L1_Composition/Context/DeviceDriversContext.cpp"
        "L1_Composition/Context/ServicesContext.cpp"

        "L2_Applications/ApplicationsTask.cpp"
        "L2_Applications/ApplicationsManager.cpp"

        "L4_DomainModels/IoPins/IoPins.cpp"
        "L4_DomainModels/Lcd2004/Lcd2004.cpp"
        "L4_DomainModels/LedStrips/LedStrips.cpp"
        "L4_DomainModels/Tm1637/Tm1637.cpp"

        "L5_DeviceModels/Lcd2004/Lcd2004Model.cpp"
        "L5_DeviceModels/Mcp23017/Mcp23017Model.cpp"
        "L5_DeviceModels/Tm1637/Tm1637Model.cpp"
        "L5_DeviceModels/Ws28xx/Ws28xxModel.cpp"
        
        "L6_DeviceDrivers/I2c/I2cDriver.cpp"
        "L6_DeviceDrivers/I2c/EspI2cDriver.cpp"
        "L6_DeviceDrivers/Lcd2004/Lcd2004Driver.cpp"
        "L6_DeviceDrivers/Lcd2004/EspLcd2004Driver.cpp"
        "L6_DeviceDrivers/Mcp23017/Mcp23017Driver.cpp"
        "L6_DeviceDrivers/Mcp23017/EspMcp23017Driver.cpp"
        "L6_DeviceDrivers/Tm1637/Tm1637Driver.cpp"
        "L6_DeviceDrivers/Tm1637/EspTm1637Driver.cpp"
        "L6_DeviceDrivers/Ws28xx/Ws28xxDriver.cpp"
        "L6_DeviceDrivers/Ws28xx/EspWs28xxDriver.cpp"

        "L8_Services/Rtos/EspRtos.cpp"
        "L8_Services/RtosQueue/EspRtosQueue.cpp"
        "L8_Services/RtosTask/EspRtosTask.cpp"
        "L8_Services/Random/EspRandom.cpp"
        "L8_Services/Assert/Assert.cpp"
        "L8_Services/Debug/Debug.cpp"
    INCLUDE_DIRS "."
)