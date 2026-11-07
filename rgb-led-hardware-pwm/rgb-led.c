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

int main() {
    pwm_init();
    DDRB |= (1 << PB7);

    while (1) {
        for (uint8_t v = 0; v < 255; v++) {
            set_rgb(255, v, 0);
            _delay_ms(8);
        }
        for (uint8_t v = 255; v > 0; v--) {
            set_rgb(v, 255, 0);
            _delay_ms(8);
        }
        for (uint8_t v = 0; v < 255; v++) {
            set_rgb(0, 255, v);
        }
        for (uint8_t v = 255; v > 0; v--) {
            set_rgb(0, v, 255);
            _delay_ms(8);
        }
        for (uint8_t v = 0; v < 255; v++) {
            set_rgb(v, 0, 255);
            _delay_ms(8);
        }
        for (uint8_t v = 255; v > 0; v--) {
            set_rgb(255, 0, v);
            _delay_ms(8);
        }
    }
}