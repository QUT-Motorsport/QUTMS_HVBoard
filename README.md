![QUTMS_Banner](https://raw.githubusercontent.com/Technosasquach/QUTMS_Master/master/src/qutmsBanner.jpg)
# HV Board
The HV Board resides inside the HV box directly infront of the accumulator and monitors the tractive system in various ways.

## Features

- CANBUS Interface using the MCP2517 ic
- Isolated analog TSAL enable/disable signalling
- IMD state sensing and powering
- Tractive system current measurement
- UART debugging header

## Functions

Whilst the BSPD circitry is located on the shutdown board, the HV board powers the device and has an amplifier to boost the signal before it makes its way through the wiring harness.

In order to detect when the tractive system has a voltage more than 60V present, there is an isolated circuit on board that compares a divided TS voltage with a reference voltage. It also has a mosfet to drive the TS active and TS inactive signals to the TSAL board.
