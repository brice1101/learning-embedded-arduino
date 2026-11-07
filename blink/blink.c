#include <stdint.h>
#include <util/delay.h>

// Addresses from the ATmega2560 datasheet, Register Summary (data space)
#define DDRB_REG (*(volatile uint8_t *)0x24)
#define PORTB_REG (*(volatile uint8_t *)0x25)

#define LED_BIT 7  // Built-in LED "L" is on PB7 (from the Mega schematic)

int main() {
    // Make PB7 an output; leave other pins as they are
    DDRB_REG |= (1 << LED_BIT);

    while (1) {
        PORTB_REG ^= (1 << LED_BIT); // flip the LED
        _delay_ms(500);
    }
}