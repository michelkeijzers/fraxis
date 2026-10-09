# Permanent Storage

## See also

ApplicationData.md for a description about the terminology regarding application data.

## Introduction

This design decision decides where to store global and application data (NVS or MicroSDCard) and the key/file 
structures.

## NVS

### Introduction

For storing approximately 20 general system settings.
All other data is stored on MicroSDCard, mainly because of the amount of applications (can be more than 500).

One key per setting.

Namespace: GlobalSettings

### Keys

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

Settings are stored max once per 10 seconds OR when starting an application.

Namespace: GlobalSettings

### Windows Simulator

For Windows, NVS is simulated by a file with the above content using the Byte Offset column.
The file is called nvs.bin and stored in a predefined folder and will be 256 bytes.


## Micro Sd

The MicroSDCard stores all application data (see ApplicationData.md).

The most application data is stored on MicroSDCard, in one folder per app, called applications/app\_<nr>.

Three files are placed in each application folder:

- Metadata.bin: contains preset names
- Preset.bin: preset information (settings)
- Highscores.bin: highscores data.

When an application is selected, only the Metadata.bin file is read and stored in RAM to speed up the menu navigation.

### ​Meta Data File

File name: Metadata.bin

Central file containing the lightweight status per app (last used timestamp, favorite status, number of versions, and execution count).

The structure is:

```
struct MetadataBinFileStructure
{
    uint32_t metadataFileVersion;
    uint8_t numberOfVersions;
    uint8_t numberOfPresets;
    uint8_t lastSelectedPreset;
    uint8_t isFavorite;
    uint32_t lastTimeExecutedTimeStamp;
    uint32_t numberOfTimesExecuted;
    char presetNames[16][numberOfPresets]
};
```

There are maximum 256 presets, thus this file is maximum 16 + 256 \* 16 = 4.1 KB. Typically with 10 presets it is a few hundred bytes.

### Presets.bin

This file stores the settings for each preset.

The structure is:

```
struct PresetsBinFileStructure
{
    uint32_t PresetFileVersion;
    PresetData[numberOfPresets];
}

struct PresetData
{
    uint8_t version;
    AppSettings settings; // for that application
}

struct AppSettings
{
    union
    {
        App1SettingsVersion1;
        App1SettingsVersion2;
        App2SettingsVersion1;
        App3SettingsVersion1;
    }

    struct AppSettingsVersion1 // Example
    {
        uint8_t hitPoints;
    }

    struct AppSettinsgVersion2 // Example
    {
        uint8_t hitPoints;
        uint8_t nrOfMonsters;
    }

    ...
}
```

The reason that this union contains the settings for all applications is to prevent memory fragmentation when switching applications.

When the preset has been selected/known, this file is read.
For 10 presets and 50 bytes of settings, the size is 500 bytes.
When 50 presets and 500 bytes of settings, the size is 25 KB (still acceptable).

There is always one (default) preset chunk which cannot be deleted.

### Highscores.bin

The Highscores file contains per preset the list of highscore names and scores.

For each preset, HighscoresData is stored:

- Number of highscores (for that preset): uint8_t
- Per entry:
  - Name (char [8])
  - Score (uint32_t)

Structure:

```
struct HighscoresBinFile
{
    uint32_t HighscoresBinFileVersion;
    HighscoresTable highscoresTables[NrOfPresets];
}

struct HighscoresTable
{
    HighscoresEntry highscoresEntry[...]; // Depending on HighscoresBinFileVersion/hardcoded
}

struct HighscoresEntry
{
    char name[8];
    uint32_t score;
}
```

Assuming 10 presets, 25 highscores, this file is around 10 _ 25 _ (8 + 4) =
3 KB. For 50 presets, 25 highscores, this file is still just 15 KB.

### Serialization/Deserialization

In Application there will be a buffer that stores the MicroSdCard files for that application. No need for double 
buffering.

There will be a generic serializer/deserializer but settings will be serialized/deserialized per app (unless templates 
are used).

# RTOS comments

Reading the file should be done asynchronously in the ApplicationTask otherwise it hangs (and it may contain watchdog/
diagnostics and other functionality that cannot be delayed).
