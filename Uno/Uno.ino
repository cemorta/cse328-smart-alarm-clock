#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "OLEDDisplay.h"
#include "ButtonHandler.h"
#include "RTCTime.h"
#include "BuzzerHandler.h"
#include "MenuHandler.h"
#include "AlarmHandler.h"

// Variables to store button states
bool leftButtonState, setButtonState, rightButtonState;

void setup() {
  Serial.begin(57600);
  setupOledDisplay();
  setupButtons();
  setupRTC();
  setupBuzzer();
  setupMenu(); // Initialize the menu
}

void loop() {
  if (Serial.available()) {  // Check if data is available to read
    processSerialData(Serial.readString());
  }

  // Read the state of the buttons
  readButtons(leftButtonState, setButtonState, rightButtonState);
  
  // Navigate and display the menu based on button states
  navigateMenu(leftButtonState, setButtonState, rightButtonState);
  displayMenu(display);

  // Check and trigger alarm if necessary
  checkAlarm(display, rtc);

  // Add a small delay to avoid spamming the serial monitor
  delay(100);
}

void processSerialData(String data) {
  if (data.startsWith("CREATEALARM: ")) {
    // Additional actions based on the alarm
    // Extracting the time part
    String timeStr = data.substring(data.indexOf(':') + 2);  // +2 to skip the ": " after "ALARMSET"
    Serial.print(timeStr);
    setAlarmTime(timeStr.substring(0, 2).toInt(), timeStr.substring(3, 5).toInt());
  }
}