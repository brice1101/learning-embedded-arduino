#include <avr/io.h>
#include <stdint.h>

// Inputs on port: D9 = PH6, D8 = PH5
#define ON_BTN  PH6
#define OFF_BTN PH5
#define BTN_MASK ((1 << ON_BTN) | (1 << OFF_BTN))

// Output on port A: D5 = PE3
#define LED     PE3

static inline uint8_t is_pressed(uint8_t pins, uint8_t bit) {
    return !(pins & (1 << bit));
}

int main() {
    // Buttons: inputs (DDR bit = 0) with pull-ups on
    DDRH &= ~BTN_MASK;
    PORTH |= BTN_MASK;

    // LED; output, starting off
    DDRE |= (1 << LED);
    PORTE &= ~(1 << LED);

    while (1) {
        uint8_t pins = PINH; // read both buttons

        // Active-low: a pressed button reads 0
        if (is_pressed(pins, ON_BTN)) PORTE |= (1 << LED);
        if (is_pressed(pins, OFF_BTN)) PORTE &= ~(1 << LED);
    }
}