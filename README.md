# Embedded Systems Practice: First Week Kick-off 🚀

Repository documenting hands-on embedded systems programming, C fundamentals, microcontroller peripherals, and debugging with the **STM32 NUCLEO-F446RE** board (ARM Cortex-M4 @ 180MHz) using **STM32CubeIDE** and HAL / CMSIS drivers.

---

## 🛠️ Hardware & Tools
- **Target Hardware:** STMicroelectronics NUCLEO-F446RE (ARM Cortex-M4 with FPU)
- **IDE:** STM32CubeIDE
- **Toolchain:** `arm-none-eabi-gcc` / GDB
- **Debugger / Programmer:** On-board ST-LINK/V2-1
- **Language:** Embedded C (C99/C11)

---

## 📅 Weekly Curriculum & Learning Overview

### [Day 1: Bit Manipulation](Day_01_Bit_Manipulation/)
- **Concepts Learned:**
  - Setting, clearing, toggling, and reading individual bits using bitwise operations (`|`, `&`, `^`, `~`, `<<`, `>>`).
  - Creating reusable preprocessor macros (`SET_BIT`, `CLEAR_BIT`, `TOGGLE_BIT`, `READ_BIT`).
  - Bit masking and register field manipulation essential for bare-metal and HAL driver programming.

### [Day 2: Pointers and Memory](Day_02_Pointers_and_Memory/)
- **Concepts Learned:**
  - Understanding pointers, memory addresses, and pointer arithmetic.
  - Traversing and manipulating arrays in place using pointer references.
  - Struct-based memory-mapped I/O: Modeling microcontroller peripheral register blocks using C `struct` pointers and the `volatile` keyword.

### [Day 3: Circular (Ring) Buffer](Day_03_Circular_Buffer/)
- **Concepts Learned:**
  - Designed and implemented a First-In-First-Out (FIFO) circular buffer.
  - Handling Head and Tail indices with modulo arithmetic wrap-around.
  - Tracking full/empty conditions for interrupt-safe asynchronous data transfer (such as UART RX/TX and sensor streaming).

### [Day 4: STM32 GPIO Configuration](Day_04_STM32_GPIO/1_Blinky/)
- **Project:** `1_Blinky`
- **Concepts Learned:**
  - Configuring GPIO pins in STM32CubeIDE (.ioc Device Tree) and HAL drivers.
  - Driving the Nucleo user LED (Green LED, `LD2` on `PA5`) using `HAL_GPIO_WritePin` and `HAL_GPIO_TogglePin`.
  - Polling user button input (`B1` on `PC13`) and debouncing.
  - Clock enabling via RCC peripheral bus registers.

### [Day 5: STM32 Timers & Output Signals](Day_05_STM32_Timers/)
- **Projects:**
  - `2_PWM_output signal`:
    - Configuring general-purpose hardware timers (TIM) in PWM generation mode.
    - Calculating timer prescaler (PSC) and auto-reload register (ARR) values to produce desired PWM frequency and duty cycles.
  - `3_ Timer with Interrupt`:
    - Configuring timer update interrupts (`TIMx_IRQHandler`).
    - Using HAL callback functions (`HAL_TIM_PeriodElapsedCallback`) for non-blocking periodic task execution.

### [Day 6: Debugging & Variable Inspection](Day_06_STM32_Debugging/4_Debugging_And_Inspect_Variables/)
- **Project:** `4_Debugging_And_Inspect_Variables`
- **Concepts Learned:**
  - Launching GDB debug sessions using the on-board ST-LINK.
  - Setting breakpoints and watchpoints.
  - Inspecting variables in real-time using STM32CubeIDE Live Watch and Expressions window.
  - Stepping through instructions (Step Over, Step Into, Step Return) and analyzing peripheral registers via the SFR (Special Function Register) view.

### Day 7: GitHub & Documentation
- Organized weekly code structure into clean modular projects.
- Configured `.gitignore` for STM32CubeIDE to omit binary artifacts (`Debug/`, `.elf`, `.hex`) while keeping complete source and project files intact.
- Published source code and detailed documentation.

---

## 📂 Repository Structure

```
├── Day_01_Bit_Manipulation/
│   └── bit_manipulation.c
├── Day_02_Pointers_and_Memory/
│   └── pointers_and_memory.c
├── Day_03_Circular_Buffer/
│   └── circular_buffer.c
├── Day_04_STM32_GPIO/
│   └── 1_Blinky/              # STM32CubeIDE Nucleo-F446RE GPIO project
├── Day_05_STM32_Timers/
│   ├── 2_PWM_output_signal/    # STM32CubeIDE PWM project
│   └── 3_Timer_with_Interrupt/ # STM32CubeIDE Timer interrupt project
├── Day_06_STM32_Debugging/
│   └── 4_Debugging_And_Inspect_Variables/ # STM32CubeIDE debug & live watch project
├── .gitignore
└── README.md
```

---

## 🚀 How to Run the Projects

### Running C Fundamentals (Days 1–3)
Compile and run with any standard GCC compiler:
```bash
gcc -Wall -Wextra Day_01_Bit_Manipulation/bit_manipulation.c -o bit_manipulation
./bit_manipulation
```

### Importing STM32 Projects into STM32CubeIDE (Days 4–6)
1. Open **STM32CubeIDE**.
2. Select **File > Open Projects from File System...**
3. Browse to the specific directory (e.g., `Day_04_STM32_GPIO/1_Blinky`) and click **Finish**.
4. Build the project: Click **Project > Build All** (`Ctrl+B`).
5. Connect your STM32 Nucleo-F446RE via USB.
6. Click **Run** or **Debug** (`F11`) to flash the firmware onto the microcontroller.

---

## 👤 Author
- **Name:** Omidu Sanvida
- **GitHub:** [@JayasekaraJMOS](https://github.com/JayasekaraJMOS)
