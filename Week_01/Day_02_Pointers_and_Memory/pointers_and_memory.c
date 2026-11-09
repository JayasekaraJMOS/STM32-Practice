/**
 * ============================================================================
 * Day 2: Pointers and Memory
 * Author: Omidu Sanvida (JayasekaraJMOS)
 * Target: Embedded C Memory Architecture, Pointer Arithmetic, and Arrays
 * ============================================================================
 */

#include <stdio.h>
#include <stdint.h>

void array_reverse_pointer(uint32_t *arr, size_t size) {
    uint32_t *start = arr;
    uint32_t *end = arr + size - 1;
    while (start < end) {
        uint32_t temp = *start;
        *start = *end;
        *end = temp;
        start++;
        end--;
    }
}

// Simulating peripheral memory-mapped I/O structure
typedef struct {
    volatile uint32_t MODER;   // Offset 0x00
    volatile uint32_t OTYPER;  // Offset 0x04
    volatile uint32_t OSPEEDR; // Offset 0x08
    volatile uint32_t PUPDR;   // Offset 0x0C
    volatile uint32_t IDR;     // Offset 0x10
    volatile uint32_t ODR;     // Offset 0x14
} Mock_GPIO_TypeDef;

int main(void) {
    printf("=== Day 2: Pointers, Memory & Peripheral Mapping in C ===\n\n");

    // 1. Pointer Arithmetic with Arrays
    uint32_t data[5] = {10, 20, 30, 40, 50};
    printf("[1] Original Array: ");
    for (size_t i = 0; i < 5; i++) {
        printf("%u ", *(data + i)); // pointer offset dereferencing
    }
    printf("\n");

    array_reverse_pointer(data, 5);
    printf("Reversed Array via Pointers: ");
    for (size_t i = 0; i < 5; i++) {
        printf("%u ", data[i]);
    }
    printf("\n\n");

    // 2. Struct Pointer and Register Mapping Simulation
    printf("[2] Struct-based Memory-Mapped Register Access:\n");
    Mock_GPIO_TypeDef mock_gpioa = {0};
    Mock_GPIO_TypeDef *const GPIOA = &mock_gpioa;

    // Configure Pin 5 as output (set MODER bit 10)
    GPIOA->MODER |= (1U << 10);
    // Set Output Pin 5 HIGH in ODR
    GPIOA->ODR |= (1U << 5);

    printf("GPIOA MODER: 0x%08X (MODER5 configured)\n", GPIOA->MODER);
    printf("GPIOA ODR:   0x%08X (Pin 5 is HIGH)\n", GPIOA->ODR);

    return 0;
}
