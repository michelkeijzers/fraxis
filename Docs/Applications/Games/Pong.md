# PONG (MANUAL)

## DESCRIPTION

Defend your goal line while attempting to hit the ball past your opponent's paddle. The game takes place on a constrained matrix grid ($5 \times 72$ horizontal playfield or $16 \times 16$ square matrix). The objective depends on the selected game mode and settings, typically to reach a target score or survive as long as possible.

Special elements or power-up pixels may appear on the playing field. Passing the ball through these elements triggers special effects or grants bonus points.

## ALTERNATIVE NAMES

* Tele-Tennis
* LED Pong
* Vector Pong

## TAGS

1 Player, 2 Players, Action, Arcade, Bouncing, Reflex, Timed, Versus

## ORIENTATION

Horizontal ($5 \times 72$), Square ($16 \times 16$)

## CORE RULES

The playfield is bounded on the top and bottom walls, with player goal lines situated at the left and right ends (or top and bottom in vertical configurations).

Each player controls a vertical paddle situated near their goal line.

The ball spawns at the center and moves diagonally or horizontally across the grid.

When the ball hits a top or bottom boundary, it bounces off at an equal angle.

When the ball collides with a player's paddle, it reflects back toward the opponent. The hit position on the paddle can alter the trajectory angle or acceleration of the ball.

If the ball crosses a player's goal line without being deflected by their paddle, the opponent earns a point (or the defending player loses a life).

The game continues until one of the configured end conditions has been met.

## GAME SETTINGS

### Summary

| Setting | Values | Description |
|----------|----------|----------|
| Target Score | Unlimited, 1-99 | Game ends when a player reaches this score. |
| Max Lives | Unlimited, 1-10 | Number of misses permitted before elimination. |
| Timed | Off, 10-300s | Ends the game when the match timer expires. |
| Ball Speed | Low, Medium, High, Dynamic | Base movement velocity of the ball. |
| Paddle Size | Small (1 px), Medium (2 px), Large (3 px) | Vertical height of player paddles. |
| Spin Control | Off, On | Allows changing bounce angle based on paddle movement. |
| Obstacles | 0-5 | Number of stationary wall blocks inside the field. |
| Power-Up Spawn Rate | Disabled, Low, Medium, High | Frequency of special visual elements spawning. |

### Target Score

Determines the score required to achieve victory.

Values:

* Unlimited
* 1 - 99

When enabled, the first player to reach the specified score wins immediately.

### Max Lives

Limits the number of times a player may miss the ball before losing.

Values:

* Unlimited
* 1 - 10

Used primarily in single-player or survival game modes.

### Timed

Determines whether the match has a strict time limit.

Values:

* Off
* 10 - 300 seconds

When enabled, the game ends when the timer expires. The player with the highest score wins.

### Ball Speed

Sets the initial speed of the ball across the LED matrix.

Values:

* Low (1 step per frame)
* Medium (1.5 steps per frame)
* High (2 steps per frame)
* Dynamic (Increases after each successful volley)

### Paddle Size

Sets the length of the paddles relative to the matrix height (e.g., 5-pixel height).

Values:

* Small (1 pixel)
* Medium (2 pixels)
* Large (3 pixels)

### Spin Control

Allows players to modify the bounce angle by moving the paddle while making contact with the ball.

Values:

* Off
* On

### Obstacles

Spawns static barrier pixels on the playing field that reflect the ball upon contact.

Values:

* 0 - 5

### Power-Up Spawn Rate

Determines how frequently special power-up pixels appear on the playfield.

Values:

* Disabled
* Low
* Medium
* High

### SPECIAL ELEMENTS

Special elements are visually identified by pulsing single-pixel indicators on the grid.

When special element rates are set to disabled, no elements are generated.

#### Summary

| Type | Visualization | Effect | Default Reward | Availability |
|--------|--------|--------|--------|--------|
| Speed Booster | Yellow | Accelerates ball speed | +50 pts | All |
| Paddle Enlarger | Green | Temporarily expands paddle size | N/A | All |
| Multi-Ball | White | Splits ball into two active balls | +100 pts | All |
| Slow Motion | Blue | Decreases ball velocity temporarily | N/A | All |
| Shield Barrier | Cyan | Blocks one goal point automatically | N/A | Versus modes |

#### Speed Booster

A special element that increases ball velocity upon contact.

Values:

* 0 - 5 active

Visualization:

* Pulsing yellow pixel

Effect:

* Instantly boosts ball speed by 25% for the current rally

Reward:

* +50 bonus points (default)

#### Paddle Enlarger

A beneficial pickup that increases paddle length.

Values:

* 0 - 2 active

Visualization:

* Pulsing green pixel

Effect:

* Expands the collector paddle by +1 pixel length for 10 seconds

Reward:

* Temporary strategic defense advantage

#### Multi-Ball

Triggers an additional ball into play.

Values:

* 0 - 1 active

Visualization:

* Pulsing white pixel

Effect:

* Generates a duplicate ball moving in the opposite direction

Reward:

* +100 bonus points when triggered

#### Slow Motion

Decreases ball speed to assist defending players.

Values:

* 0 - 3 active

Visualization:

* Pulsing blue pixel

Effect:

* Reduces ball velocity by 30% for 5 seconds

Reward:

* Enhanced reaction time

#### Shield Barrier

Deploys a temporary protective barrier behind the paddle.

Values:

* 0 - 2 active

Visualization:

* Pulsing cyan pixel

Effect:

* Covers the player's goal line for one ball hit

Only available in multiplayer game modes.

## SCORING METHODS

### Standard Score

The player earns 1 point each time the opponent fails to return the ball.

First player to reach the Target Score wins.

### Rally Score

Points equal:

Volleys in Current Rally × 100

Re-sets to zero when a goal is scored.

### Time Attack Score

Score equals:

Total Successful Hits × 50 + Power-Up Bonuses

### Custom Score

Multiple score systems may be combined.

Example:

Goals Scored × 1,000 + Longest Rally × 500 + Special Element Rewards

## END CONDITIONS

Depending on the selected settings, a match may end when:

* A player reaches the Target Score.
* A player loses all lives (Max Lives reaches 0).
* The match timer expires.
* A player forfeits or disconnects.

## VARIANTS

### Summary

The following variants are recommended configurations. Custom configurations may also be created.

| Preset | Players | Timed | Ball Speed | Main Objective |
|---------|---------|---------|---------|---------|
| Classic Versus | 2 | No | Medium | Reach target score (11 points) |
| Wall Bounce (Solo) | 1 | No | Dynamic | Maximum rally off back wall |
| Speed Demon | 1-2 | Yes | High | Maximum score before time expires |
| Obstacle Course | 2 | Optional | Medium | Score while dodging grid barriers |
| Survival | 1 | No | Dynamic | Keep ball active with limited lives |

### CLASSIC VERSUS

#### Objective

Defeat your opponent by reaching 11 points first.

#### Settings

* Target Score: 11
* Max Lives: Unlimited
* Timed: Off
* Ball Speed: Medium
* Paddle Size: Medium (2 px)
* Spin Control: On
* Obstacles: 0
* Power-Ups: Disabled

#### Scoring

Standard Score

### WALL BOUNCE (SOLO)

#### Objective

Bounce the ball against a solid back wall as many times as possible without missing.

#### Settings

* Players: 1
* Target Score: Unlimited
* Max Lives: 1
* Timed: Off
* Ball Speed: Dynamic
* Paddle Size: Medium (2 px)
* Spin Control: On

#### Scoring

Rally Score

### SPEED DEMON

#### Objective

Achieve the highest score possible within a limited timeframe under fast ball conditions.

#### Settings

* Timed: 60 seconds
* Target Score: Unlimited
* Ball Speed: High
* Paddle Size: Small (1 px)
* Power-Up Spawn Rate: High

#### Scoring

Time Attack Score

### OBSTACLE COURSE

#### Objective

Outmaneuver your opponent while predicting complex ball trajectories off internal wall blocks.

#### Settings

* Players: 2
* Target Score: 7
* Obstacles: 3
* Ball Speed: Medium
* Spin Control: On

#### Scoring

Standard Score

Winner:

* First player to reach 7 points.

### SURVIVAL

#### Objective

Keep the ball in play as long as possible while ball velocity increases dynamically.

#### Settings

* Players: 1
* Max Lives: 3
* Ball Speed: Dynamic
* Paddle Size: Medium (2 px)
* Power-Up Spawn Rate: Medium

#### Scoring

Rally Score + Power-Up Bonuses

#### End of Game

* All lives lost.