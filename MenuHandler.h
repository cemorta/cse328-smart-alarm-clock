#ifndef MENUHANDLER_H
#define MENUHANDLER_H

#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

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

// Current menu item
MenuItem currentMenuItem = MENU_SHOW_TIME;

void setupMenu() {
  currentMenuItem = MENU_SHOW_TIME;
}

void navigateMenu(bool leftButtonPressed, bool setButtonPressed, bool rightButtonPressed) {
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
        // Add logic to set the alarm
        break;
      case MENU_SET_TIME:
        // Add logic to set the time
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
      display.setCursor(0, 10);
      display.println("1. Show Time");
      displayTime(display); // Display current time
      break;
    case MENU_SET_ALARM:
      display.setCursor(0, 10);
      display.println("2. Set Alarm");
      // Add additional display logic for setting alarm
      break;
    case MENU_SET_TIME:
      display.setCursor(0, 10);
      display.println("3. Set Time");
      // Add additional display logic for setting time
      break;
    default:
      break;
  }

  display.display();
}

#endif // MENUHANDLER_H
