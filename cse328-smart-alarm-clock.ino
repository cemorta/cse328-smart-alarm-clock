#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "OLEDDisplay.h"
#include "ButtonHandler.h"
#include "RTCTime.h"
#include "BuzzerHandler.h"
#include "MenuHandler.h"
#include "AlarmHandler.h"

void setup() {
  Serial.begin(115200);
  setupOledDisplay();
  setupButtons();
  setupRTC();
  setupBuzzer();
  setupMenu(); // Initialize the menu
}

void loop() {
  // Variables to store button states
  bool leftButtonState, setButtonState, rightButtonState;
  
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
