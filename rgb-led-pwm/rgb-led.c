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

static void soft_pwm_period(uint8_t r, uint8_t g, uint8_t b) {
    for (uint8_t t = 0; t < 255; t++) {
        uint8_t bits = 0;
        if (t < r) bits |= RED;
        if (t < g) bits |= GREEN;
        if (t < b) bits |= BLUE;
        set_rgb(bits);
        _delay_us(20);
    }
}

// Show one colour for given time
static void show(uint8_t r, uint8_t g, uint8_t b, uint16_t periods) {
    for (uint16_t i = 0; i < periods; i++) {
        soft_pwm_period(r, g, b);
    }
}

int main(void) {
    DDRF |= RGB_MASK;

    while (1) {
        show(255, 40, 0, 200);  // Orange
        show(120, 0, 255, 200);  // Purple
        show(0, 255, 60, 200);  // Spring green

        // Fade red up and down
        for (uint8_t v = 0; v < 255; v++) show(v, 0, 0, 2);
        for (uint8_t v = 255; v > 0; v--) show(v, 0, 0, 2);
    }
}