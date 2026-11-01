# TUNNEL RUNNER (MANUAL)

## DESCRIPTION

Navigate a player vehicle through a narrow horizontal passage on a constrained matrix display ($5 \times 72$ horizontal playfield). The objective is to survive as long as possible and achieve the highest score by avoiding the shifting upper and lower cave boundaries, as well as optional internal obstacles.

Because the playfield features a tight vertical height constraint of 5 pixels (where the outermost rows form the upper and lower tunnel boundaries), the game demands high concentration and swift reflexes.

Special elements or power-up pixels may occasionally spawn within the open tunnel track to grant temporary benefits or bonus points.

## ALTERNATIVE NAMES

- Trench Run
- Cave Flyer
- Horizontal Copter

## TAGS

1 Player, Arcade, Action, Endless, Reflex, Timed, Highscore

## ORIENTATION

Horizontal ($5 \times 72$)

## CORE RULES

The playfield consists of a horizontal matrix layout 5 rows high and 72 columns wide.

The player controls a single-pixel (or small paddle) vehicle constrained to a vertical axis near the left side of the screen.

The tunnel continuously scrolls from right to left, creating the visual effect of continuous forward flight.

During flight, the height and vertical position of the upper and lower boundary walls change dynamically per column or time interval.

The player must not collide with the upper or lower boundary walls.

Colliding with a wall or an internal obstacle results in an instant crash and loss of a life.

The score increases continuously based on distance traveled, multiplied by current speed and obstacle settings.

The game continues until one of the configured end conditions has been met.

## GAME SETTINGS

### Summary

| Setting | Values | Description |
|----------|----------|----------|
| Max Lives | 1-10 | Number of crashes allowed before game over. |
| Speed Mode | Fixed, Dynamic | Velocity behavior of horizontal terrain scrolling. |
| Base Speed | Slow, Medium, Fast, Extreme | Initial scrolling velocity of the tunnel walls. |
| Tunnel Width | Narrow (1-2 px), Medium (2-3 px), Wide (3-4 px) | Clearance width between top and bottom borders. |
| Border Variance | Smooth, Rough, Cavernous | Frequency and severity of border height shifts. |
| Obstacles | Off, Low, Medium, High | Spawns static or moving barrier blocks inside the tunnel path. |
| Power-Up Spawn Rate | Disabled, Low, Medium, High | Frequency of special item pixels spawning in open space. |

### Max Lives

Limits the number of times a player may crash before elimination.

Values:

- 1 - 10

When set to 1, a single collision results in an immediate game over.

### Speed Mode

Controls how the scroll speed behaves during gameplay.

Values:

- Fixed (Speed remains constant throughout the run)
- Dynamic (Scroll speed increases gradually over time)

### Base Speed

Determines the baseline scrolling velocity of the tunnel walls across the LED matrix.

Values:

- Slow
- Medium
- Fast
- Extreme

### Tunnel Width

Defines the vertical gap size between the top ceiling and bottom floor boundaries.

Values:

- Narrow (1-2 pixels clearance)
- Medium (2-3 pixels clearance)
- Wide (3-4 pixels clearance)

### Border Variance

Controls how aggressively the upper and lower terrain changes elevation.

Values:

- Smooth (Gradual, gentle slope shifts)
- Rough (Frequent steps and sharp turns)
- Cavernous (Extreme height spikes and narrow chokes)

### Obstacles

Spawns single-pixel or vertical column barriers inside the open passage.

Values:

- Off
- Low
- Medium
- High

### Power-Up Spawn Rate

Determines how frequently special pickup pixels appear floating on the playfield.

Values:

- Disabled
- Low
- Medium
- High

### SPECIAL ELEMENTS

Special elements are visually identified by pulsing single-pixel indicators floating within the safe clearance path.

When special element rates are set to disabled, no elements are generated.

#### Summary

| Type | Visualization | Effect | Default Reward | Availability |
|--------|--------|--------|--------|--------|
| Bonus Star | Yellow | Score boost | +1,000 pts | All |
| Slow Motion | Blue | Temporarily slows scroll speed | N/A | All |
| Shield Barrier | Cyan | Protects against 1 wall collision | N/A | Multi-life modes |
| Shrink Vehicle | Green | Reduces ship size to 1 px | N/A | All |

#### Bonus Star

A special element that grants instant bonus score when collected.

Visualization:

- Pulsing yellow pixel

Effect:

- Immediately adds points to current run score

Reward:

- +1,000 bonus points (default)

#### Slow Motion

Decreases scroll velocity to assist in navigating tight terrain.

Visualization:

- Pulsing blue pixel

Effect:

- Reduces scroll speed by 35% for 5 seconds

Reward:

- Enhanced reaction time

#### Shield Barrier

Deploys a temporary protective energy field around the vehicle.

Visualization:

- Pulsing cyan pixel

Effect:

- Absorbs one border or obstacle collision without losing a life

Only available in multi-life game modes.

#### Shrink Vehicle

Reduces player ship size for easier clearance.

Visualization:

- Pulsing green pixel

Effect:

- Makes navigation through narrow gaps significantly easier for 8 seconds

## SCORING METHODS

### Distance Score

The score equals:

Distance Traveled (pixels scrolled) × Speed Multiplier

### Survival Score

The score equals:

Seconds Survived × 100 + Special Element Rewards

### Custom Score

Combines distance, obstacles dodged, and items collected.

Example:

Distance × 10 + Obstacles Passed × 200 + Bonus Star Rewards

## END CONDITIONS

Depending on the selected settings, a run ends when:

- Player exhausts all available lives (Max Lives reaches 0).
- A player reaches a configured distance limit (if enabled).

## VARIANTS

### Summary

The following variants are recommended configurations. Custom configurations may also be created.

| Preset | Players | Speed Mode | Tunnel Width | Main Objective |
|---------|---------|---------|---------|---------|
| Classic Cave | 1 | Dynamic | Medium | Fly as far as possible |
| Flappy Sprint | 1 | Fixed | Narrow | Navigate narrow terrain at high speed |
| Obstacle Dash | 1-2 | Dynamic | Wide | Dodge internal barriers and walls |
| Marathon | 1 | Fixed | Wide | Long-distance endurance survival |
| Chaos Cavern | 1 | Dynamic | Narrow | Extreme cavernous terrain with obstacles |

### CLASSIC CAVE

#### Objective

Survive as long as possible inside a standard scrolling tunnel that moves progressively faster.

#### Settings

- Max Lives: 1
- Speed Mode: Dynamic
- Base Speed: Medium
- Tunnel Width: Medium
- Border Variance: Rough
- Obstacles: Off
- Power-Up Spawn Rate: Low

#### Scoring

Distance Score

### FLAPPY SPRINT

#### Objective

Survive high-speed flight through tight gap openings.

#### Settings

- Max Lives: 1
- Speed Mode: Fixed
- Base Speed: Fast
- Tunnel Width: Narrow
- Border Variance: Smooth
- Obstacles: Off
- Power-Up Spawn Rate: Disabled

#### Scoring

Distance Score

### OBSTACLE DASH

#### Objective

Navigate wider tunnel paths filled with internal barrier blocks.

#### Settings

- Max Lives: 3
- Speed Mode: Dynamic
- Base Speed: Medium
- Tunnel Width: Wide
- Border Variance: Smooth
- Obstacles: High
- Power-Up Spawn Rate: Medium

#### Scoring

Custom Score

### MARATHON

#### Objective

Endurance run focused on precise movement over long distances.

#### Settings

- Max Lives: 5
- Speed Mode: Fixed
- Base Speed: Slow
- Tunnel Width: Wide
- Border Variance: Rough
- Obstacles: Low
- Power-Up Spawn Rate: Low

#### Scoring

Distance Score

### CHAOS CAVERN

#### Objective

Navigate unpredictable, highly variable cavernous terrain with maximum hazards.

#### Settings

- Max Lives: 1
- Speed Mode: Dynamic
- Base Speed: Fast
- Tunnel Width: Narrow
- Border Variance: Cavernous
- Obstacles: High
- Power-Up Spawn Rate: High

#### Scoring

Custom Score

#### End of Game

- All lives depleted or maximum distance reached.
