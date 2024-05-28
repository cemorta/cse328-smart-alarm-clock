#ifndef BUZZERHANDLER_H
#define BUZZERHANDLER_H

#include <Arduino.h>

// Define buzzer pin
#define BUZZER_PIN 5

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

// Function for approval sound
void approvalSound() {
  beepBuzzer(1000, 200); // High-pitched short beep
}

// Function for cancellation sound
void cancellationSound() {
  beepBuzzer(500, 200); // Low-pitched short beep
  delay(100);
  beepBuzzer(500, 200); // Low-pitched short beep
}

// Function for continue sound
void continueSound() {
  beepBuzzer(750, 100); // Medium-pitched short beep
  delay(50);
  beepBuzzer(750, 100); // Medium-pitched short beep
  delay(50);
  beepBuzzer(750, 100); // Medium-pitched short beep
}

#endif // BUZZERHANDLER_H
