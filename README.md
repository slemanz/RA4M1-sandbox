# RA4M1 Sandbox

This project is a bare-metal firmware development environment for the **Renesas
RA4M1** microcontroller (found on the Arduino UNO R4 Minima). It is designed
without the use of standard frameworks like Arduino or CMSIS-Core, focusing on
direct register manipulation and clean architectural separation.

## Architecture

The firmware follows a modular, five-layer architecture to ensure portability and maintainability:

* **[App:](app/)** High-level application logic.
* **[Common:](common/)** Generic library containing abstract utilities and shared code.
* **[Interface:](interface/)** An abstraction bridge between the Common and Drivers layers, allowing for easier MCU migration.
* **[Drivers:](drivers/)** Hardware-specific implementations that interact directly with the RA4M1 peripherals.
* **Hardware:** The physical board and peripheral layer.

```
        ┌────────────────┐
        │      APP       │  
        ├────────────────┤
        │     COMMON     │  
        ├────────────────┤
        │   INTERFACE    │  
        ├────────────────┤
        │    DRIVERS     │  
        ├────────────────┤
        │    HARDWARE    │  
        └────────────────┘
```

## Hardware & Tools

* **Board:** Arduino UNO R4 Minima.
* **Debugger/Programmer:** SEGGER J-Link.
* **Development:** Bare-metal C (no external frameworks).
* **Debugging:** Ozone (project file provided as `app.jdebug`).

## Build Instructions

The build system uses a [Makefile](app/Makefile) located inside the app directory.

**Build the project:**

```bash
make all
```

**Clean build artifacts:**

```bash
make clean
```

**Flash the target via J-Link:**

```bash
make load
```

## Pinout Reference

| Arduino Pin | MCU Pin | Function |
| --- | --- | --- |
| Pin 13 | P111 | GPT3_A (Blinky LED) |
| Pin 8 | P304 | GPT7_A |
| Pin 1 | P302 | SCI2_TXD (UART) |
| Pin 0 | P301 | SCI2_RXD (UART) |

*Note: The UART interface (SCI2) is configured for **115200 baud**.*

## Release History


## License

This project is licensed under the **MIT License**.

Feel free to use, copy, or modify this code as you wish. However, if your
hardware decides to go on strike, catch fire, or summon an ancient demon because
of a bug, please remember: I've never met you, and I certainly didn't write that
specific line of code. Use it at your own risk!