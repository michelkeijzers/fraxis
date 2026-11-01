# AUTORUN (MANUAL)

## DESCRIPTION

AutoRun is an automated diagnostic and hardware test mode designed for quick system verification. It performs high-speed random operations to verify matrix pixel functionality, test dedicated 3mm status LEDs, and validate display outputs without requiring any manual user interaction.

## ALTERNATIVE NAMES

-

## TAGS

Automated, Diagnostics, Hardware Verification, Performance Test, System Check, 

## ORIENTATION

n.a.

## CORE FEATURES

### Automated Hardware Check

The test sequence executes automatically upon launch, rapidly toggling pixels across the entire matrix.

### Visual Pixel Matrix Check

Quickly lights up random pixels across the display matrix to identify dead or stuck pixels, broken lines, or faulty display driver outputs.

### Score & Time Display Verification

Slow/fast increasing of the score displays to verify numerical display segment driving and communication buses.

The Time display shows the time.

### Dedicated 3mm LED Testing

Directly drives and toggles discrete 3mm status LEDs (non-strip components) on the controller board or front panel to confirm discrete IO output lines are fully operational.

### Zero User Dependency

Operates fully autonomously without needing joystick inputs, button presses, or external inputs.

## SETTINGS

AutoRun does not feature configurable settings.

## HARDWARE OUTPUT SPECIFICATION

| Hardware Output | Driven Component | Verification Objective |
|---|---|---|
| LED Matrix | $16 \times 16$ or $5 \times 72$ Array | Pixel activity, row/column drivers, color lines |
| Numeric Displays | Score & Time Displays | Bus integrity, segment driver ICs |
| Discrete Indicators | Dedicated 3mm LEDs | Individual micro-controller GPIO outputs |

## HARDWARE & DISPLAY OUTPUT MATRIX

### Matrix Pixel Activity

* **Visualization:** High-speed random pixel lighting.
* **Effect:** Illuminates pixels across the matrix layout.
* **Purpose:** Allows quick detection of inactive pixels, shorted LED rows, or flickering matrix sections.

### Dedicated 3mm LEDs

* **Visualization:** Toggled discrete LED indicators.
* **Effect:** Alternates state or flashes discrete 3mm indicators on the hardware board.
* **Purpose:** Validates individual GPIO lines and driver transistors for dedicated status LEDs.

### Score and Time Displays

* **Visualization:** Continuous numerical sequence updates.
* **Effect:** Rapidly alters values on score and timer display segments.
* **Purpose:** Confirms proper communication over output buses to numeric display hardware.

## DIAGNOSTIC EXECUTION

### Operation Sequence

1. **Initialization:** Clears previous display states upon launch.
2. **Execution:** Runs the random pixel generation, numeric display updates, and 3mm LED toggling.
3. **Looping:** Runs indefinitely until the system is stopped or navigated back to the main menu.

### Pass/Fail Verification Criteria

During the diagnostic execution, inspect the hardware for the following:

* **Pass:** All matrix pixels respond, numerical displays rapidly show changing numbers, and all 3mm discrete LEDs flash.
* **Fail:** Dead pixels/columns on the matrix, unresponsive score/time displays, or non-functional 3mm LEDs indicate a hardware or wiring fault on that specific output line.
