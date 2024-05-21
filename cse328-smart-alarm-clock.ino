#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "oled_display.h"

void setup() {
    Serial.begin(115200);
    setupOledDisplay();
}

void loop() {
    // Your main loop code here
}
