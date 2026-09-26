# Application Data

## See also

See PermanentStorage.md for a detailed description how the above data is stored.

## Applications

There will be many applications on the system.

The last executed application is stored to the user can easily select/sort by it.
The amount of executions per application is stored so the user can easily select/sort by it.

## Menu Application

The menu is a special application that is active from the start and has application number 0.
It can launch or pause another application, and when that application stops or pauses, execution is
returned to the Menu application.

## Versions

An application can have multiple versions (upto 256, but typically 1 or a few).

## Application Type

Applications are divided in four categories:

- Games: games of all kind.
- Demoes: interactive or non-interactive demoes showing the capabilities of the device.
- Tools: useful apps for the user, such as a clock, countdown alarm etc.
- Utilities: apps used for setup, diagnosing, measuring and debugging the system.

## Tags

Each application has (multiple) tags, and tags are hardcoded in the application.
Some tags are specific to certain application types.

Tags are used to filter the applications for easy selection by the user.

## Presets

Each application has presets. A preset has a name and contains a set of 'settings'.

The last selected preset for each application is stored, so the user can easily select the last executed preset.

## Settings

Each preset has settings which are specific for a game, or even game version.
Settings can be e.g. HitPoints, Ball Speed, Number of Obstacles etc.

## Highscores

Only for games, high scores are kept, containing of a name of the player and the score.

## Storage

See PermanentStorage.md for a detailed description how the above data is stored.
