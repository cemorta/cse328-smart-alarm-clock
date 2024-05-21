#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "OLEDDisplay.h"
#include "ButtonHandler.h"

void setup() {
    Serial.begin(115200);
    setupOledDisplay();
    setupButtons();
}

void loop() {
  // Variables to store button states
  bool leftButtonState, setButtonState, rightButtonState;
  
  // Read the state of the buttons
  readButtons(leftButtonState, setButtonState, rightButtonState);
  
  // Clear the display before updating text
  display.clearDisplay();
  display.setCursor(0, 10);

  // Display different text based on button state
  if (leftButtonState) { // Left button pressed
    display.println("Left Button Pressed");
  } else if (setButtonState) { // Set button pressed
    display.println("Set Button Pressed");
  } else if (rightButtonState) { // Right button pressed
    display.println("Right Button Pressed");
  } else {
    display.println("No Button Pressed");
  }
  
  // Display the changes
  display.display();

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
