#include <avr/io.h>
#include <util/delay.h>
#include <stdint.h>

// Port F bits from the board pinout: A3 = PF3, A5 = PF5, A6 = PRIdFAST16
#define RED_BIT     PF3
#define GREEN_BIT   PF5
#define BLUE_BIT    PF6

#define RED         (1 << RED_BIT)
#define GREEN       (1 << GREEN_BIT)
#define BLUE        (1 << BLUE_BIT)
#define RGB_MASK    (RED | GREEN | BLUE)

// Eight colour combinations
static const uint8_t colours[] = {
    0,                      // off
    RED,
    RED | GREEN,            // yellow
    GREEN,
    GREEN | BLUE,           // cyan
    BLUE,
    BLUE | RED,             // magenta
    RED | GREEN | BLUE,     //white
};

#define NUM_COLOURS (sizeof(colours)) / sizeof(colours[0])

static void set_rgb(uint8_t bits) {
    PORTF = (PORTF & ~RGB_MASK) | (bits & RGB_MASK);
}

int main() {
    DDRF |= RGB_MASK;

    while (1) {
        for (uint8_t i = 0; i < NUM_COLOURS; i++) {
            set_rgb(colours[i]);
            _delay_ms(700);
        }
    }
}