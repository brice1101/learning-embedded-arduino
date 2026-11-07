#include <stdint.h>
#include <util/delay.h>

// Addresses from the ATmega2560 datasheet, Register Summary (data space)
#define PINB_REG (*(volatile uint8_t *)0x23)
#define DDRB_REG (*(volatile uint8_t *)0x24)
#define PORTB_REG (*(volatile uint8_t *)0x25)

#define LED_BIT 7  // Built-in LED "L" is on PB7 (from the Mega schematic)

void dot() {
    PORTB_REG |= (1 << LED_BIT);
    _delay_ms(120);
    PORTB_REG &= ~(1 << LED_BIT);
    _delay_ms(120);
}

void dash() {
    PORTB_REG |= (1 << LED_BIT);
    _delay_ms(360);
    PORTB_REG &= ~(1 << LED_BIT);
    _delay_ms(120);
}

int main() {
    // Make PB7 an output; leave other pins as they are
    DDRB_REG |= (1 << LED_BIT);

    while (1) {
        for (int i = 0; i < 3; i++) {
            dot(); // S
        }
        _delay_ms(240);  // 1 second after blink, add an extra 2 between letters
        for (int i = 0; i < 3; i++) {
            dash(); // O
        }
        _delay_ms(240);
        for (int i = 0; i < 3; i++) {
            dot();  // S
        }
        _delay_ms(720);  // 1 second after blink, add an extra 6 between words
    }
}