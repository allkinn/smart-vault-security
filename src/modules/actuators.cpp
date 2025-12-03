#include "actuators.h"
#include "../config/pins.h"
#include "../config/constants.h"
#include <Servo.h>
#include <Arduino.h>

Servo lockServo;

void initActuators() {
  pinMode(LED_RED, OUTPUT);
  pinMode(LED_YELLOW, OUTPUT);
  pinMode(LED_GREEN, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);
  
  lockServo.attach(SERVO_PIN);
  lockVault();
}

void lockVault() {
  //  ADJUST: Test servo direction
  lockServo.write(SERVO_LOCKED);
}

void unlockVault() {
  lockServo.write(SERVO_UNLOCKED);
}

void setLED(char color, bool state) {
  #ifdef LED_GREEN  // Only if defined
    if (color == 'G') digitalWrite(LED_GREEN, state);
  #endif
}

void blinkLED(char color, int times, int delayMs) {
  for (int i = 0; i < times; i++) {
    setLED(color, true);
    delay(delayMs);
    setLED(color, false);
    delay(delayMs);
  }
}

void beep(int frequency, int duration) {
  tone(BUZZER_PIN, frequency, duration);
  delay(duration);
  noTone(BUZZER_PIN);
}

void playSuccess() {
  //  ADJUST: Customize melody
  beep(BUZZ_SUCCESS, 100);
  delay(50);
  beep(BUZZ_SUCCESS * 1.2, 100);
  delay(50);
  beep(BUZZ_SUCCESS * 1.5, 200);
}

void playFail() {
  beep(BUZZ_FAIL, 300);
  delay(100);
  beep(BUZZ_FAIL, 300);
}

void playAlarm() {
  //  ADJUST: Alarm pattern
  for (int i = 0; i < 3; i++) {
    tone(BUZZER_PIN, BUZZ_ALARM);
    delay(200);
    tone(BUZZER_PIN, BUZZ_ALARM * 0.8);
    delay(200);
  }
  noTone(BUZZER_PIN);
}
