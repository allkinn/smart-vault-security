/*
 * TEST: LCD I2C Display
 * 
 * Purpose: Verify LCD wiring and I2C address
 */

#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// ⚠️ TRY BOTH ADDRESSES: 0x27 or 0x3F
#define LCD_ADDRESS 0x27

LiquidCrystal_I2C lcd(LCD_ADDRESS, 16, 2);

void setup() {
  Serial.begin(9600);
  Serial.println("=== LCD I2C TEST ===");
  
  // Scan for I2C devices
  Serial.println("Scanning I2C bus...");
  Wire.begin();
  byte count = 0;
  
  for (byte i = 1; i < 127; i++) {
    Wire.beginTransmission(i);
    if (Wire.endTransmission() == 0) {
      Serial.print("Found device at 0x");
      if (i < 16) Serial.print("0");
      Serial.println(i, HEX);
      count++;
    }
  }
  
  if (count == 0) {
    Serial.println("ERROR: No I2C devices found!");
    Serial.println("Check wiring: SDA=A4, SCL=A5");
  } else {
    Serial.print("Found ");
    Serial.print(count);
    Serial.println(" device(s)");
  }
  Serial.println();
  
  Serial.println("Initializing LCD...");
  lcd.init();
  lcd.backlight();
  lcd.clear();
  
  Serial.println("If LCD is blank:");
  Serial.println("1. Try address 0x3F instead of 0x27");
  Serial.println("2. Adjust contrast pot on I2C module");
  Serial.println("3. Check I2C connections");
  Serial.println();
}

void loop() {
  // Test 1: Simple text
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("LCD TEST");
  lcd.setCursor(0, 1);
  lcd.print("Line 2 OK!");
  Serial.println("Display: Test 1 - Simple text");
  delay(2000);
  
  // Test 2: Full width
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("1234567890123456");
  lcd.setCursor(0, 1);
  lcd.print("ABCDEFGHIJKLMNOP");
  Serial.println("Display: Test 2 - Full width (16 chars)");
  delay(2000);
  
  // Test 3: Special characters
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Symbols: !@#$%^&");
  lcd.setCursor(0, 1);
  lcd.print("Numbers: 0123456");
  Serial.println("Display: Test 3 - Special chars");
  delay(2000);
  
  // Test 4: Cursor positioning
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("TL");
  lcd.setCursor(14, 0);
  lcd.print("TR");
  lcd.setCursor(0, 1);
  lcd.print("BL");
  lcd.setCursor(14, 1);
  lcd.print("BR");
  Serial.println("Display: Test 4 - Corner positioning");
  delay(2000);
  
  // Test 5: Backlight control
  Serial.println("Display: Test 5 - Backlight blink");
  for (int i = 0; i < 3; i++) {
    lcd.noBacklight();
    delay(300);
    lcd.backlight();
    delay(300);
  }
  
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("ALL TESTS PASS");
  lcd.setCursor(0, 1);
  lcd.print("Ready for use!");
  Serial.println("=== ALL TESTS COMPLETE ===");
  Serial.println();
  delay(3000);
}