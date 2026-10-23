# Permanent Storage

## See also

ApplicationData.md for a description about the terminology regarding application data.

## Introduction

This design decision decides where to store global and application data (NVS or MicroSDCard) and the key/file structures.

## NVS

### Introduction

THe following categories need to be stored:

- Approximately 20 general system settings
- Dynamic application info such as favorite, last time used, number of times started. ALl other application info is static and lives in firmware (not SRAM or storage).

All other data is stored on MicroSDCard, mainly because of the amount of applications (can be more than 500).

One key per setting.

### Global settings

Namespace: GlobalSettings

| Data                             | Key                | Type        | Size (bytes) | Comment  |
| -------------------------------- | ------------------ | --------    | ------------ | -------- |
| NVS Version                      | NvsVersion         | uint8_t     | 1            | Implemented, but not used yet. |
| LCD Brightness                   | LcdBrightness      | uint8_t     | 1            | Not implemented, needs hardware change on LCD2004 |
| TM1637's Brightness              | 7SegBrightness     | uint8_t     | 1            | Implemented |
| Led Strips Brightness Percentage | LedStripsBright    | uint8_t     | 1            | Implemented
| Speaker Volume                   | AmpVolume          | uint8_t     | 1            | 
| Microphone Volume                | MicVolume          | uint8_t     | 1            | 
| Debug Flags                      | DebugFlags         | uint32_t    | 1            | Implemented
| Last Selected App Index          | LastSelAppIndex    | uint16_t    | 2            | Implemented
| Last Selected View Mode          | LastSelViewMode    | uint8_t     | 1            | Implemented
| Last Selected App Type           | LastSelAppType     | uint8_t     | 1            | Implemented
| Last Selected Tag                | LastSelTag         | uint8_t     | 1            | Implemented
| WiFi SSID                        | WiFiSsid           | char[33]    | 33           | 
| WiFi Encrypted Password          | WiFiEncPassword    | uint8_t[64] | 64           | 
| Bluetooth Enabled                | BtEnabled          | bool        | 1            | 
| Bluetooth Mode                   | BtMode             | uint8_t     | 1            | 
| Bluetooth Last Device Name       | BtLastDevName      | char[32]    | 32           | 
| Bluetooth Last Device Address    | BtLastDevAddr      | uint8_t[6]  | 6            | 
| Bluetooth Auto Reconnect         | BtAutoReconnect    | bool        | 1            | 

For storing approximately 20 general system settings.
All other data is stored on MicroSDCard, mainly because of the amount of applications (can be more than 500).

One key per setting.

Settings are stored when the settings menu is left.

There is no dirty flag but the values are read from NVS and if different, written.

### Static Applications Info

Namespace: AppsInfo (max 15 characters length)

The following keys are blobs and written for each app, e.g. Favorites contains the favorite info for app 0, app 1, ...

| Data                             | Key                | Type        | Size (bytes) | Comment  |
| -------------------------------- | ------------------ | --------    | ------------ | -------- |
| Favorites                        | Favorites          | uint8_t     | 1            | Implemented                 
| Nr of times executed             | NrOfTimesStart     | uint16_t    | 2            | Keeps max value when reached
| Date/times last started          | LastTimesStart     | uint32_t    | 4            | Epoch since Jan 1, 2025.

Note that in 4 bytes, a time stamp can span 89 years.

A dirty flag is used for each of the variable (arrays). This prevents reading from NVS which takes 4 KB (for the biggest variable lastTimesStarted in case of 1000 apps).

Applications Info is stored when a new application is started or when the favorites flag is changed. 
Although in theory this could result in flash wearing, it is high unlikely a player will cause this deliberately (or not deliberately).

### Windows Simulator

For Windows, NVS is simulated by storing every key in its own file.

## Micro Sd

The MicroSDCard stores all application data (see ApplicationData.md).

One file is usage.bin, which is storing all usage data for all apps. 
For each app, an /apps/app_X.bin file is written, storing the data for that application, the presets and highscores.
For Windows, the above files also are written in JSON format.

### Messages (M30)

- Only one file is read/written simultaneously (although FileExists can be executed during a read/write 
file).
- Mode is Read, Write, Append (used for logging).
- After a FileStatus is sent, no further FileDataChunk messages are sent.
- OpenFile creates or empties file when mode is Write.
- ReadFile is used for streaming (samples in future) or reading a complete file, ReadOneFileChunk for reading a small portion (auto open/close the file) and ReadFileChunk for a portion with manual open/close the file.
- Assuming automatic overwrites for writing.
- bytesUsed is bytes filled, 100 (MAX_DATA_LENGTH) bytes maximum to prevent large RTOS messages.
- Enum Status is shared between all commands (open, read write, close, file exists, delete)
- A file can be read fully or by chunk/position (like a file seek).

#### Check file existence
```
M20 -> M40 : FileExists(string fileName)
M40 -> M20 : FileStatus(enum status, OK or FileNotFound) 
```

#### Read entire file
```
M20 -> M40 : OpenFile(string fileName, EMode.Read)
M40 -> M20 : FileStatus(enum status) 
M20 -> M40 : ReadFile()
M40 -> M20 : FileDataChunk(uint8_t data[MAX_DATA_LENGTH], uint16_t 
bytesUsed, bool lastChunk), multiple times, or none if empty
M40 -> M20 : FileStatus(enum status) 
M20 -> M40 : CloseFile()
M40 -> M20 : FileStatus(enum status) 
```

#### Read one chunk
```
```
M20 -> M40 : ReadOneFileChunk(string fileName, uint32_t startPosition, uint32_t length), internal opens and closes file
M40 -> M20 : FileDataChunk(uint8_t data[MAX_DATA_LENGTH], uint16_t 
bytesUsed, bool lastChunk), multiple times 
M40 -> M20 : FileStatus(OK), closes file when lastChunk
```

#### Read chunk(s)
```
M20 -> M40 : OpenFile(string fileName, EMode.read)
M40 -> M20 : FileStatus(enum status) 
M20 -> M40 : ReadFileChunk(uint32_t startPosition, uint32_t length) 
M40 -> M20 : FileDataChunk(uint8_t data[MAX_DATA_LENGTH], uint16_t 
bytesUsed, bool lastChunk), multiple times 
M40 -> M20 : FileStatus(OK) 
M20 -> M40 : CloseFile()
M40 -> M20 : FileStatus(enum status) 
```
#### Write file
```
M20 -> M40 : OpenFile(string fileName, EMode.Write)
M40 -> M20 : FileStatus(enum status) 
M20 -> M40 : FileDataChunk(uint8_t data[MAX_DATA_LENGTH], uint16_t bytesUsed, bool lastChunk), multiple times
M40 -> M20 : FileStatus(enum status) 
M20 -> M40 : CloseFile()
M40 -> M20 : FileStatus(enum status) 
```

#### Delete file
```
M20 -> M40 : DeleteFile(string fileName)
M40 -> M20 : FileStatus(enum status) 
```

Enum status:
- OK
- Busy (Spi Task busy)
- FileAlreadyOpen
- NoFileOpened
- InvalidFileName
- InvalidParameter
- FileNotFound
- CannotCreateFile
- AccessError
- ReadError
- WriteError
- DiskFull
- CrcError

### Serialization/Deserialization

In Application there will be a buffer that stores the MicroSdCard files for that application. No need for double 
buffering.

There will be a generic serializer/deserializer but settings will be serialized/deserialized per app (unless templates 
are used).

# RTOS comments

Reading the file should be done asynchronously in the SpiTask otherwise it hangs (and it may contain watchdog/
diagnostics and other functionality that cannot be delayed).
