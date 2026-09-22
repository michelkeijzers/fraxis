# SHORT TERM

| Stat    | Layer(s) | Sub Category   | Item                         | Description                     |
| ------- | -------- | -------------- | ---------------------------- | ------------------------------- |
| Todo    | M20       | TM1637         | Sending messages             |                                 |
| Todo    | M30       | TM1637         | Messages                     |                                 |
| Todo    | M40       | TM1637         | Create domain model          |                                 |
| Todo    | M50       | TM1637         | Create device model          |                                 |
| Todo    | M60       | TM1637         | Device driver                |                                 |
| Todo    | M20       | Led Strips     | Sending messages             |                                 |
| Todo    | M30       | Led Strips     | Messages                     |                                 |
| Todo    | M40       | Led Strips     | Create domain model          |                                 |
| Todo    | M50       | Led Strips     | Create device model          |                                 |
| Todo    | M60       | Led Strips     | Device driver                |                                 |
| Todo    | M60       | Led Strips     | Double buffer?               |                                 |
| Todo    | M50       | Led Strips     | Current Limiting             |                                 |
| Todo    | M20       | Apps           | Application start/stopping   |                                 |
| Todo    | M20       | Apps           | Application resuming         |                                 |
| Todo    | M70       | LCD2004        | 20x4 format                  |                                 |
|         |          |                |                              |                                 |

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
|      | BART     | Cable        | Jack Cable Bart             | Bart               |


# IMPROVEMENTS

| Stat | Layer(s) | Sub Category   | Item                                        | Description |
| ---- | -------- | -------------- | ------------------------------------------- | ----------- |
|      | M10       | Context        | Minimum context                             |             |
|      | M20       | Context        | Minimum context                             |             |
|      | M30      | Context        | Minimum context                             |             |
|      | M40      | Context        | Minimum context                             |             |
|      | M50      | Context        | Minimum context                             |             |
|      | M60      | Context        | Minimum context                             |             |
|      | All      | Destructors    | Remove empty destructors (and constructors) |             |
|      | All      | Inline getters | Check if useful                             |             |

# FUTURE

| Stat | Layer(s) | Sub Category   | Item                      | Description |
| ---- | -------- | -------------- | ------------------------- | ----------- |
|      | M10       | NVS            | For settings/highs scores | + Menu      |
|      | M20       | NVS            | For settings/highs scores | + Menu      |
|      | M30       | NVS            | For settings/highs scores |             |
|      | M40       | NVS            | For settings/highs scores |             |
|      | M50       | NVS            | For settings/highs scores |             |
|      | M60       | NVS            | For settings/highs scores |             |
|      | M10       | Passive Buzzer |                           |             |
|      | M20       | Passive Buzzer |                           |             |
|      | M30       | Passive Buzzer |                           |             |
|      | M40       | Passive Buzzer |                           |             |
|      | M50       | Passive Buzzer |                           |             |
|      | M60       | Passive Buzzer |                           |             |
|      | M10       | Micro SD Card  |                           |             |
|      | M20       | Micro SD Card  |                           |             |
|      | M30       | Micro SD Card  |                           |             |
|      | M40       | Micro SD Card  |                           |             |
|      | M50       | Micro SD Card  |                           |             |
|      | M60       | Micro SD Card  |                           |             |
|      | M10       | I2S Speaker    |                           |             |
|      | M10       | I2S Speaker    |                           |             |
|      | M30       | I2S Speaker    |                           |             |
|      | M40       | I2S Speaker    |                           |             |
|      | M50       | I2S Speaker    |                           |             |
|      | M60       | I2S Speaker    |                           |             |
|      | ???      | Samples via SD |                           |             |
|      | M10       | I2S Microphone |                           |             |
|      | M20      | I2S Microphone |                           |             |
|      | M30      | I2S Microphone |                           |             |
|      | M40       | I2S Microphone |                           |             |
|      | M50       | I2S Microphone |                           |             |
|      | M60       | I2S Microphone |                           |             |
|      | M20       | Applications   | Write games, demos etc    |             |

# DONE

| Stat     | Layer(s) | Sub Category | Item     | Description         |
| -------- | -------- | ------------ | -------- | ------------------- |
| Done    | M50       | LCD2004        | Finish device model          |                                 |
| Done    | M60       | LCD2004        | Support single char writing  |                                 |
| Done    | M60       | I2c            | Create device driver         | Initialize                      |
| Done    | M60       | LCD2004        | Create device driver         |                                 |
| Done    | M50       | PinIo          | Send input queue messages    |                                 |
| Done    | M50       | PinIo          | Connect to M60                |                                 |
| Done    | M60       | MCP23017       | Create device drivers        |                                 |
| Done    | M20       | PinIO          | Process input queue messages |                                 |

# REJECTED

| Rejected | Buttons  | Core         | Debounce | Hardware debouncing |
|         |          |                |                              |                                 |
|         |          |                |                              |                                 |
|         |          |                |                              |                                 |
|         |          |                |                              |                                 |
|         |          |                |                              |                                 |
|         |          |                |                              |                                 |
|         |          |                |                              |                                 |
|         |          |                |                              |                                 |
|         |          |                |                              |                                 |
|         |          |                |                              |                                 |
|         |          |                |                              |                                 |
|         |          |                |                              |                                 |
|         |          |                |                              |                                 |
|         |          |                |                              |                                 |
|         |          |                |                              |                                 |
|         |          |                |                              |                                 |
|         |          |                |                              |                                 |
|         |          |                |                              |                                 |
|         |          |                |                              |                                 |
|         |          |                |                              |                                 |
|         |          |                |                              |                                 |
|         |          |                |                              |                                 |
|         |          |                |                              |                                 |
|         |          |                |                              |                                 |
|         |          |                |                              |                                 |
|         |          |                |                              |                                 |
|         |          |                |                              |                                 |
|         |          |                |                              |                                 |
|         |          |                |                              |                                 |
|         |          |                |                              |                                 |
|         |          |                |                              |                                 |
|         |          |                |                              |                                 |
|         |          |                |                              |                                 |
|         |          |                |                              |                                 |
|         |          |                |                              |                                 |
