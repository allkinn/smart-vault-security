#ifndef PINS_H
#define PINS_H

// Keypad pins (4x4)
#define KEYPAD_ROW1 A1
#define KEYPAD_ROW2 A2  
#define KEYPAD_ROW3 A3
#define KEYPAD_ROW4 D6
#define KEYPAD_COL1 D7
#define KEYPAD_COL2 D8
#define KEYPAD_COL3 D12
#define KEYPAD_COL4 D13

// LCD I2C (A4=SDA, A5=SCL automatic)
#define LCD_ADDRESS 0x27

// Dot Matrix
#define DOTMATRIX_DIN 11
#define DOTMATRIX_CLK 10
#define DOTMATRIX_CS 9

// Servo
#define SERVO_PIN 3

// Sensors
#define HC_TRIG_PIN 4
#define HC_ECHO_PIN 5
#define PIR_PIN 2
#define HALL_PIN A0

// Output
#define BUZZER_PIN 1  // D1, sacrifice Serial TX
