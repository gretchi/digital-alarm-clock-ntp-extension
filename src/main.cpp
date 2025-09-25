#include <Arduino.h>
#include "M5Atom.h"

// const int BTN_1;
// const int BTN_2;
// const int BTN_A;
// const int BTN_B;
// const int BTN_C;

const int BTN_SET = 22;

void setup()
{
    pinMode(BTN_SET, INPUT);
}

void press_ms(int gpio, int ms)
{
    pinMode(gpio, OUTPUT);
    digitalWrite(gpio, HIGH);
    delay(ms);
    pinMode(gpio, INPUT);
}

void loop()
{
    press_ms(BTN_SET, 100);
    delay(1000);
}
