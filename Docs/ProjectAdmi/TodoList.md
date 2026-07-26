# SHORT TERM

| Stat    | Layer(s) | Sub Category   | Item                         | Description                     |
| ------- | -------- | -------------- | ---------------------------- | ------------------------------- |
| Ongoing | L5       | LCD2004        | Finish device model          |                                 |
| Todo    | L6       | LCD2004        | Support single char writing  |                                 |
| Todo    | L6       | I2c            | Create device driver         | Initialize                      |
| Todo    | L6       | LCD2004        | Create device driver         |                                 |
| Todo    | L5       | PinIo          | Send input queue messages    |                                 |
| Todo    | L5       | PinIo          | Connect to L6                |                                 |
| Todo    | L6       | MCP23017       | Create device drivers        |                                 |
| Todo    | L2       | PinIO          | Process input queue messages |                                 |
| Todo    | L2       | Apps           | Application start/stopping   |                                 |
| Todo    | L2       | Apps           | Application resuming         |                                 |
| Todo    | L3       | Led Strip      | Queue messages               |                                 |
| Todo    | L4       | Led Strip      | Led Strip commands           |                                 |
| Todo    | L5       | Led Strip      | Create device model          | X/Y -> X Conversion/orientation |
| Todo    | L5       | Led Strip      | Current limiter              |                                 |
| Todo    | L5       | Led Strip      | Connect to L6                |                                 |
| Todo    | L6       | Led Strip      | Create device driver         |                                 |
| Todo    | L4       | TM1637         | Create domain model          |                                 |
| Todo    | L5       | TM1637         | Create device model          |                                 |
| Todo    | L5       | TM1637         | Connect to L6                |                                 |
| Todo    | L6       | TM1637         | Create device driver         |                                 |
| Todo    | L7       | GdiScreen      | Empty screen                 |                                 |
| Todo    | L7       | LCD2004        |                              |                                 |
| Todo    | L7       | Joysticks      |                              |                                 |
| Todo    | L7       | TM1637         |                              |                                 |
| Todo    | L7       | Led Strips     |                              |                                 |
| Todo    | L7       | PinIo/MCP23017 |                              |                                 |

# MID TERM

| Stat | Layer(s) | Sub Category | Item                        | Description        |
| ---- | -------- | ------------ | --------------------------- | ------------------ |
|      | MCP23017 | Hardware     | Initial Test, I/O, debounce |                    |
|      | 2004     | Hardware     | 2004 + MCP23017             | With Level Shifter |
|      | I2S      | Hardware     | LED Strips                  |                    |
|      | I2S      | Hardware     | Speaker Hardware            | Initial Test       |
|      | I2S      | Hardware     | Speaker Core/Simulator      |                    |
|      | I2S      | Hardware     | Mic Hardware                |                    |
|      | I2S      | Hardware     | Mic Core/Simulator          |                    |
|      | I2S      | Hardware     | SOLDERING Board             |                    |
|      | I2S      | Hardware     | SOLDERING All               |                    |

# IMPROVEMENTS

| Stat | Layer(s) | Sub Category   | Item                                        | Description |
| ---- | -------- | -------------- | ------------------------------------------- | ----------- |
|      | L2       | Context        | Minimum context                             |             |
|      | L3       | Context        | Minimum context                             |             |
|      | L4       | Context        | Minimum context                             |             |
|      | L5       | Context        | Minimum context                             |             |
|      | L6       | Context        | Minimum context                             |             |
|      | All      | Destructors    | Remove empty destructors (and constructors) |             |
|      | All      | Inline getters | Check if useful                             |             |

# FUTURE

| Stat | Layer(s) | Sub Category   | Item                      | Description |
| ---- | -------- | -------------- | ------------------------- | ----------- |
|      | L1       | NVS            | For settings/highs scores | + Menu      |
|      | L2       | NVS            | For settings/highs scores | + Menu      |
|      | L3       | NVS            | For settings/highs scores |             |
|      | L4       | NVS            | For settings/highs scores |             |
|      | L5       | NVS            | For settings/highs scores |             |
|      | L6       | NVS            | For settings/highs scores |             |
|      | L1       | Passive Buzzer |                           |             |
|      | L2       | Passive Buzzer |                           |             |
|      | L3       | Passive Buzzer |                           |             |
|      | L4       | Passive Buzzer |                           |             |
|      | L5       | Passive Buzzer |                           |             |
|      | L6       | Passive Buzzer |                           |             |
|      | L1       | Micro SD Card  |                           |             |
|      | L2       | Micro SD Card  |                           |             |
|      | L3       | Micro SD Card  |                           |             |
|      | L4       | Micro SD Card  |                           |             |
|      | L5       | Micro SD Card  |                           |             |
|      | L6       | Micro SD Card  |                           |             |
|      | L1       | I2S Speaker    |                           |             |
|      | L2       | I2S Speaker    |                           |             |
|      | L3       | I2S Speaker    |                           |             |
|      | L4       | I2S Speaker    |                           |             |
|      | L5       | I2S Speaker    |                           |             |
|      | L6       | I2S Speaker    |                           |             |
|      | ???      | Samples via SD |                           |             |
|      | L1       | I2S Microphone |                           |             |
|      | L2       | I2S Microphone |                           |             |
|      | L3       | I2S Microphone |                           |             |
|      | L4       | I2S Microphone |                           |             |
|      | L5       | I2S Microphone |                           |             |
|      | L6       | I2S Microphone |                           |             |
|      | L2       | Applications   | Write games, demos etc    |             |

# DONE

| Stat     | Layer(s) | Sub Category | Item     | Description         |
| -------- | -------- | ------------ | -------- | ------------------- |
| Rejected | Buttons  | Core         | Debounce | Hardware debouncing |
