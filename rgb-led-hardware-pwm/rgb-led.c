#include <avr/io.h>
#include <util/delay.h>
#include <stdint.h>

// Timer 3 outputs on port E: D5 = PE3 = OC3A, D3 = PE5 = OC3C, D2 = PE4 = OC3B
#define RED_PIN     PE5
#define GREEN_PIN   PE3
#define BLUE_PIN    PE4

static void pwm_init() {
    // Timer drives pins, but must still be outputs
    DDRE |= (1 << RED_PIN) | (1 << GREEN_PIN) | (1 << BLUE_PIN);

    // Non-inverting PWN on channels A, B, and C; WGM30 is half of mode 5
    TCCR3A = (1 << COM3A1) | (1 << COM3B1) | (1 << COM3C1) | (1 << WGM30);

    // WGM32 is other half of mode 5
    TCCR3B = (1 << WGM32) | (1 << CS31) | (1 << CS30);
}

static void set_rgb(uint8_t r, uint8_t g, uint8_t b) {
    OCR3C = r;
    OCR3A = g;
    OCR3B = b;
}

static void hue_to_rgb(uint16_t hue, uint8_t *r, uint8_t *g, uint8_t *b) {
    uint8_t segment = hue / 256;
    uint8_t x = hue % 256;

    switch (segment) {
        case 0: *r = 255; *g = x; *b = 0; break;
        case 1: *r = 255 - x; *g = 255; *b = 0; break;
        case 2: *r = 0; *g = 255; *b = x; break;
        case 3: *r = 0; *g = 255 - x; *b = 255; break;
        case 4: *r = x; *g = 0; *b = 255; break;
        default: *r = 255; *g = 0; *b = 255 - x; break;
    }
}

int main() {
    pwm_init();
    uint8_t r, g, b;

    while (1) {
        for (uint16_t hue = 0; hue < 1536; hue++) {
            hue_to_rgb(hue, &r, &g, &b);
            set_rgb(r, g, b);
            _delay_ms(4);
        }
    }
}