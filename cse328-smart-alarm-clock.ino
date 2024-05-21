#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "OLEDDisplay.h"
#include "ButtonHandler.h"
#include "RTCTime.h"

void setup() {
  Serial.begin(115200);
  setupOledDisplay();
  setupButtons();
  setupRTC();
}

void loop() {
  // Variables to store button states
  bool leftButtonState, setButtonState, rightButtonState;
  
  // Read the state of the buttons
  readButtons(leftButtonState, setButtonState, rightButtonState);
  
  // Display different text based on button state
  if (leftButtonState) { // Left button pressed
    display.clearDisplay();
    display.setCursor(0, 10);
    display.println("Left Button Pressed");
    display.display();
  } else if (setButtonState) { // Set button pressed
    display.clearDisplay();
    display.setCursor(0, 10);
    display.println("Set Button Pressed");
    display.display();
  } else if (rightButtonState) { // Right button pressed
    display.clearDisplay();
    display.setCursor(0, 10);
    display.println("Right Button Pressed");
    display.display();
  } else {
    displayTime(display); // Display current time if no button is pressed
  }

  // Print the state of each button to the serial monitor
  Serial.print("Left Button: ");
  Serial.print(leftButtonState ? "Pressed" : "Not Pressed");
  Serial.print("\tSet Button: ");
  Serial.print(setButtonState ? "Pressed" : "Not Pressed");
  Serial.print("\tRight Button: ");
  Serial.println(rightButtonState ? "Pressed" : "Not Pressed");
  
  // Add a small delay to avoid spamming the serial monitor
  delay(100);
}
