#include <Arduino.h>
#include <WiFi.h>
#include <SPIFFS.h>
#include <ESPAsyncWebServer.h>
#include <ESP32IR.h>

void initWiFi();
void initIRJoystick();
void mountROMsFileRoute();
void mountNotFoundRoute();
void readJoystickIRReceive();
void mountPageIndexEmulator();
