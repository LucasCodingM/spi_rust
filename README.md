# SPI Interface Between STM32F4 (Rust) and Arduino

This project demonstrates SPI communication between an STM32F407VGT6 microcontroller (programmed in Rust) and an Arduino Uno. The STM32 acts as the **SPI master**, while the Arduino is the **SPI slave**.

## 🚀 Features

- SPI master implementation in Rust (STM32F4)
- Manual control of Slave Select (SS) line (PA4)
- SPI communication with Arduino using standard `SPI.h` library
- "Hello World" message transmission every 1 second

---

## 🛠 Hardware Setup

### Required Components

- STM32F407VGT6 Dev Board
- Arduino Uno
- Logic Analyzer (optional but recommended)
- Level shifter (optional, if needed for voltage matching)
- Jumper wires, breadboard

### Wiring Table

| STM32F4 (3.3V) | Arduino Uno (5V) | SPI Role      |
|----------------|------------------|---------------|
| PB3 (SPI1_SCK) | D13              | Clock         |
| PB4 (SPI1_MISO)| D12              | Master In     |
| PB5 (SPI1_MOSI)| D11              | Master Out    |
| PA4 (GPIO)     | D10              | Slave Select  |
| GND            | GND              | Common Ground |

> ⚠️ Voltage compatibility is critical! Use a level shifter if needed between 3.3V (STM32) and 5V (Arduino).

---


