#ifndef PINS_H
#define PINS_H

// Keypad pins (4x4)
#define KEYPAD_ROW1    A1
#define KEYPAD_ROW2    A2
#define KEYPAD_ROW3    A3
#define KEYPAD_ROW4    6   // Using digital pin
#define KEYPAD_COL1    7
#define KEYPAD_COL2    8
#define KEYPAD_COL3    12
#define KEYPAD_COL4    13

// LCD I2C (uses A4=SDA, A5=SCL automatically)
#define LCD_ADDRESS    0x27  // ADJUST: Try 0x3F if LCD not detected

// Dot Matrix MAX7219
#define DOTMATRIX_DIN  11
#define DOTMATRIX_CLK  10
#define DOTMATRIX_CS   9

// Servo
#define SERVO_PIN      3

// Sensors
#define HC_TRIG_PIN    4
#define HC_ECHO_PIN    5
#define PIR_PIN        2
#define HALL_PIN       A0

// Outputs
#define BUZZER_PIN     A6   // Using analog as digital
#define LED_RED        A7
#define LED_YELLOW     14   // Same as A0 in digital mode
#define LED_GREEN      15   // Same as A1 in digital mode

// Note: We're using analog pins as digital where needed
// Total used: 19 pins (within Uno limits)

#endif