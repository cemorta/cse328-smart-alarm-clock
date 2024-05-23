#ifndef ALARMHANDLER_H
#define ALARMHANDLER_H

#include <Wire.h>
#include <RTClib.h>
#include "BuzzerHandler.h"  // Ensure this include if you use beepBuzzer in this file

// Alarm time variables
int alarmHour = 0;
int alarmMinute = 0;
bool alarmSet = false;

void setAlarmTime(int hour, int minute) {
  alarmHour = hour;
  alarmMinute = minute;
  alarmSet = true;
}

void checkAlarm(Adafruit_SSD1306 &display, RTC_DS3231 &rtc) {
  if (!alarmSet) return;

  DateTime now = rtc.now();
  if (now.hour() == alarmHour && now.minute() == alarmMinute) {
    beepBuzzer(1000, 1000); // Assuming beepBuzzer handles tone and noTone internally
    display.clearDisplay();
    display.setCursor(0, 0);
    display.println("Alarm Triggered!");
    display.display();
    delay(2000); // Display message for 2 seconds
    alarmSet = false; // Optionally reset alarm, or manage this elsewhere
  }
}

#endif // ALARMHANDLER_H
