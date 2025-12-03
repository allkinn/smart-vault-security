#include "sensors.h"
#include "../config/pins.h"
#include "../config/constants.h"
#include <Arduino.h>

void initSensors() {
  pinMode(PIR_PIN, INPUT);
  pinMode(HALL_PIN, INPUT);
  pinMode(HC_TRIG_PIN, OUTPUT);
  pinMode(HC_ECHO_PIN, INPUT);
}

bool checkMotion() {
  return digitalRead(PIR_PIN) == HIGH;
}

bool checkMagnetic() {
  //  ADJUST: Hall effect logic depends on your sensor type
  // Some are active LOW, some active HIGH
  // Test and change if needed
  return digitalRead(HALL_PIN) == LOW;  // Assuming active LOW
}

float getDistance() {
  //  CALIBRATION POINT: HC-SR04 reading
  digitalWrite(HC_TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(HC_TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(HC_TRIG_PIN, LOW);
  
  long duration = pulseIn(HC_ECHO_PIN, HIGH, 30000); // 30ms timeout
  if (duration == 0) return -1; // No echo
  
  float distance = duration * 0.034 / 2;
  
  //  ADJUST: Filtering - ignore outliers
  if (distance < 2 || distance > 400) return -1;
  
  return distance;
}

bool isInProximityRange() {
  float dist = getDistance();
  if (dist < 0) return false;
  
  //  ADJUST: Check if within range
  return (dist >= PROX_MIN_DISTANCE && dist <= PROX_MAX_DISTANCE);
}