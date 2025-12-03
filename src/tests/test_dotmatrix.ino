/*
 * TEST: MAX7219 Dot Matrix (8x8)
 * 
 * Purpose: Verify dot matrix wiring and orientation
 * 
 * Instructions:
 * 1. Upload this sketch
 * 2. Observe patterns on matrix
 * 3. Verify orientation is correct
 * 4. Adjust HARDWARE_TYPE if scrambled
 * 
 * Expected Output:
 * Series of test patterns cycling on display
 */

#include <MD_MAX72xx.h>

// ⚠️ MATCH THESE TO YOUR pins.h
#define DOTMATRIX_DIN 11
#define DOTMATRIX_CLK 10
#define DOTMATRIX_CS 9

// ⚠️ TRY DIFFERENT HARDWARE TYPES IF DISPLAY IS SCRAMBLED
// Options: PAROLA_HW, GENERIC_HW, ICSTATION_HW, FC16_HW
#define HARDWARE_TYPE MD_MAX72XX::FC16_HW

#define MAX_DEVICES 1

MD_MAX72XX mx = MD_MAX72XX(HARDWARE_TYPE, DOTMATRIX_CS, MAX_DEVICES);

void setup() {
  Serial.begin(9600);
  Serial.println("=== DOT MATRIX TEST ===");
  
  mx.begin();
  mx.clear();
  
  // Test brightness levels
  Serial.println("Testing brightness levels...");
  for (int i = 0; i <= 15; i++) {
    mx.control(MD_MAX72XX::INTENSITY, i);
    mx.setPoint(3, 3, true);
    delay(100);
  }
  
  // Set medium brightness
  mx.control(MD_MAX72XX::INTENSITY, 8); // ⚠️ ADJUST: 0-15
  mx.clear();
  
  Serial.println("Starting pattern tests...");
  Serial.println("If display is scrambled, try different HARDWARE_TYPE");
  Serial.println();
}

void loop() {
  // Test 1: Single pixel walk
  Serial.println("Test 1: Pixel walk");
  mx.clear();
  for (int row = 0; row < 8; row++) {
    for (int col = 0; col < 8; col++) {
      mx.setPoint(row, col, true);
      delay(50);
      mx.setPoint(row, col, false);
    }
  }
  delay(500);
  
  // Test 2: Row scan
  Serial.println("Test 2: Row scan");
  mx.clear();
  for (int row = 0; row < 8; row++) {
    for (int col = 0; col < 8; col++) {
      mx.setPoint(row, col, true);
    }
    delay(200);
    mx.clear();
  }
  delay(500);
  
  // Test 3: Column scan
  Serial.println("Test 3: Column scan");
  mx.clear();
  for (int col = 0; col < 8; col++) {
    for (int row = 0; row < 8; row++) {
      mx.setPoint(row, col, true);
    }
    delay(200);
    mx.clear();
  }
  delay(500);
  
  // Test 4: Patterns
  Serial.println("Test 4: Test patterns");
  
  // Checkboard
  mx.clear();
  for (int row = 0; row < 8; row++) {
    for (int col = 0; col < 8; col++) {
      if ((row + col) % 2 == 0) {
        mx.setPoint(row, col, true);
      }
    }
  }
  delay(1000);
  
  // Border
  mx.clear();
  for (int i = 0; i < 8; i++) {
    mx.setPoint(0, i, true);
    mx.setPoint(7, i, true);
    mx.setPoint(i, 0, true);
    mx.setPoint(i, 7, true);
  }
  delay(1000);
  
  // X pattern
  mx.clear();
  for (int i = 0; i < 8; i++) {
    mx.setPoint(i, i, true);
    mx.setPoint(i, 7-i, true);
  }
  delay(1000);
  
  // Test 5: Icons (using setColumn)
  Serial.println("Test 5: Icon patterns");
  
  // Smiley face
  byte smiley[] = {0x3C, 0x42, 0xA5, 0x81, 0xA5, 0x99, 0x42, 0x3C};
  displayIcon(smiley, "Smiley");
  
  // Heart
  byte heart[] = {0x00, 0x66, 0xFF, 0xFF, 0xFF, 0x7E, 0x3C, 0x18};
  displayIcon(heart, "Heart");
  
  // Arrow up
  byte arrowUp[] = {0x18, 0x3C, 0x7E, 0x18, 0x18, 0x18, 0x18, 0x18};
  displayIcon(arrowUp, "Arrow Up");
  
  // Arrow down
  byte arrowDown[] = {0x18, 0x18, 0x18, 0x18, 0x18, 0x7E, 0x3C, 0x18};
  displayIcon(arrowDown, "Arrow Down");
  
  // Check mark
  byte check[] = {0x00, 0x01, 0x02, 0x04, 0x88, 0x50, 0x20, 0x00};
  displayIcon(check, "Check");
  
  // X mark
  byte xmark[] = {0x00, 0x82, 0x44, 0x28, 0x10, 0x28, 0x44, 0x82};
  displayIcon(xmark, "X mark");
  
  // Key icon
  byte key[] = {0x00, 0x3C, 0x42, 0x42, 0x7E, 0x18, 0x18, 0x00};
  displayIcon(key, "Key");
  
  // Lock icon
  byte lock[] = {0x3C, 0x42, 0x42, 0xFF, 0xFF, 0xDB, 0xDB, 0xFF};
  displayIcon(lock, "Lock");
  
  // Test 6: Scrolling text simulation
  Serial.println("Test 6: Horizontal scroll");
  for (int offset = 7; offset >= -8; offset--) {
    mx.clear();
    if (offset >= 0 && offset < 8) {
      for (int i = 0; i < 8; i++) {
        mx.setPoint(i, offset, true);
      }
    }
    delay(100);
  }
  
  Serial.println("=== ALL TESTS COMPLETE ===");
  Serial.println();
  delay(2000);
}

void displayIcon(byte pattern[], const char* name) {
  mx.clear();
  for (int i = 0; i < 8; i++) {
    mx.setColumn(i, pattern[i]);
  }
  Serial.print("Displaying: ");
  Serial.println(name);
  delay(1500);
}