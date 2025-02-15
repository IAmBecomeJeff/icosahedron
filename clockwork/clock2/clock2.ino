//#include <ESP8266WiFi.h>
#include <WiFi.h>
#include <ESPmDNS.h>
#include <WiFiUdp.h>
#include <ArduinoOTA.h>
#include <time.h>
#include "FastLED.h"
#include "Arduino.h"

#define DATA_PIN    2
#define LED_TYPE    WS2811
#define COLOR_ORDER RGB
#define NUM_LEDS    96
#define BRIGHTNESS  255
CRGB leds[NUM_LEDS];

//Digits color values in RGB
int r = 255;
int g = 255;
int b = 255;

// Pattern modes
uint8_t current_mode = 0;

//const char* ESP_HOST_NAME = "esp-" + ESP.getFlashChipId();
//Your Wifi info
const char* ssid = "UniversalMindLattice";
const char* password = "correcthorsebatterystaple";

//Your time zone
int timezone = -6 * 3600;
int dst = 1;

#include "time_locations.h"
#include "pride.h"
#include "ota.h"
#include "switch_mode.h"



void setup() {
  Serial.begin(115200);
  delay(500);
  connectWiFi();
  Serial.println();
  Serial.println("\n\nNext Loop-Step: " + String(millis()) + ":");
  configTime(timezone, dst, "pool.ntp.org","time.nist.gov");
  FastLED.addLeds<LED_TYPE,DATA_PIN,COLOR_ORDER>(leds, NUM_LEDS)
    .setCorrection(TypicalLEDStrip)
    .setDither(BRIGHTNESS < 255);
  FastLED.setBrightness(BRIGHTNESS);
}


void loop()
{
    ArduinoOTA.handle();
    // Find and print time
    time_t now = time(nullptr);
    struct tm* p_tm = localtime(&now);
    /*
     * Serial.print("-------------------------------------------------\n");
    Serial.print("Date & Time : ");
    Serial.print(p_tm->tm_mday);
    Serial.print("/");
    Serial.print(p_tm->tm_mon + 1);
    Serial.print("/");
    Serial.print(p_tm->tm_year + 1900);
    Serial.print(" ");
    */
    int hour=p_tm->tm_hour;
    int minute=p_tm->tm_min;
    if(hour>12)
    {
      hour=hour-12;
    }
    Serial.print(hour);
    Serial.print(":");
    Serial.print(minute);
    Serial.print(":");
    Serial.println(p_tm->tm_sec);

    // Background animations
    run_mode(current_mode);

    EVERY_N_MINUTES(1) {
        current_mode = (current_mode + 1) % num_modes;
    }
    // Add Clock
    switch_time(hour, minute);
    FastLED.show();
}
