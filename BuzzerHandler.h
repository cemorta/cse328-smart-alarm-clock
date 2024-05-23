#ifndef BUZZERHANDLER_H
#define BUZZERHANDLER_H

#include <Arduino.h>

// Define buzzer pin
#define BUZZER_PIN 6

// Function to initialize the buzzer pin
void setupBuzzer() {
  pinMode(BUZZER_PIN, OUTPUT);
}

// Function to make the buzzer beep
void beepBuzzer(int frequency, int duration) {
  tone(BUZZER_PIN, frequency); // Beep at the specified frequency
  delay(duration);             // Beep for the specified duration
  noTone(BUZZER_PIN);          // Stop the beep
}

#endif // BUZZERHANDLER_H
