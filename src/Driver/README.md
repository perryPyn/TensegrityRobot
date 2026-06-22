# Feetech Multi-Servo Control Driver (SMS/STS)

This repository contains the driver and geometric utilities used to control a 4-servo setup of Feetech SMS/STS series smart servos (specifically the STS3215 model). It handles UART bus communication, manual offset calibration, and a kinematic inverse model for motion transformation.

## Global Configuration

The driver applies specific dynamic parameters by default to ensure smooth and stable displacements:
* **Default Speed (`speed`):** `1500` steps/s
* **Default Acceleration (`acc`):** `30` ($100\text{ steps/s}^2$)
* **Target Servo IDs:** Synchronous bus targeting IDs `1`, `2`, `3`, and `4`.

---

## Function Reference Table

| Function | Description |
| :--- | :--- |
| `initSerial()` | Initializes the dual UART communication ports (PC and Servos). |
| `initServoManual(offset)` | Blocks execution for manual calibration via the console. |
| `hardReset()` | Restores all connected servos on the bus to factory default settings. |
| `setID(ID)` | Assigns a new unique identifier to the connected servo. |
| `setMode(ID, mode)` | Switches between position control, continuous speed, or stepper modes. |
| `enableMultiLoop(ID, maxAngle)` | Disables angle limits to allow multi-turn operations. |
| `ping(ID)` | Pings the target ID to verify hardware communication. |
| `getPosition(ID)` | Reads and prints the current absolute feedback position from the encoder. |
| `getLoad(ID)` | Reads and prints the current mechanical load/torque on the motor. |
| `setPosition(ID, Position)` | Commands a single servo to move to a specific position. |
| `setPositionsRaw(Position)` | Broadcasts a synchronous position packet to all 4 servos (ignores offsets). |
| `setPositions(Position, Offset)` | Broadcasts a synchronous position packet to all 4 servos while applying offsets. |
| `computePosition(alpha, position)` | Simple kinematic model converting plate inclination ($\alpha$) into individual servo steps. |