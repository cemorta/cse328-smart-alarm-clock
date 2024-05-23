#ifndef MENUHANDLER_H
#define MENUHANDLER_H

#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "AlarmHandler.h"
#include "RTCTime.h"

// Define menu items
enum MenuItem {
  MENU_SHOW_TIME,
  MENU_SET_ALARM,
  MENU_SET_TIME,
  MENU_TOTAL_ITEMS
};

// Function prototypes
void setupMenu();
void navigateMenu(bool leftButtonPressed, bool setButtonPressed, bool rightButtonPressed);
void displayMenu(Adafruit_SSD1306 &display);
void setAlarmMenu(bool leftButtonPressed, bool rightButtonPressed, bool setButtonPressed);

// Current menu item
MenuItem currentMenuItem = MENU_SHOW_TIME;
int alarmSettingStage = 0; // 0: Setting hour, 1: Setting minute
bool openSetAlarmMenu = false;

void setupMenu() {
  currentMenuItem = MENU_SHOW_TIME;
}

void navigateMenu(bool leftButtonPressed, bool setButtonPressed, bool rightButtonPressed) {
  if (openSetAlarmMenu) {
    setAlarmMenu(leftButtonPressed, rightButtonPressed, setButtonPressed);
    return; // Exit to prevent menu item change while setting alarm
  }

  if (leftButtonPressed) {
    currentMenuItem = (MenuItem)((currentMenuItem + MENU_TOTAL_ITEMS - 1) % MENU_TOTAL_ITEMS);
  } else if (rightButtonPressed) {
    currentMenuItem = (MenuItem)((currentMenuItem + 1) % MENU_TOTAL_ITEMS);
  } else if (setButtonPressed) {
    // Handle select action
    switch (currentMenuItem) {
      case MENU_SHOW_TIME:
        // Do nothing, just show the time
        break;
      case MENU_SET_ALARM:
        openSetAlarmMenu = true; // Open the set alarm menu
        alarmSettingStage = 0; // Start with setting hour
        break;
      case MENU_SET_TIME:
        // Logic for setting time
        break;
      default:
        break;
    }
  }
}

void displayMenu(Adafruit_SSD1306 &display) {
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);

  switch (currentMenuItem) {
    case MENU_SHOW_TIME:
      displayTime(display); // Call displayTime function from RTCTime.h
      break;
    case MENU_SET_ALARM:
      display.setCursor(0, 0);
      display.println("2. Set Alarm");
      display.setCursor(0, 20);
      if (openSetAlarmMenu) {
        if (alarmSettingStage == 0) {
          display.println("Set Hour: " + String(alarmHour));
        } else {
          display.println("Set Minute: " + String(alarmMinute));
        }
      } else {
        display.println("Alarm:");
        display.setCursor(0, 30);
        if (alarmSet) {
          display.println("Set for " + String(alarmHour) + ":" + String(alarmMinute));
        } else {
          display.println("Not set");
        }
      }
      break;
    case MENU_SET_TIME:
      display.setCursor(0, 0);
      display.println("3. Set Time");
      break;
    default:
      break;
  }

  display.display();
}

void setAlarmMenu(bool leftButtonPressed, bool rightButtonPressed, bool setButtonPressed) {
  if (alarmSettingStage == 0) { // Setting hour
    if (leftButtonPressed) {
      alarmHour = (alarmHour + 23) % 24; // Decrement hour
    } else if (rightButtonPressed) {
      alarmHour = (alarmHour + 1) % 24; // Increment hour
    } else if (setButtonPressed) {
      alarmSettingStage = 1; // Move to setting minute
    }
  } else if (alarmSettingStage == 1) { // Setting minute
    if (leftButtonPressed) {
      alarmMinute = (alarmMinute + 59) % 60; // Decrement minute
    } else if (rightButtonPressed) {
      alarmMinute = (alarmMinute + 1) % 60; // Increment minute
    } else if (setButtonPressed) {
      setAlarmTime(alarmHour, alarmMinute); // Set the alarm
      alarmSettingStage = 0; // Reset stage
      openSetAlarmMenu = false; // Exit set alarm menu
    }
  }
}

#endif // MENUHANDLER_H
