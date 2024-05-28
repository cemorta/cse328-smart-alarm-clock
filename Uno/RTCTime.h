#ifndef RTCTIME_H
#define RTCTIME_H

#include <Wire.h>
#include <RTClib.h>

// Create an instance of the RTC
RTC_DS3231 rtc;

void setupRTC() {
  Wire.begin();
  Wire.setClock(400000); // Set I2C frequency to 400kHz for faster communication
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

  // Prepare time string
  char timeStr[9]; // hh:mm:ss
  snprintf(timeStr, sizeof(timeStr), "%02d:%02d:%02d", now.hour(), now.minute(), now.second());

  // Prepare date string
  char dateStr[11]; // dd/mm/yyyy
  snprintf(dateStr, sizeof(dateStr), "%02d/%02d/%04d", now.day(), now.month(), now.year());

  // Set text size for time
  display.setTextSize(2);
  display.setTextColor(SSD1306_WHITE);

  // Calculate position to center the time string
  int16_t x1, y1;
  uint16_t w, h;
  display.getTextBounds(timeStr, 0, 0, &x1, &y1, &w, &h);
  int16_t xTime = (display.width() - w) / 2;
  int16_t yTime = (display.height() / 2) - h; // Adjust y-coordinate to add padding

  // Display the time string
  display.setCursor(xTime, yTime);
  display.println(timeStr);

  // Set text size for date
  display.setTextSize(1);

  // Calculate position to center the date string
  display.getTextBounds(dateStr, 0, 0, &x1, &y1, &w, &h);
  int16_t xDate = (display.width() - w) / 2;
  int16_t yDate = yTime + h + 16; // Adjust y-coordinate to add padding

  // Display the date string
  display.setCursor(xDate, yDate);
  display.println(dateStr);

  // Display the changes
  display.display();
}

#endif // RTCTIME_H
