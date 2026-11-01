# SIMON MEMORY (MANUAL)

## DESCRIPTION

Memorize and replicate sequences of illuminated pixels or colored zones across the matrix display. The game starts with a simple sequence that grows progressively longer and faster with each successful turn. The objective depends on the selected game mode and settings, typically to achieve the longest flawless sequence or highest score.

Special modifier steps or bonus signals may occasionally flash during a sequence. Successfully replicating these steps triggers special effects or awards bonus points.

## ALTERNATIVE NAMES

* Matrix Simon
* Pixel Memory
* LED Repeat

## TAGS

1 Player, 2 Players, Puzzle, Memory, Reflex, Timed, Versus

## ORIENTATION

Both ($5 \times 72$ or $16 \times 16$)

## CORE RULES

The playfield is divided into interactive color zones or discrete grid coordinates on the matrix.

At the start of each round, the game displays a sequence of visual pulses (flashing pixels or matrix sectors with accompanying tones).

Once the sequence presentation completes, the player must replicate the exact sequence by selecting the corresponding matrix inputs in the correct order.

A successful replication completes the round and appends one additional step to the sequence for the next round.

An incorrect input or timing out immediately breaks the sequence, ending the turn or deducting a life.

The game continues until one of the configured end conditions has been met.

## GAME SETTINGS

### Summary

| Setting | Values | Description |
|----------|----------|----------|
| Max Sequence | Unlimited, 1-255 | Maximum sequence length required for victory. |
| Max Lives | 1-10 | Number of input mistakes allowed before game over. |
| Timed Step | Off, 1-10s | Time limit permitted per individual step input. |
| Sequence Speed | Slow, Normal, Fast, Progressive | Speed at which sequence steps flash. |
| Color Count | 2, 4, 6, 8 | Number of distinct active colors/zones on matrix. |
| Reverse Mode | Off, On | Player must enter the sequence in reverse order. |
| Mirror Mode | Off, On | Inverts the positional layout of inputs. |
| Special Steps | Disabled, Low, Medium, High | Frequency of bonus or modifier step flashes. |

### Max Sequence

Limits the total length of the sequence needed to win the game.

Values:

* Unlimited
* 1 - 255

When enabled, the game ends in victory once the player successfully replicates a sequence of this length.

### Max Lives

Sets the number of errors a player can make before elimination.

Values:

* 1 - 10

When set to 1, a single mistake results in an immediate game over.

### Timed Step

Determines whether players have a strict time limit to make each individual input.

Values:

* Off
* 1 - 10 seconds

When enabled, failing to input the next step within the allowed time counts as a mistake.

### Sequence Speed

Controls the playback speed of the light sequence.

Values:

* Slow (1000 ms pulse)
* Normal (500 ms pulse)
* Fast (250 ms pulse)
* Progressive (Speed increases as sequence length grows)

### Color Count

Sets the total number of unique visual zones or colors used on the matrix.

Values:

* 2
* 4
* 6
* 8

Higher counts increase visual complexity and memory difficulty.

### Reverse Mode

Requires the player to enter the demonstrated pattern in reverse order (last to first).

Values:

* Off
* On

### Mirror Mode

Flips the spatial position of the input targets relative to where they flash on the display.

Values:

* Off
* On

### Special Steps

Determines how frequently special signal steps appear within a standard sequence.

Values:

* Disabled
* Low
* Medium
* High

## SPECIAL STEPS

Special steps are visually identified by distinct blinking animations or unique pixel indicators during sequence presentation.

When special step settings are set to disabled, no special steps are generated.

### Summary

| Type | Visualization | Effect | Default Reward | Availability |
|--------|--------|--------|--------|--------|
| Bonus Step | Gold | Bonus score multiplier | +2,500 | All |
| Double Tap | Flash (White) | Requires hitting step twice | +5,000 | All |
| Stealth Step | Fade Out | Disappears instantly upon playback | +7,500 | Advanced modes |
| Time Extra | Blue Pulse | Adds time to total match timer | +5 seconds | Timed modes |
| Shield Step | Cyan | Forgives next input mistake | N/A | Multiplayer |

#### Bonus Steps

A special step that awards additional score when successfully recalled.

Values:

* 0 - 50 active

Visualization:

* Gold flashing pulse

Effect:

* Grants substantial bonus points upon successful entry

Reward:

* +2,500 points (default)

#### Double Taps

A modifier step requiring two consecutive inputs on the same target.

Values:

* 0 - 50 active

Visualization:

* Rapid double white flash

Effect:

* Must be pressed twice in succession during player recall phase

Reward:

* +5,000 points (default)

#### Stealth Steps

A difficult step that flashes briefly without persisting visually.

Values:

* 0 - 50 active

Visualization:

* Instant flash and immediate fade-out

Effect:

* Requires high visual recognition and memory

Reward:

* +7,500 points (default)

#### Time Extras

Grants additional overall match time when entered correctly.

Values:

* 0 - 50 active

Visualization:

* Pulsing blue step

Effect:

* Extends match duration

Reward:

* +5 seconds (default)

Only available in timed game modes.

#### Shield Steps

Protects the player against their next mistake.

Values:

* 0 - 1 active

Visualization:

* Pulsing cyan step

Effect:

* Absorbs one sequence error without losing a life

Only available in multi-life or multiplayer modes.

## SCORING METHODS

### Classic Score

The score equals:

Sequence Length Achieved × 1,000

### Perfect Streak Score

The score equals:

Completed Steps² × 100

Deducts 50% score penalty on any mistake.

### Speed Recall Score

Score equals:

(Base Step Value + Time Remaining Bonus) × Multiplier

Calculated based on how rapidly the sequence is successfully entered.

### Custom Score

Multiple scoring methods may be combined.

Example:

Sequence Length × 1,000 + Special Step Bonuses + Speed Multiplier

## END CONDITIONS

Depending on the selected settings, a game may end when:

* The player makes maximum allowed mistakes (Lives reach 0).
* The player reaches the configured Max Sequence length.
* The step timer or match timer expires.
* A player forfeits in a versus match.

## VARIANTS

### Summary

The following variants are recommended configurations. Custom configurations may also be created.

| Preset | Players | Timed Step | Sequence Speed | Main Objective |
|---------|---------|---------|---------|---------|
| Classic Memory | 1 | Off | Progressive | Reach highest sequence possible |
| Speed Recall | 1 | 2 seconds | Fast | Maximize score under strict step timers |
| Reverse Mind | 1 | Off | Normal | Replicate sequence in reverse order |
| Memory War | 2 | 3 seconds | Progressive | Outlast opponent on shared sequence |
| Chaos Matrix | 1-2 | 5 seconds | Progressive | Replicate sequences with special steps |

### CLASSIC MEMORY

#### Objective

Memorize and repeat progressively longer sequences with no time limit.

#### Settings

* Max Sequence: Unlimited
* Max Lives: 1
* Timed Step: Off
* Sequence Speed: Progressive
* Color Count: 4
* Reverse Mode: Off
* Mirror Mode: Off
* Special Steps: Disabled

#### Scoring

Classic Score

### SPEED RECALL

#### Objective

Replicate sequence steps as rapidly as possible under strict time constraints.

#### Settings

* Max Sequence: 50
* Max Lives: 3
* Timed Step: 2 seconds
* Sequence Speed: Fast
* Color Count: 4
* Special Steps: Optional

#### Scoring

Speed Recall Score

### REVERSE MIND

#### Objective

Replicate the demonstrated pattern back to front.

#### Settings

* Max Sequence: Unlimited
* Max Lives: 1
* Timed Step: Off
* Sequence Speed: Normal
* Color Count: 4
* Reverse Mode: On
* Mirror Mode: Off

#### Scoring

Classic Score × 1.5 Multiplier

### MEMORY WAR

#### Objective

Take turns completing the growing sequence until one player makes a mistake.

#### Rules

Players alternate turns trying to repeat the identical expanding sequence.

The first player to fail an entry loses the round.

#### Settings

* Players: 2
* Max Sequence: Unlimited
* Max Lives: 1
* Timed Step: 3 seconds
* Sequence Speed: Progressive
* Color Count: 4
* Shield Steps: Enabled

#### Scoring

Perfect Streak Score

Winner:

* Surviving player with zero mistakes.

### CHAOS MATRIX

#### Objective

Navigate unpredictable sequences containing complex spatial modifiers and special steps.

#### Settings

* Max Sequence: 100
* Max Lives: 3
* Timed Step: 5 seconds
* Sequence Speed: Progressive
* Color Count: 8
* Special Steps: High

#### Scoring

Custom Score

#### End of Game

* Max Sequence reached or all lives depleted.