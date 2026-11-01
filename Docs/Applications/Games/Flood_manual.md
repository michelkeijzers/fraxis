# FLOOD (MANUAL)

## DESCRIPTION

Conquer territories by selecting colors and expanding your territory. The objective depends on the selected game mode and settings. In most games, the goal is to conquer the largest area of the map or to conquer the entire map.

Special territories may appear on the map. These territories provide bonus points or special effects when conquered.

## ALTERNATIVE NAMES

* Flood-It
* Color Flood

## TAGS

1 Player, 2 Players, Puzzle, Strategy, Timed, Versus

## ORIENTATION

Both

## CORE RULES

The map consists of territories represented by different colors.

The player starts with ownership of a single territory located in a corner of the map.

During each conquest, the player selects a color.

All territories adjacent to the player's territory that have the selected color become part of the player's territory.

The conquered territories adopt the color of the player's territory, allowing further expansion in future turns.

The game continues until one of the configured end conditions has been met.

## GAME SETTINGS

### Summary

| Setting | Values | Description |
|----------|----------|----------|
| Timed | Off, 10-120s | Ends the game when the timer expires. |
| Max Conquests | Unlimited, 1-255 | Maximum number of conquests per player. |
| Max Same Colors | Unlimited, 1-10 | Limits the usage of a specific color. |
| Fog Of War | Off, On | Hides unexplored areas. |
| Shared Board | Off, On | Players share the same map. |
| Select Enemy Color | Off, On | Allows selecting the opponent's color. |
| Percent Of Map | Off, 1-100% | Victory threshold based on owned territory. |
| Center Objective | Disabled, Bonus Points, Instant Victory | Defines the behavior of Center Territories. |
| Center Bonus Points | 0-100,000 | Bonus awarded for conquering a Center Territory. |

### Timed

Determines whether the game has a time limit.

Values:

* Off
* 10 - 120 seconds

When enabled, the game ends when the timer expires.

### Max Conquests

Limits the number of conquests a player may perform.

Values:

* Unlimited
* 1 - 255

When the limit is reached, the player can no longer perform additional conquests.

### Max Same Colors

Limits how often a specific color may be selected by a player.

Values:

* Unlimited
* 1 - 10

A player may no longer select a color after reaching its limit.

Example:

When Max Same Colors is set to 3, each individual color may only be selected three times during the game.

### Fog Of War

Determines whether only nearby territories are visible.

Values:

* Off
* On

When enabled, unexplored areas of the map remain hidden.

### Shared Board

Determines whether players play on separate maps or compete on a single shared map.

Values:

* Off
* On

### Select Enemy Color

Determines whether a player may select the current color of an opponent.

Values:

* Off
* On

Used only in multiplayer modes.

### Percent Of Map

Defines a victory threshold based on map ownership.

Values:

* Off
* 1% - 100%

The game ends when a player reaches or exceeds the configured percentage of the map.

### Center Objective

Defines the behavior of Center Territories.

Values:

* Disabled
* Bonus Points
* Instant Victory

### Center Bonus Points

The amount of bonus points awarded when conquering a Center Territory.

Values:

* 0 - 100,000

Only used when Center Objective is set to Bonus Points.

### SPECIAL TERRITORIES

Special territories are visually identified by a pulsing center pixel.

When all special territory counts are set to zero, no special territories are generated.

#### Summary

| Type | Visualization | Effect | Default Reward | Availability |
|--------|--------|--------|--------|--------|
| Bonus Territory | Yellow | Bonus score | +5,000 | All |
| Major Capital City | White | High-value objective | +10,000 | All |
| Center Territory | Red | Bonus or instant victory | +25,000 | All |
| Time Territory | Blue | Adds time | +10 seconds | Timed modes |
| Shield Territory | Cyan | Blocks enemy conquest | N/A | Multiplayer |

#### Bonus Territories

The number of Bonus Territories generated on the map.

Values:

* 0 - 255

Visualization:

* Pulsing yellow center pixel

Effect:

* Grants bonus points when conquered

Reward:

* +5,000 points (default)

#### Major Capital Cities

The number of Major Capital Cities generated on the map.

Values:

* 0 - 255

Visualization:

* Pulsing white center pixel

Effect:

* High-value strategic territory

Reward:

* +10,000 points (default)

#### Center Territories

The number of Center Territories generated on the map.

Values:

* 0 - 1

Visualization:

* Pulsing red center pixel

Effect:

* Grants bonus points or instant victory

Reward:

* +25,000 points (default)

Additional Settings:

* Center Objective
* Center Bonus Points

#### Time Territories

The number of Time Territories generated on the map.

Values:

* 0 - 255

Visualization:

* Pulsing blue center pixel

Effect:

* Grants additional time when conquered

Reward:

* +10 seconds (default)

Only available in timed game modes.

#### Shield Territories

The number of Shield Territories generated on the map.

Values:

* 0 - 255

Visualization:

* Pulsing cyan center pixel

Effect:

* Blocks the next enemy conquest affecting the player

Only available in multiplayer game modes.

## SCORING METHODS

### Classic Score

The game starts with 500,000 points.

Each conquest reduces the score by 10,000 points.

Minimum score: 0.

### Area Score

The score equals:

Area Owned × 1,000

### Territory Percentage Score

The score equals the percentage of the map owned by the player multiplied by 10,000.

### Custom Score

Multiple score systems may be combined.

Example:

Area Owned × 1,000 + Bonus Territory Rewards + Major Capital Cities Rewards

## END CONDITIONS

Depending on the selected settings, a game may end when:

* The entire map has been conquered.
* The timer expires.
* The maximum number of conquests has been reached.
* A player reaches the configured Percent Of Map threshold.
* A Center Territory triggers an instant victory.

## VARIANTS

### Summary

The following variants are recommended configurations. Custom configurations may also be created.

| Preset | Players | Timed | Shared Board | Main Objective |
|---------|---------|---------|---------|---------|
| Classic | 1 | No | No | Conquer entire map |
| Limited Conquests | 1-2 | No | Optional | Max territory in limited turns |
| Time Attack | 1-2 | Yes | Optional | Max territory before time expires |
| Players War | 2 | Optional | Yes | Defeat opponent |
| Capture The Center | 1-2 | Optional | Optional | Capture Center Territory |

### CLASSIC

#### Objective

Conquer the entire map using as few conquests as possible.

#### Settings

* Timed: Off
* Max Conquests: 50
* Max Same Colors: Unlimited
* Fog Of War: Off
* Shared Board: Off
* Bonus Territories: 0
* Major Capital Cities: 0
* Center Territories: 0

#### Scoring

Classic Score

### LIMITED CONQUESTS

#### Objective

Conquer as much of the map as possible within the allowed number of conquests.

#### Settings

* Timed: Off
* Max Conquests: Configurable
* Max Same Colors: Unlimited
* Fog Of War: Off
* Shared Board: Off

#### Scoring

Area Score

### TIME ATTACK

#### Objective

Conquer as much of the map as possible before time expires.

#### Settings

* Timed: Configurable
* Max Conquests: Unlimited
* Max Same Colors: Unlimited
* Fog Of War: Off
* Shared Board: Off
* Time Territories: Optional

#### Scoring

Area Score

### PLAYERS WAR

#### Objective

Conquer more territory than your opponent.

#### Rules

Players start in opposite corners of the same map.

By default, players may not select their own color.

#### Settings

* Shared Board: On
* Select Enemy Color: Configurable
* Percent Of Map: Configurable
* Timed: Optional
* Max Conquests: Optional
* Shield Territories: Optional

#### Scoring

Area Score

Winner:

* Player with the largest territory.

### CAPTURE THE CENTER

#### Objective

Conquer the Center Territory before your opponent.

#### Settings

* Center Territories: 1
* Center Objective: Bonus Points or Instant Victory
* Center Bonus Points: Configurable
* Shared Board: Optional
* Timed: Optional

#### Scoring

Area Score + Center Bonus

### FOG OF WAR

#### Objective

Conquer as much territory as possible while exploring the hidden map.

#### Settings

* Fog Of War: On

#### Scoring

Depends on the selected scoring method.

### COLOR RESTRICTION

#### Objective

Manage color selections efficiently while expanding your territory.

#### Settings

* Max Same Colors: Configurable

#### Scoring

Depends on the selected scoring method.

### TREASURE HUNT

#### Objective

Conquer special territories to maximize your score.

#### Settings

* Bonus Territories: 10
* Major Capital Cities: 3
* Center Territories: 1
* Timed: Off
* Max Conquests: Unlimited

#### Scoring

Area Score + Special Territory Bonuses

#### End of Game

* Entire map conquered.
