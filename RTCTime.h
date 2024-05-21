#ifndef RTCTIME_H
#define RTCTIME_H

#include <Wire.h>
#include <RTClib.h>

// Create an instance of the RTC
RTC_DS3231 rtc;

void setupRTC() {
  // Initialize the RTC
  if (!rtc.begin()) {
    Serial.println("Couldn't find RTC");
    while (1);
  }
  if (rtc.lostPower()) {
    Serial.println("RTC lost power, let's set the time!");
    // The following line sets the RTC to the date & time this sketch was compiled
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
    // Uncomment to set the date & time manually
    // rtc.adjust(DateTime(2023, 1, 1, 0, 0, 0));
  }
}

void displayTime(Adafruit_SSD1306 &display) {
  DateTime now = rtc.now();

  display.clearDisplay();
  display.setCursor(0, 10);
  display.print(now.year(), DEC);
  display.print('/');
  display.print(now.month(), DEC);
  display.print('/');
  display.print(now.day(), DEC);
  display.print(" ");
  display.print(now.hour(), DEC);
  display.print(':');
  display.print(now.minute(), DEC);
  display.print(':');
  display.print(now.second(), DEC);
  display.display();
}

#endif // RTCTIME_H
 
