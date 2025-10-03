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
    M5.begin(true, false, true);
    pinMode(BTN_SET, INPUT);
}

void press_ms(int gpio, int ms)
{
    pinMode(gpio, OUTPUT);
    M5.dis.drawpix(0, 0x0000FF);
    digitalWrite(gpio, HIGH);
    delay(ms);
    pinMode(gpio, INPUT);
    M5.dis.drawpix(0, 0x000000);
}

void loop()
{
    press_ms(BTN_SET, 100);
    delay(1000);
}
