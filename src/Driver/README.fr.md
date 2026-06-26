# Multi-Servo Driver Configuration and Reference (SMS/STS)
> 🌍 Lire en [Français](README.fr.md).
---

This folder contains the low-level driver, UART Half-Duplex bus management, command console processing, and inverse kinematic models for controlling the 4 FEETECH servomotors (STS3215).

## Communication Bus Configuration

The driver orchestrates two asynchronous serial communication links on the Arduino Mega:
* **Servomotor Bus (`Serial1`):** Half-Duplex link operating at **1,000,000 bps**. The global instance `st` from the `SMS_STS` library is bound to this port.
* **Console Link (`Serial`):** USB serial link to the computer operating at **115,200 bps**.

### Default Dynamic Parameters
* **Speed (`speed`):** `1500` steps/s
* **Acceleration (`acc`):** `50` (Feetech internal unit)
* **Pre-calibration Positions (`precal`):** `{4600, 5100, 4700, 1100}` (used as a baseline during mechanical alignment).
* **Servo Identifiers:** The bus synchronously targets hardware IDs `1`, `2`, `3`, and `4`.

---

## Function Reference

### 1. Initialization and Hardware Management

#### `void initSerial()`
Initializes the `Serial` (115,200 baud) and `Serial1` (1,000,000 baud) ports. Assigns the Feetech library stream pointer to `Serial1`. Blocks execution for 100 ms to stabilize the link.

#### `void initServoManual(s16 offset[4])`
Blocks execution inside a `while (!areServoSetup)` loop. Continuously reads raw position commands from the serial console and applies them to the motors without offsets. Upon exiting the loop (reception of the `o` command), it calculates and increments the final system offsets.

#### `void hardReset()`
Sends a complete factory reset command using the global broadcast address `254`. Requires prior un-locking of the EPROM.

#### `void setID(u8 ID)`
Modifies the identifier of a single connected servo using the broadcast address `254`. *Warning: Only one servo must be present on the bus during this operation.*

#### `void setTargetID(u8 ID, u8 targetID)`
Modifies the ID of the target servo specified by `targetID` to assign it the new `ID` value.

#### `void setMode(u8 ID, int mode)`
Configures the operating mode of the servo in its `SMS_STS_MODE` EPROM register:
* `0`: Position Mode
* `1` / `2`: Continuous Speed Mode
* `3`: Stepper Mode

#### `void enableMultiLoop(u8 ID, u16 minAngle, u16 maxAngle)`
Configures the minimum and maximum angle limits by writing to the EPROM. Allows switching the servo into absolute multi-turn mode (for example, with the values `1, 1`).

---

### 2. Data Reading (Feedback)

#### `void ping(u8 ID)`
Sends a Ping request to servo `ID`. Prints the result or an error to the serial console.

#### `s16 getPosition(u8 ID)`
Queries the servo to retrieve the current absolute position of its magnetic encoder via the `st.ReadPos()` function. Returns the value and prints it to the console.

#### `s16 getLoad(u8 ID)`
Reads and returns the mechanical load (instantaneous torque) applied to the motor via `st.ReadLoad()`.

#### `void printPositions(s16 position[4])`
Formats and prints a line to the serial console containing the current positions of the 4 servos separated by vertical bars.

---

### 3. Motion Control

#### `void setPosition(u8 ID