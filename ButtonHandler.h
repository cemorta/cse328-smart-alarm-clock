#ifndef BUTTONHANDLER_H
#define BUTTONHANDLER_H

#include <Arduino.h>

// Define button pins
#define LEFT_BUTTON 7
#define SET_BUTTON 8
#define RIGHT_BUTTON 9

// Function to initialize button pins
void setupButtons() {
    pinMode(LEFT_BUTTON, INPUT_PULLUP);
    pinMode(SET_BUTTON, INPUT_PULLUP);
    pinMode(RIGHT_BUTTON, INPUT_PULLUP);
}

// Function to read the state of the buttons
void readButtons(bool &leftButtonState, bool &setButtonState, bool &rightButtonState) {
    leftButtonState = digitalRead(LEFT_BUTTON) == HIGH;
    setButtonState = digitalRead(SET_BUTTON) == HIGH;
    rightButtonState = digitalRead(RIGHT_BUTTON) == HIGH;
}

#endif // BUTTONHANDLER_H
