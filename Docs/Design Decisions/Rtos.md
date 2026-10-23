# RTOS

# TASKS

Core 0: Time Critical
Core 1: Logic, UI, I/O, System

| Task      | Contains                                            | Core | Priority | Percentage | Notes                |
| --------- | --------------------------------------------------- | ---- | -------- | ---------- | -------------------- |
| LedStrips | WS2812                                              | 0    | Highest  | 5-15%      | 60 Hz                |
| Sound     | MAX98357 speaker, INMP441 Mic, Passive Buzzer       | 0    | High     | 10-25%     | 16 kHz, 16 bit, mono |
| I2C       | MCP23017 (Joysticks, PinIO, LEDs, button), 2004 LCD | 1    | High     | 3-10%      |                      |
| Tm1637    | TM1637 (Central Panel, Player 1/2)                  | 1    | Medium   | 2-6%       |                      |
| Applications  | Applications                                                | 1    | Medium   | 5-20%      |                      |
| System    | Menu, NVRAM, Logging, Settings                      | 1    | Low      | 2-5%       |                      |

# QUEUES

| Queue         | Source       | Destination  | Messages         | Data                       | Notes                              |
| ------------- | ------------ | ------------ | ---------------- | -------------------------- | ---------------------------------- |
| LedStripQueue | Applications         | LedStrips    | SetLeds          | ledBuffer                  | -                                  |
|               |              |              | SetBrightness    | level                      | -                                  |
| SoundQueue    | Applications         | Sound        | PlaySample       | id                         | -                                  |
|               |              |              | Tone             | frequency, duration        |                                    |
|               |              |              | StopSound        |                            |                                    |
|               |              |              | StartMic         |                            |                                    |
|               |              |              | StopMic          |                            |                                    |
| I2CRequest    | Applications, System | I2C          | WriteLed         | ledId, value               |                                    |
|               |              |              | PrintLcd         | line1, line2               |                                    |
|               |              |              | ClearLcd         |                            |                                    |
| I2CEvent      | I2C          | Applications, System | JoystickEvent    | player, direction          |                                    |
|               |              |              | ButtonEvent      | id, pressed                |                                    |
| Tm1637        | Applications, System | Tm1637       | SetValue         | id, value                  |                                    |
|               |              |              | SetTime          | first, second              |                                    |
| System        | System       | Applications         | RunApplication           | applicationId                      |                                    |
|               | Applications         | System       | ChangeSettings   | Settings                   |                                    |
|               |              |              | UpdateHighscores | Highscores                 |                                    |
| Logging       | Any          | System       | Log              | Source, type, logging text | Type = Error, warning, info, debug |
