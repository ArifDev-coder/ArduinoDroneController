#include <Arduino.h>
#include <WiFi.h>
#include <WiFiUdp.h>

const char* ssid = "Z_DRONE";
const char* pass = "Z12345678";

void setup()
{
    WiFi.mode(WIFI_AP);
    WiFi.softAP(ssid, pass);
}

void loop()
{
    Serial.println("Testing...");
    delay(1000);
}