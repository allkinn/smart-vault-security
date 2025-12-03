/*
 * TEST: Keypad 4x4
 * 
 * Purpose: Verify keypad wiring and key detection
 * 
 * Instructions:
 * 1. Upload this sketch
 * 2. Open Serial Monitor (9600 baud)
 * 3. Press each key on keypad
 * 4. Verify correct key appears in Serial Monitor
 */

#include <Keypad.h>

// ⚠️ MATCH THESE TO YOUR pins.h
#define KEYPAD_ROW1 A1
#define KEYPAD_ROW2 A2
#define KEYPAD_ROW3 A3
#define KEYPAD_ROW4 6
#define KEYPAD_COL1 7
#define KEYPAD_COL2 8
#define KEYPAD_COL3 12
#define KEYPAD_COL4 13

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

void setup() {
  Serial.begin(9600);
  Serial.println("=== KEYPAD TEST ===");
  Serial.println("Press any key...");
  Serial.println();
}

void loop() {
  char key = keypad.getKey();
  
  if (key) {
    Serial.print("Key pressed: ");
    Serial.println(key);
    
    switch(key) {
      case '1': Serial.println("  -> Top-left"); break;
      case 'A': Serial.println("  -> Top-right"); break;
      case '*': Serial.println("  -> Bottom-left"); break;
      case 'D': Serial.println("  -> Bottom-right"); break;
    }
    Serial.println();
  }
}