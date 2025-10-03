#include "app_wifi.h"

#include <Arduino.h>
#include "M5Atom.h"

WiFiManager wm;
extern bool is_loop;

const String password_spec_chars = "2345679abcdefghjkmnopqrstuvwxyzACDEFGHJKLMNOPQRSTUVWXYZ"; // 55文字

String configure_ssid = "";
String configure_password = "";

void generateConfigureSSID()
{
    String mac_addr = String(WiFi.macAddress());
    mac_addr.replace(":", "");

    configure_ssid = "DigitalClock"
                     "_" +
                     mac_addr;
}

void initAppWiFi()
{
    generateConfigureSSID();
    generateConfigurePassword();
}

void generateConfigurePassword()
{
    String mac_addr = String(WiFi.macAddress());
    mac_addr.replace(":", "");
    char bytes_mac_addr[13] = {};
    mac_addr.toCharArray(bytes_mac_addr, 13);

    uint64_t seed = 0;
    for (int i = 0; i < 8; i++)
    {
        char c = bytes_mac_addr[12 - i];
        seed = seed << 8 | (uint64_t)c & 0xFF;
    }

    seed ^= 0x543D3449AC073FA0LL; // デタラメな数列をXOR

    // 乱数生成器初期化
    randomSeed(seed);

    configure_password = "";

    for (int i = 0; i < 10; i++)
    {
        int s = random(55);
        configure_password = configure_password + password_spec_chars.substring(s, s + 1);
    }
}

void getSSID(char *ssidBuffer, size_t bufferSize)
{
    String ssid = WiFi.SSID();

    strncpy(ssidBuffer, ssid.c_str(), bufferSize - 1);
    ssidBuffer[bufferSize - 1] = '\0';
}

int WiFiConnect()
{
    if (WiFi.isConnected())
    {
        Serial.println("already connected");
        return 0;
    }

    // 設定済みWi-Fiへ接続
    wm.setEnableConfigPortal(false);

    for (int i = 0; i < 3; i++)
    {
        if (wm.autoConnect())
        {
            Serial.println("successful new connection");
            return 0;
        }

        delay(5000);
        Serial.println("retry to connect");
    }

    // 新規接続
    wm.setEnableConfigPortal(true);

    if (wm.autoConnect(configure_ssid.c_str(), configure_password.c_str()))
    {
        if (WiFi.psk().compareTo("") == 0)
        {
            // オープンネットワークへの接続は禁止
            Serial.println("connecting to an open network is prohibited");
            wm.resetSettings();
            ESP.restart();
        }
        Serial.println("successful new connection");
        return 0;
    }

    Serial.println("failed to connect");

    return -1;
}

// void wifi_state()
// {
//     static bool wifi_status_lump_state = 0;

//     if (WiFi.status() == WL_CONNECTED)
//     {
//         // Wi-Fi接続中
//         M5.dis.drawpix(PIX_POS_WIFI_STATE, PIX_COL_WIFI_CONNECTED);
//     }
//     else
//     {
//         // Wi-Fi未接続
//         if (wifi_status_lump_state == 1)
//         {
//             M5.dis.drawpix(PIX_POS_WIFI_STATE, PIX_COL_WIFI_DISCONNECTED);
//         }
//         else
//         {
//             M5.dis.drawpix(PIX_POS_WIFI_STATE, PIX_COL_BLACK);
//         }
//     }

//     if (!is_loop)
//     {
//         // loopが実行されていない場合、Updateを代理
//         M5.update();
//     }

//     wifi_status_lump_state = !wifi_status_lump_state;
// }
