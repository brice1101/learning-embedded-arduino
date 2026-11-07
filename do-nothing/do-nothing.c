#include <avr/sleep.h>
#include <avr/interrupt.h>

int main() {
    cli();
    set_sleep_mode(SLEEP_MODE_PWR_DOWN);
    sleep_mode();
    while (1) { }
}
