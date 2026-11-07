/**
 * ============================================================================
 * Day 1: Bit Manipulation Exercises
 * Author: Omidu Sanvida (JayasekaraJMOS)
 * Target: Embedded C Fundamentals (Registers & Bitwise Operations)
 * ============================================================================
 */

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

// Helper macro definitions for bit manipulation
#define SET_BIT(REG, BIT)     ((REG) |= (1U << (BIT)))
#define CLEAR_BIT(REG, BIT)   ((REG) &= ~(1U << (BIT)))
#define TOGGLE_BIT(REG, BIT)  ((REG) ^= (1U << (BIT)))
#define READ_BIT(REG, BIT)    (((REG) >> (BIT)) & 1U)

void print_binary(uint8_t byte) {
    for (int i = 7; i >= 0; i--) {
        printf("%d", (byte >> i) & 1);
    }
    printf("\n");
}

int main(void) {
    uint8_t reg = 0x00; // Simulating an 8-bit hardware control register
    printf("=== Day 1: Bit Manipulation in Embedded C ===\n\n");

    printf("Initial register value: 0x%02X | Binary: ", reg);
    print_binary(reg);

    // 1. Setting Bit 3 and Bit 5
    printf("\n[1] Setting Bit 3 and Bit 5...\n");
    SET_BIT(reg, 3);
    SET_BIT(reg, 5);
    printf("Result: 0x%02X | Binary: ", reg);
    print_binary(reg);

    // 2. Reading Bits
    printf("\n[2] Reading bit states:\n");
    printf("Bit 3 is: %u\n", READ_BIT(reg, 3));
    printf("Bit 4 is: %u\n", READ_BIT(reg, 4));
    printf("Bit 5 is: %u\n", READ_BIT(reg, 5));

    // 3. Toggling Bit 5 (turn off) and Bit 0 (turn on)
    printf("\n[3] Toggling Bit 5 and Bit 0...\n");
    TOGGLE_BIT(reg, 5);
    TOGGLE_BIT(reg, 0);
    printf("Result: 0x%02X | Binary: ", reg);
    print_binary(reg);

    // 4. Clearing Bit 3
    printf("\n[4] Clearing Bit 3...\n");
    CLEAR_BIT(reg, 3);
    printf("Result: 0x%02X | Binary: ", reg);
    print_binary(reg);

    // 5. Bit Masking - checking multiple bits
    printf("\n[5] Bit Masking (Checking bits 0 to 3):\n");
    uint8_t lower_nibble = reg & 0x0F;
    printf("Lower nibble: 0x%02X\n", lower_nibble);

    return 0;
}
