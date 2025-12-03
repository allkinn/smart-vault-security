#include "../config/pins.h"
#include "../config/constants.h"
#include "../modules/display.h"
#include "../modules/sensors.h"
#include "../modules/actuators.h"
#include "../modules/keypad_handler.h"
#include "../modules/dotmatrix.h"

enum State {
  IDLE,
  PASSWORD,
  MOTION,
  MAGNETIC,
  PROXIMITY,
  UNLOCKED,
  LOCKDOWN
};

State currentState = IDLE;
unsigned long stageStartTime = 0;
int passwordFails = 0;
unsigned long proximityHoldStart = 0;
bool proximityHolding = false;

void setup() {
  Serial.begin(SERIAL_BAUD);
  Serial.println("=== SMART VAULT SECURITY v1.0 ===");
  
  initDisplay();
  initSensors();
  initActuators();
  initKeypad();
  initDotMatrix();
  
  displayMessage("SECURITY VAULT", "Initializing...");
  delay(2000);
  
  transitionTo(IDLE);
}

void loop() {
  switch(currentState) {
    case IDLE:
      handleIdle();
      break;
    case PASSWORD:
      handlePassword();
      break;
    case MOTION:
      handleMotion();
      break;
    case MAGNETIC:
      handleMagnetic();
      break;
    case PROXIMITY:
      handleProximity();
      break;
    case UNLOCKED:
      handleUnlocked();
      break;
    case LOCKDOWN:
      handleLockdown();
      break;
  }
}

void transitionTo(State newState) {
  currentState = newState;
  stageStartTime = millis();
  
  Serial.print("State: ");
  Serial.println(newState);
  
  // Turn off all LEDs
  setLED('R', false);
  setLED('Y', false);
  setLED('G', false);
  
  switch(newState) {
    case IDLE:
      displayMessage("VAULT READY", "Press # to start");
      showIdle();
      break;
    case PASSWORD:
      displayMessage("STAGE 1/4", "Password Entry");
      showPassword();
      setLED('Y', true);
      delay(1500);
      break;
    case MOTION:
      displayMessage("STAGE 2/4", "Motion Detect");
      showMotion();
      setLED('Y', true);
      delay(1500);
      break;
    case MAGNETIC:
      displayMessage("STAGE 3/4", "Magnetic Key");
      showMagnetic();
      setLED('Y', true);
      delay(1500);
      break;
    case PROXIMITY:
      displayMessage("STAGE 4/4", "Proximity Lock");
      showProximity();
      setLED('Y', true);
      proximityHolding = false;
      delay(1500);
      break;
    case UNLOCKED:
      displayMessage("ACCESS", "GRANTED!");
      showSuccess();
      setLED('G', true);
      playSuccess();
      unlockVault();
      break;
    case LOCKDOWN:
      displayMessage("SYSTEM", "LOCKDOWN!");
      showLockdown();
      playAlarm();
      break;
  }
}

void handleIdle() {
  // Wait for # key to start
  char key = keypad.getKey();
  if (key == '#') {
    beep(BUZZ_KEYPRESS, 50);
    passwordFails = 0;
    transitionTo(PASSWORD);
  }
}

void handlePassword() {
  bool success = checkPassword(PASSWORD_TIMEOUT);
  
  if (success) {
    Serial.println("Password correct!");
    blinkLED('G', 3, 100);
    delay(500);
    transitionTo(MOTION);
  } else {
    passwordFails++;
    Serial.print("Password fail count: ");
    Serial.println(passwordFails);
    
    if (passwordFails >= MAX_PASSWORD_FAILS) {
      transitionTo(LOCKDOWN);
    } else {
      displayMessage("TIMEOUT!", "Try again");
      blinkLED('R', 3, 200);
      delay(2000);
      transitionTo(PASSWORD);
    }
  }
}

void handleMotion() {
  unsigned long elapsed = millis() - stageStartTime;
  
  // Check timeout
  if (elapsed > MOTION_TIMEOUT) {
    displayMessage("MOTION TIMEOUT!", "Restarting...");
    playFail();
    blinkLED('R', 3, 200);
    delay(2000);
    transitionTo(PASSWORD);
    return;
  }
  
  // Display countdown
  int remaining = (MOTION_TIMEOUT - elapsed) / 1000;
  char msg[17];
  sprintf(msg, "Move in %ds", remaining);
  displayMessage("Show Movement:", msg);
  
  // Check motion
  if (checkMotion()) {
    // Motion detected - wait for stable period
    delay(500);
    if (checkMotion()) {
      Serial.println("Motion detected!");
      displayMessage("MOTION", "CONFIRMED!");
      blinkLED('G', 3, 100);
      playSuccess();
      delay(1000);
      transitionTo(MAGNETIC);
    }
  }
  
  // Blink yellow LED
  if (elapsed % 1000 < 500) {
    setLED('Y', true);
  } else {
    setLED('Y', false);
  }
}

void handleMagnetic() {
  unsigned long elapsed = millis() - stageStartTime;
  
  // Check timeout
  if (elapsed > MAGNETIC_TIMEOUT) {
    displayMessage("MAG TIMEOUT!", "Restarting...");
    playFail();
    blinkLED('R', 3, 200);
    delay(2000);
    transitionTo(PASSWORD);
    return;
  }
  
  // Display countdown
  int remaining = (MAGNETIC_TIMEOUT - elapsed) / 1000;
  char msg[17];
  sprintf(msg, "Time: %ds", remaining);
  displayMessage("Tap Magnet:", msg);
  
  // Check magnetic sensor
  if (checkMagnetic()) {
    delay(100); // Debounce
    if (checkMagnetic()) {
      Serial.println("Magnet detected!");
      displayMessage("MAGNETIC KEY", "ACCEPTED!");
      blinkLED('G', 3, 100);
      playSuccess();
      delay(1000);
      transitionTo(PROXIMITY);
    }
  }
  
  // Blink yellow LED
  if (elapsed % 500 < 250) {
    setLED('Y', true);
  } else {
    setLED('Y', false);
  }
}

void handleProximity() {
  unsigned long elapsed = millis() - stageStartTime;
  
  // Check timeout
  if (elapsed > PROXIMITY_TIMEOUT) {
    displayMessage("PROX TIMEOUT!", "Restarting...");
    playFail();
    blinkLED('R', 3, 200);
    delay(2000);
    transitionTo(PASSWORD);
    return;
  }
  
  float dist = getDistance();
  bool inRange = isInProximityRange();
  
  // Display distance
  char line1[17], line2[17];
  if (dist > 0) {
    sprintf(line1, "Dist: %.1fcm", dist);
  } else {
    sprintf(line1, "Dist: --");
  }
  
  if (inRange) {
    if (!proximityHolding) {
      proximityHoldStart = millis();
      proximityHolding = true;
    }
    
    unsigned long holdDuration = millis() - proximityHoldStart;
    int holdRemaining = (PROX_HOLD_TIME - holdDuration) / 1000 + 1;
    sprintf(line2, "HOLD: %ds", holdRemaining);
    
    // Success beep frequency
    if (holdDuration % 500 < 250) {
      tone(BUZZER_PIN, BUZZ_SUCCESS);
    } else {
      noTone(BUZZER_PIN);
    }
    
    showSuccess();  //or setLED('G', true);
    
    // Check if held long enough
    if (holdDuration >= PROX_HOLD_TIME) {
      noTone(BUZZER_PIN);
      Serial.println("Proximity success!");
      displayMessage("PROXIMITY", "CONFIRMED!");
      blinkLED('G', 5, 100);
      delay(1000);
      transitionTo(UNLOCKED);
      return;
    }
  } else {
    proximityHolding = false;
    sprintf(line2, "Range: 8-12cm");
    noTone(BUZZER_PIN);
    setLED('G', false);
    setLED('Y', true);
  }
  
  displayMessage(line1, line2);
  
  delay(100); // Small delay for stability
}

void handleUnlocked() {
  // Stay unlocked - wait for manual reset or timeout
  //  ADJUST: Add auto-lock after X seconds if needed
  displayMessage("VAULT UNLOCKED", "Reset to lock");
  
  // Optional: Auto-lock after 30 seconds
  if (millis() - stageStartTime > 30000) {
    lockVault();
    transitionTo(IDLE);
  }
}

void handleLockdown() {
  displayMessage("LOCKDOWN MODE", "Wait 60sec");
  blinkLED('R', 1, 250);
  
  //  ADJUST: Lockdown duration or add manual override
  if (millis() - stageStartTime > LOCKDOWN_DURATION) {
    passwordFails = 0;
    transitionTo(IDLE);
  }
}
