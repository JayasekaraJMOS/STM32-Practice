# Week 2: Bare-Metal GPIO (Register Level) 🔧

Driving GPIO pins on the **STM32 NUCLEO-F446RE** by writing directly to hardware registers — no HAL, no CubeMX-generated GPIO code. Everything is worked out from ST's own documents.

---

## 📚 Documents Used

| Document | What it gives you | Search tip (Ctrl+F) |
|---|---|---|
| **RM0390** – Reference manual | Register addresses, offsets, bit fields | `register boundary addresses`, `GPIOx_MODER` |
| **DS10693** – STM32F446 datasheet | Chip pins, pin types, alternate functions | `SWDIO`, `PA13` |
| **UM1724** – Nucleo-64 user manual | Which board header pin is which GPIO | `ARDUINO connectors on NUCLEO-F446RE`, `B1 USER` |

---

## [Day 8: Bare-Metal GPIO & Bit Manipulation](Day_08_Bare_Metal_GPIO/5_Bare-Metal_GPIO_BitManipulation/)

**Project:** `5_Bare-Metal_GPIO_BitManipulation` — set every usable pin on ports A, B and C as output and drive it HIGH.

### 1. Register address = Base + Offset
- Base addresses come from **RM0390 §2.2.2, Table 1 (register boundary addresses)**.
- Each register page only gives an **address offset**.

| Peripheral | Base | Register | Offset | Address |
|---|---|---|---|---|
| RCC | `0x40023800` | `RCC_AHB1ENR` | `0x30` | `0x40023830` |
| GPIOA | `0x40020000` | `MODER` / `BSRR` | `0x00` / `0x18` | `0x40020000` / `0x40020018` |
| GPIOB | `0x40020400` | `MODER` / `BSRR` | `0x00` / `0x18` | `0x40020400` / `0x40020418` |
| GPIOC | `0x40020800` | `MODER` / `BSRR` | `0x00` / `0x18` | `0x40020800` / `0x40020818` |

```c
#define GPIOA_MODER (*(volatile uint32_t*)(GPIOA_BASE + 0x00U))
```
⚠️ Bracket `(BASE + OFFSET)` **before** the cast — otherwise `+` becomes pointer arithmetic (×4).

### 2. Enable the peripheral clock first
- All peripheral clocks are **off at reset** to save power.
- Writes to a GPIO register are ignored until its clock is on: `RCC_AHB1ENR` bit 0 = GPIOA, bit 1 = GPIOB, bit 2 = GPIOC.

### 3. MODER — 2 bits per pin
- **MODERy controls pin y** (PA5 → `GPIOA_MODER`, MODER5, bits 11:10).
- Pin `y` uses bits `2y+1 : 2y`.

| Bits | Mode |
|---|---|
| `00` | Input (reset) |
| `01` | **Output** |
| `10` | Alternate function |
| `11` | Analog |

Each hex digit covers 2 pins → `0x5` = `01 01` = two outputs.

### 4. Reset values & debug pins
- `GPIOA_MODER` resets to `0xA8000000` → PA13, PA14, PA15 start in AF mode.
- **PA13 = SWDIO, PA14 = SWCLK** — the ST-Link uses these to download code and debug. **Never change them**, or the board stops connecting ("Connect under reset" needed).
- PA15 / PB3 / PB4 are JTAG-only — free to use, because the Nucleo uses SWD.

### 5. Clear first, then set
OR can only turn bits on, so clear the field before writing a new value:

```c
GPIOA_MODER &= 0x3C000000U;   // keep PA13, PA14; clear everything else
GPIOA_MODER |= 0x41555555U;   // PA0–PA12 and PA15 = 01 (output)
```

```
Reset:     10 10 10 00 00 ... 00   (0xA8000000)
& mask:    00 10 10 00 00 ... 00   (0x28000000)
| value:   01 10 10 01 01 ... 01   (0x69555555)
Pin:       15 14 13 12 11 ...  0
```
Bug found along the way: masking with `0xFC000000` kept PA15 = `10`, and `10 | 01 = 11` → **analog** instead of output.

### 6. BSRR — atomic set/reset
- Bits 0–15 `BSy` → pin HIGH, bits 16–31 `BRy` → pin LOW. Writing `0` does nothing.
- Write-only and atomic: `GPIOA_BSRR = (1U << 5);` (no read-modify-write needed).

### 7. Nucleo board pins to watch
| Pin | Used for |
|---|---|
| PA5 | Green LED LD2 (Arduino D13) |
| PC13 | Blue user button B1 — keep as input (`0x51555555` skips it) |
| PA2 / PA3 | USART2 to ST-Link virtual COM port (printf) |
| PC14 / PC15 | 32.768 kHz LSE crystal |

### 8. Finding any pin myself
1. **UM1724, Table 19** → board pin → GPIO name (D7 → **PA8**).
2. Name → port **A**, position **8** (position in the registers, not the chip's leg number).
3. **RM0390** → GPIOA base + `MODER8` (bits 17:16) → `1U << 16`.
4. **DS10693** pin table → check it's an `I/O` pin on LQFP64 and free on the board.

---

## 🚀 Running
1. STM32CubeIDE → **File > Open Projects from File System…** → select the project folder.
2. Build (`Ctrl+B`), connect the Nucleo, Run.
3. LD2 lights up; every Arduino D/A pin measures ~3.3 V to GND.

---

## 👤 Author
- **Name:** Omidu Sanvida
- **GitHub:** [@JayasekaraJMOS](https://github.com/JayasekaraJMOS)
