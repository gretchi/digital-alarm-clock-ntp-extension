#include <Arduino.h>
#include <M5Atom.h>
#include <WiFiManager.h>
#include <WiFi.h>
#include "app_wifi.h"

const int BTN_1_SET = 33;
const int BTN_2_00 = 23;
const int BTN_A_HOUR = 19;
const int BTN_B_MINUTE = 22;
const int PRESS_MS = 100;

extern WiFiManager wm;
extern String configure_ssid;
extern String configure_password;

void press_ms(int gpio, int ms);

void setup()
{
    M5.begin(true, false, true);
    Serial.begin(115200);
    M5.dis.drawpix(0, 0xFF0000);

    pinMode(BTN_1_SET, INPUT);
    pinMode(BTN_2_00, INPUT);
    pinMode(BTN_A_HOUR, INPUT);
    pinMode(BTN_B_MINUTE, INPUT);

    initAppWiFi();
    Serial.printf("Configure Wi-Fi SSID: %s, Password: %s\n", configure_ssid.c_str(), configure_password.c_str());
    if (WiFiConnect() == 0)
    {
        Serial.println("Wi-Fi not connecting");
    }
    M5.dis.drawpix(0, 0x008000);

    press_ms(BTN_1_SET, PRESS_MS);
    delay(5000);

    press_ms(BTN_1_SET, PRESS_MS);
    for (int i = 0; i < 3; i++)
    {
        press_ms(BTN_A_HOUR, PRESS_MS);
        delay(300);
    }
    for (int i = 0; i < 15; i++)
    {
        press_ms(BTN_B_MINUTE, PRESS_MS);
        delay(300);
    }
}

void press_ms(int gpio, int ms)
{
    pinMode(gpio, OUTPUT);
    M5.dis.drawpix(0, 0x0080FF);
    digitalWrite(gpio, HIGH);
    delay(ms);
    pinMode(gpio, INPUT);
    M5.dis.drawpix(0, 0x008000);
    delay(ms);
}

void loop()
{
    M5.update();
    delay(100);
}
