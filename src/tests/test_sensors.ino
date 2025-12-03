/*
 * TEST: All Sensors (PIR, Hall Effect, HC-SR04)
 * 
 * Purpose: Verify sensor readings and calibrate thresholds
 */

// ⚠️ MATCH THESE TO YOUR pins.h
#define HC_TRIG_PIN 4
#define HC_ECHO_PIN 5
#define PIR_PIN 2
#define HALL_PIN A0

void setup() {
  Serial.begin(9600);
  Serial.println("=== SENSOR TEST ===");
  Serial.println();
  
  pinMode(PIR_PIN, INPUT);
  pinMode(HALL_PIN, INPUT);
  pinMode(HC_TRIG_PIN, OUTPUT);
  pinMode(HC_ECHO_PIN, INPUT);
  
  Serial.println("Waiting 5 seconds for PIR to stabilize...");
  for (int i = 5; i > 0; i--) {
    Serial.print(i);
    Serial.print("...");
    delay(1000);
  }
  Serial.println("Ready!");
  Serial.println();
  
  Serial.println("TEST INSTRUCTIONS:");
  Serial.println("1. PIR: Wave hand to trigger");
  Serial.println("2. Hall: Bring magnet close");
  Serial.println("3. HC-SR04: Move hand at different distances");
  Serial.println();
  delay(2000);
}

void loop() {
  Serial.println("========================================");
  
  // Test PIR
  bool motionDetected = digitalRead(PIR_PIN);
  Serial.print("PIR Motion: ");
  if (motionDetected) {
    Serial.println("DETECTED ✓");
  } else {
    Serial.println("No motion");
  }
  
  // Test Hall Effect
  int hallValue = digitalRead(HALL_PIN);
  Serial.print("Hall Sensor: ");
  if (hallValue == LOW) {
    Serial.println("MAGNET DETECTED ✓ (active LOW)");
  } else if (hallValue == HIGH) {
    Serial.println("No magnet (or active HIGH?)");
  }
  Serial.print("  Raw value: ");
  Serial.println(hallValue);
  
  // Test HC-SR04
  float distance = getDistance();
  Serial.print("Distance: ");
  if (distance > 0) {
    Serial.print(distance);
    Serial.print(" cm");
    
    if (distance >= 8 && distance <= 12) {
      Serial.println("  ✓ IN RANGE [8-12cm]");
    } else if (distance < 8) {
      Serial.println("  (too close)");
    } else {
      Serial.println("  (too far)");
    }
  } else {
    Serial.println("ERROR (no echo)");
  }
  
  Serial.println();
  delay(500);
}

float getDistance() {
  digitalWrite(HC_TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(HC_TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(HC_TRIG_PIN, LOW);
  
  long duration = pulseIn(HC_ECHO_PIN, HIGH, 30000);
  
  if (duration == 0) return -1;
  
  float distance = duration * 0.034 / 2;
  
  if (distance < 2 || distance > 400) return -1;
  
  return distance;
}