# DRAW (MANUAL)

## DESCRIPTION

Draw is a pixel-art creation utility designed for low-resolution matrix displays ($5 \times 72$ horizontal playfield or $16 \times 16$ square matrix). It allows creators to paint, edit, and store visual artwork using two joysticks for intuitive canvas navigation and color manipulation. A secondary LCD2004 display provides real-time tool information, canvas metrics, and storage management menus.

## ALTERNATIVE NAMES

* LED Artist
* Matrix Canvas
* Pixel Painter
* Paint

## TAGS

1 Player, Utility, Creative, Pixel Art, Tool

## ORIENTATION

Both ($5 \times 72$ or $16 \times 16$)

## HARDWARE INTERFACE

### Displays

* **Main LED Matrix ($5 \times 72$ or $16 \times 16$):** Displays the active canvas, active cursor position, and visual feedback.
* **LCD2004 (20x4 Character Display):** Displays application status, active tool settings, color values, file navigation, and confirmation prompts.

### Dual Joystick Controls

| Control Input | Function | Description |
| ----- | ----- | ----- |
| **Joystick 1 (Position & Navigation)** | X / Y Movement | Moves the drawing cursor across the matrix canvas. |
| **Joystick 1 Button** | Action / Paint | Toggles pixel state or applies the currently selected tool/color. |
| **Joystick 2 (Tools & Colors)** | Up / Down | Cycles through available drawing tools and LCD menu items. |
| **Joystick 2 (Tools & Colors)** | Left / Right | Cycles through RGB colors or adjusts tool parameters (e.g., brush size). |
| **Joystick 2 Button** | Mode / Menu | Opens the Save/Load menu on the LCD2004 display or toggles modes. |

---

## CORE FEATURES

### Dual-Joystick Canvas Navigation

The application uses dual inputs to separate spatial positioning from tool adjustment:
* **Cursor Control:** Joystick 1 controls the pixel cursor position on the main matrix screen. The cursor blinks at regular intervals to remain visible regardless of background color.
* **Tool & Color Selection:** Joystick 2 modifies drawing parameters independently without disrupting cursor placement.

### Drawing Tools

Draw includes multiple basic painting modes tailored for low-resolution matrix displays:

* **Pencil (Single Pixel):** Places or toggles a single pixel at the cursor's location.
* **Line Tool:** Selects a start pixel and endpoint to render straight lines across the grid.
* **Fill / Bucket:** Fills connected pixels of the same color with the active color.
* **Eraser:** Clears targeted pixels (turns them off / resets to black).
* **Clear Canvas:** Instantly resets all pixels on the main matrix to off.

### Color Management

Supports multi-color matrix hardware (e.g., WS2812B RGB LEDs) or single-color intensity variations:
* Preset palette cycling via Joystick 2 (Red, Green, Blue, Yellow, Cyan, Magenta, White, Off).
* Custom RGB hue adjustment displayed on the LCD2004 screen.

---

## LCD2004 DISPLAY INTERFACE

The LCD2004 screen acts as the primary control center and menu system during editing and file operations.

### Standard Editing Screen Layout

```
+--------------------+
| TOOL: Pencil       |
| COLOR: Red [255,0,0]|
| POS: X:12 Y:03     |
| [J2-Btn: Main Menu]|
+--------------------+
```

* **Line 1:** Active tool name and parameters (e.g., Pencil, Eraser, Fill).
* **Line 2:** Active color name and RGB values.
* **Line 3:** Current cursor coordinates ($X, Y$).
* **Line 4:** Contextual button hints and action feedback.

---

## STORAGE & FILE MANAGEMENT (SAVE / LOAD)

The LCD2004 display provides a file management system for persistent artwork storage (on internal flash or SD storage).

### Save Functionality

1. Press **Joystick 2 Button** to enter the **Main Menu** on the LCD2004 screen.
2. Select **Save Artwork** using Joystick 2 (Up/Down) and press Joystick 2 Button to confirm.
3. Choose a target file slot (`SLOT_01` to `SLOT_99`) or enter a custom filename.
4. Confirm save. The current pixel matrix state is written to persistent storage.

### Load Functionality

1. Open the **Main Menu** using **Joystick 2 Button**.
2. Select **Load Artwork**.
3. Scroll through saved files on the LCD2004 screen using Joystick 2.
4. Press **Joystick 1 Button** or **Joystick 2 Button** to confirm loading.
5. The selected image immediately renders onto the main LED matrix display.

### Quick Actions

* **Quick Save:** Holding Joystick 2 Button for 2 seconds saves directly to the last active file slot.
* **Preview Mode:** Browsing files on the LCD2004 instantly renders a low-latency preview on the matrix display.