#ifndef DISPLAY_H
#define DISPLAY_H

#include <LiquidCrystal_I2C.h>

void initDisplay();
void displayMessage(const char* line1, const char* line2 = "");
void displayClear();
void displayProgress(const char* stage, int percent);

#endif