#include "keypad_handler.h"
#include "display.h"
#include "actuators.h"
#include "pins.h"
#include "constants.h"
#include <Keypad.h>

const byte ROWS = 4;
const byte COLS = 4;

char keys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};

byte rowPins[ROWS] = {KEYPAD_ROW1, KEYPAD_ROW2, KEYPAD_ROW3, KEYPAD_ROW4};
byte colPins[COLS] = {KEYPAD_COL1, KEYPAD_COL2, KEYPAD_COL3, KEYPAD_COL4};

Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

void initKeypad() {
  // Keypad library handles initialization
}

bool checkPassword(unsigned long timeout) {
  String input = "";
  unsigned long startTime = millis();
  
  displayMessage("ENTER CODE:", "");
  
  while (millis() - startTime < timeout) {
    char key = keypad.getKey();
    
    if (key) {
      beep(BUZZ_KEYPRESS, 50);
      
      if (key == '#') {
        // Submit
        if (input == PASSWORD_CODE) {
          return true;
        } else {
          input = "";
          displayMessage("WRONG CODE!", "Try again...");
          playFail();
          delay(1000);
          displayMessage("ENTER CODE:", "");
        }
      } else if (key == '*') {
        // Clear
        input = "";
        displayMessage("ENTER CODE:", "");
      } else if (input.length() < PASSWORD_LENGTH) {
        input += key;
        
        // Display masked input
        String masked = "";
        for (int i = 0; i < input.length(); i++) masked += "*";
        displayMessage("ENTER CODE:", masked.c_str());
      }
    }
    
    // Show remaining time
    if ((millis() - startTime) % 5000 == 0) {
      int remaining = (timeout - (millis() - startTime)) / 1000;
      Serial.print("Time left: ");
      Serial.println(remaining);
    }
  }
  
  return false; // Timeout
}

 char getSingleKey() {
  return keypad.getKey();
}