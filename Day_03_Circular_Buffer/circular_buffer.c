/**
 * ============================================================================
 * Day 3: Circular Buffer (Ring Buffer) Implementation
 * Author: Omidu Sanvida (JayasekaraJMOS)
 * Target: Embedded Systems FIFO Data Structure for UART/Sensor Streams
 * ============================================================================
 */

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

#define BUFFER_CAPACITY 8

typedef struct {
    uint8_t buffer[BUFFER_CAPACITY];
    size_t head; // write index
    size_t tail; // read index
    size_t count;
} CircularBuffer;

void cb_init(CircularBuffer *cb) {
    cb->head = 0;
    cb->tail = 0;
    cb->count = 0;
}

bool cb_is_full(const CircularBuffer *cb) {
    return cb->count == BUFFER_CAPACITY;
}

bool cb_is_empty(const CircularBuffer *cb) {
    return cb->count == 0;
}

bool cb_write(CircularBuffer *cb, uint8_t data) {
    if (cb_is_full(cb)) {
        return false; // buffer full
    }
    cb->buffer[cb->head] = data;
    cb->head = (cb->head + 1) % BUFFER_CAPACITY;
    cb->count++;
    return true;
}

bool cb_read(CircularBuffer *cb, uint8_t *data) {
    if (cb_is_empty(cb)) {
        return false; // buffer empty
    }
    *data = cb->buffer[cb->tail];
    cb->tail = (cb->tail + 1) % BUFFER_CAPACITY;
    cb->count--;
    return true;
}

int main(void) {
    CircularBuffer rx_buffer;
    cb_init(&rx_buffer);

    printf("=== Day 3: Circular (Ring) Buffer Implementation ===\n\n");

    printf("Pushing 6 bytes (A, B, C, D, E, F) into circular buffer...\n");
    for (char c = 'A'; c <= 'F'; c++) {
        cb_write(&rx_buffer, (uint8_t)c);
    }
    printf("Current buffer count: %zu / %d\n", rx_buffer.count, BUFFER_CAPACITY);

    printf("\nReading 3 bytes:\n");
    uint8_t val;
    for (int i = 0; i < 3; i++) {
        if (cb_read(&rx_buffer, &val)) {
            printf("Read: '%c' (0x%02X)\n", (char)val, val);
        }
    }
    printf("Remaining count: %zu\n", rx_buffer.count);

    printf("\nWriting 4 more bytes (G, H, I, J) to wrap around indices...\n");
    for (char c = 'G'; c <= 'J'; c++) {
        if (cb_write(&rx_buffer, (uint8_t)c)) {
            printf("Wrote '%c' successfully\n", c);
        } else {
            printf("Failed to write '%c' - Buffer Full!\n", c);
        }
    }

    printf("\nDraining buffer:\n");
    while (cb_read(&rx_buffer, &val)) {
        printf("Read: '%c'\n", (char)val);
    }
    printf("Buffer is now empty: %s\n", cb_is_empty(&rx_buffer) ? "true" : "false");

    return 0;
}
