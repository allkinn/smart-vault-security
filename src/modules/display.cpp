#include "display.h"
#include "../config/pins.h"

LiquidCrystal_I2C lcd(LCD_ADDRESS, 16, 2);

void initDisplay() {
  lcd.init();
  lcd.backlight();
  lcd.clear();
}

void displayMessage(const char* line1, const char* line2) {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(line1);
  if (line2[0] != '\0') {
    lcd.setCursor(0, 1);
    lcd.print(line2);
  }
}

void displayClear() {
  lcd.clear();
}

void displayProgress(const char* stage, int percent) {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(stage);
  lcd.setCursor(0, 1);
  lcd.print("Progress: ");
  lcd.print(percent);
  lcd.print("%");
}