#pragma once

#include <string>
#include <stddef.h>
#include <string.h>
#include <WiFi.h>
#include <WiFiManager.h>

void getSSID(char *ssidBuffer, size_t bufferSize);
void initAppWiFi();
void generateConfigureSSID();
void generateConfigurePassword();
int WiFiConnect();
// void wifi_state();
