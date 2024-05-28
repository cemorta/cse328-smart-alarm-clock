#ifndef ALARMHANDLER_H
#define ALARMHANDLER_H

#include <Wire.h>
#include <RTClib.h>

// Alarm time variables
int alarmHour = 0;
int alarmMinute = 0;
bool alarmSet = false;

void sendTime() {
  char buf[20];
  sprintf(buf, "%02d:%02d:00", alarmHour, alarmMinute);
  Serial.println(buf);
}

void setAlarmTime(int hour, int minute) {
  alarmHour = hour;
  alarmMinute = minute;
  alarmSet = true;
  Serial.print("ALARMSET: ");
  sendTime();
}

void checkAlarm(Adafruit_SSD1306 &display, RTC_DS3231 &rtc) {
  if (!alarmSet) return;

  DateTime now = rtc.now();
  if (now.hour() == alarmHour && now.minute() == alarmMinute) {
    Serial.print("BUZZALARM");
    display.clearDisplay();
    display.setCursor(0, 0);
    display.println("Alarm Triggered!");
    display.display();
    delay(2000); // Display message for 2 seconds
    alarmSet = false; // Optionally reset alarm, or manage this elsewhere
  }
}

#endif // ALARMHANDLER_H
