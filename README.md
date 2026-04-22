<h1 align="center">ElectroMazeSTM</h1>
<p align="center">
  <b>Tilt-stage firmware for the maze-solving system</b><br>
</p>

<p align="center">
  <img alt="C" src="https://img.shields.io/badge/C-00599C?style=flat&logo=c&logoColor=white">
  <img alt="STM32" src="https://img.shields.io/badge/STM32-03234B?style=flat&logo=stmicroelectronics&logoColor=white">
  <img alt="ChibiOS" src="https://img.shields.io/badge/ChibiOS%2FRT-F39200?style=flat">
  <img alt="GCC ARM" src="https://img.shields.io/badge/GCC%20arm--none--eabi-333?style=flat">
</p>

<p align="center">
  <img width="600" alt="Physical tilt-stage rig" src="https://github.com/user-attachments/assets/72a2bfaa-150c-439d-add1-8218a801faf1">
</p>

---

> Part of a 3-repo thesis project alongside **[ElectroMazeCV](https://github.com/veparkh/ElectroMazeCV)** (vision & control software) and **[ElectroMaze](https://github.com/veparkh/ElectroMaze)** (Android app).

## Role in the system

```
  Host PC (Python)    ──►  UART  ──►  STM32F767 (this repo)
  · vision + CV                        · IMU sensor fusion (Fusion AHRS)
  · pathfinding                        · roll/pitch setpoint tracking
  · high-level controller              · motor driver
                                       │
                                       ▼
                                 Two-axis tilt stage
```

## What it does

- **UART protocol** with the host PC — receives roll / pitch setpoints, sends back telemetry.
- **IMU sensor fusion** — reads gyroscope + accelerometer (+ magnetometer when available), runs the [Fusion AHRS](https://github.com/xioTechnologies/Fusion) library (Madgwick-style orientation filter with quaternion output), converts to Euler angles.
- **Local control loop** — compares host setpoint against measured orientation, drives the actuators to match. Loop runs on the MCU, independent of host latency.
- **Multi-threaded architecture** — ChibiOS/RT threads split responsibilities: sensor acquisition, AHRS update, UART I/O, and motor update each run in their own context.

## Target

- **Board:** ST Nucleo-144 F767ZI
- **MCU:** STM32F767ZI (ARM Cortex-M7 @ 216 MHz)
- **RTOS:** ChibiOS/RT with the `rt-nil` OSAL
- **Toolchain:** `arm-none-eabi-gcc`, link-time GC + LTO enabled

## Layout

```
main.c                          — entry point, kernel start, thread creation
src/
  ├── maze.c                    — top-level tilt-stage logic
  └── serial.c                  — UART protocol parsing / serialisation
engine/src/engine.c             — motor driver and setpoint tracking
uart/src/uart.c                 — UART driver wrapper over ChibiOS HAL
positionSensor/
  ├── Sensors.c                 — IMU driver
  ├── SensorsThread.c           — periodic IMU sampling thread
  ├── FusionAhrs.c              — orientation filter (gyro + accel + mag → quaternion)
  ├── FusionCompass.c           — magnetometer-based tilt correction
  └── FusionOffset.c            — gyroscope bias estimation
cfg/
  ├── chconf.h                  — ChibiOS kernel configuration
  ├── halconf.h                 — HAL driver selection
  └── mcuconf.h                 — MCU-specific clock / peripheral settings
```

## AHRS pipeline

The IMU readings pass through three stages of [Seb Madgwick's Fusion library](https://github.com/xioTechnologies/Fusion):

1. **FusionOffset** continuously estimates and subtracts the gyroscope bias.
2. **FusionAhrs** fuses corrected gyro + accelerometer (+ magnetometer) into a single orientation quaternion.
3. The quaternion is converted to ZYX Euler angles to get roll / pitch / yaw in degrees, which the local control loop compares against the host setpoint.


## Companion repositories

- **[ElectroMazeCV](https://github.com/veparkh/ElectroMazeCV)** — the host-side Python code: computer vision, pathfinding, high-level controller.
- **[ElectroMaze](https://github.com/veparkh/ElectroMaze)** — the Android companion app: live camera view + manual control via phone orientation.

## Status

BSc thesis project — feature-complete and defended (2024).
