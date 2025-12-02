# Smart Vault Security System

**Multi-stage authentication system using Arduino Uno**

---

##  Overview

4-layer security vault prototype featuring:
- **Stage 1:** Keypad password authentication
- **Stage 2:** PIR motion detection verification
- **Stage 3:** Magnetic key alignment
- **Stage 4:** Ultrasonic proximity calibration

Successful completion of all stages unlocks servo mechanism.

---

##  Hardware Requirements

### Microcontroller
- Arduino Uno R3

### Input Devices
- Keypad 4x4 matrix
- HC-SR04 ultrasonic sensor
- PIR HC-SR501 motion sensor
- Hall effect magnetic sensor
- DHT11 (optional - not used in current config)

### Output Devices
- LCD 16x2 with I2C module (address 0x27 or 0x3F)
- MAX7219 Dot Matrix (8x8)
- SG90 Servo motor
- Active buzzer
- LEDs: Red, Yellow, Green

### Power
- USB (5V) for Arduino + logic
- External 5-9V supply for servo (recommended)
- Common ground between Arduino and external PSU

---

##  Pin Configuration

| Component | Arduino Pins | Notes |
|-----------|--------------|-------|
| Keypad Row 1-4 | A1, A2, A3, D6 | 4x4 matrix |
| Keypad Col 1-4 | D7, D8, D12, D13 | |
| LCD I2C | A4 (SDA), A5 (SCL) | Check address |
| Dot Matrix | D11 (DIN), D10 (CLK), D9 (CS) | SPI |
| Servo | D3 | PWM capable |
| HC-SR04 | D4 (Trig), D5 (Echo) | |
| PIR Sensor | D2 | Digital input |
| Hall Sensor | A0 | Digital mode |
| Buzzer | A6 | Digital mode |
| LED Red | A7 | Digital mode |
| LED Yellow | D14/A0 | Share if needed |
| LED Green | D15/A1 | Share if needed |

**Total: 19/20 pins used**

---

##  Required Libraries

Install via Arduino IDE Library Manager:

```
1. Keypad by Mark Stanley & Alexander Brevig
2. LiquidCrystal I2C by Frank de Brabander
3. MD_MAX72XX by MajicDesigns
4. Servo (built-in)
```

---

## 🚀 Quick Start

### 1. Clone Repository
```bash
git clone <your-repo-url>
cd smart-vault-security
```

### 2. Install Libraries
Open Arduino IDE → Tools → Manage Libraries → Search and install required libraries

### 3. Test Individual Components
Upload test sketches in order:
```
src/tests/test_keypad.ino
src/tests/test_sensors.ino
src/tests/test_display.ino
src/tests/test_dotmatrix.ino
```

### 4. Calibrate Sensors
Open Serial Monitor (9600 baud) and adjust values in `src/config/constants.h`

### 5. Upload Main Firmware
```
src/main/main.ino
```

---

##  Configuration & Calibration

### Critical Settings (MUST ADJUST)

Edit `src/config/constants.h`:

```cpp
// 1. PASSWORD - Change from default
#define PASSWORD_CODE "1234"

// 2. SERVO POSITIONS - Test with ServoTest sketch
#define SERVO_LOCKED 0      // Locked angle (0-180)
#define SERVO_UNLOCKED 90   // Unlocked angle

// 3. PROXIMITY RANGE - Measure and adjust
#define PROX_MIN_DISTANCE 8   // Min cm
#define PROX_MAX_DISTANCE 12  // Max cm

// 4. STAGE TIMEOUTS - Adjust difficulty
#define PASSWORD_TIMEOUT 30000   // 30 sec
#define MOTION_TIMEOUT 10000     // 10 sec
#define MAGNETIC_TIMEOUT 15000   // 15 sec
#define PROXIMITY_TIMEOUT 20000  // 20 sec
```

Edit `src/config/pins.h`:

```cpp
// LCD I2C Address - Run I2C scanner to find
#define LCD_ADDRESS 0x27  // Try 0x3F if not working
```

Edit `src/modules/sensors.cpp`:

```cpp
// Hall effect sensor logic (line ~20)
// Test if your sensor is active HIGH or LOW
return digitalRead(HALL_PIN) == LOW;  // Change if needed
```

### Optional Tuning

Adjust for better UX:
- Buzzer frequencies
- LED blink rates  
- Dot matrix brightness
- Proximity hold time

---

##  Usage / Demo Flow

### Starting System
1. Power on Arduino
2. LCD shows "VAULT READY"
3. Press `#` on keypad to begin

### Stage 1: Password Entry
- Enter 4-digit code on keypad
- Press `#` to submit
- Press `*` to clear
- Max 3 attempts, then lockdown

### Stage 2: Motion Detection
- Wave hand in front of PIR sensor
- Must detect within 10 seconds
- LED blinks yellow during detection

### Stage 3: Magnetic Key
- Tap magnet to hall effect sensor
- Hold until confirmation beep
- 15 second timeout

### Stage 4: Proximity Lock
- Position hand 8-12cm from HC-SR04
- Hold steady for 3 seconds
- Buzzer beeps faster when in range
- Distance shown on LCD

### Success
- Servo unlocks (90° rotation)
- Green LED solid
- Success melody plays
- Dot matrix shows checkmark

### Failure Modes
- **Wrong password 3x:** Lockdown for 60 seconds
- **Stage timeout:** Restart from Stage 1
- **Manual reset:** Press reset button on Arduino

---

##  Troubleshooting

### LCD Not Displaying
```cpp
// Try different I2C address in pins.h
#define LCD_ADDRESS 0x3F  // Instead of 0x27
```
Run I2C scanner sketch to find address

### Dot Matrix Shows Garbage
```cpp
// Try different hardware type in dotmatrix.cpp
#define HARDWARE_TYPE MD_MAX72XX::GENERIC_HW
// Options: FC16_HW, PAROLA_HW, ICSTATION_HW
```

### Servo Not Moving
- Check external power supply connection
- Verify common ground
- Test servo positions (0-180° range)
- Check if servo wire is connected to PWM pin

### HC-SR04 Returns -1 / Invalid Distance
- Check wiring (Trig/Echo swap?)
- Ensure clear line of sight
- Adjust timeout in sensors.cpp
- Test range: 2-400cm

### PIR Always Triggering / Never Triggering
- Check sensor sensitivity potentiometer
- Adjust time delay potentiometer
- Wait 60 seconds after power on for calibration
- Remove jumper if in repeatable trigger mode

### Hall Sensor Not Detecting
- Test magnet polarity (flip magnet)
- Check sensor type (active HIGH vs LOW)
- Reduce distance between magnet and sensor

### Keypad Not Responding
- Verify pin connections (easy to misalign)
- Test with test_keypad.ino
- Check if rowPins/colPins are correct

---

## 📂 Project Structure

```
smart-vault-security/
├── README.md                 # This file
├── .gitignore               
├── docs/
│   ├── wiring-diagram.png   # TODO: Add wiring photo
│   ├── pin-mapping.md       # Detailed pin reference
│   └── demo-script.md       # Presentation talking points
├── src/
│   ├── main/
│   │   └── main.ino         # Main firmware
│   ├── config/
│   │   ├── pins.h           # Pin definitions
│   │   └── constants.h      # Tunable parameters
│   ├── modules/
│   │   ├── display.h/cpp    # LCD functions
│   │   ├── dotmatrix.h/cpp  # MAX7219 animations
│   │   ├── sensors.h/cpp    # Sensor readings
│   │   ├── actuators.h/cpp  # Servo, buzzer, LEDs
│   │   └── keypad_handler.h/cpp # Password logic
│   └── tests/
│       ├── test_keypad.ino
│       ├── test_sensors.ino
│       ├── test_display.ino
│       └── test_dotmatrix.ino
└── hardware/
    └── bom.md               # Bill of materials
```

---

## 🔄 State Machine Logic

```
IDLE → PASSWORD → MOTION → MAGNETIC → PROXIMITY → UNLOCKED
  ↑       ↓         ↓         ↓           ↓
  └───────┴─────────┴─────────┴───────────┘
          (timeout/fail: restart)
  
  PASSWORD (3x fail) → LOCKDOWN (60s) → IDLE
```

---

##  Development Checklist

- [x] Modular code architecture
- [x] Pin optimization (20 pins max)
- [x] State machine implementation
- [x] Non-blocking timing (millis-based)
- [ ] Component testing (run test sketches)
- [ ] Sensor calibration
- [ ] Physical wiring
- [ ] Enclosure/mounting
- [ ] Demo dry runs (5x minimum)
- [ ] Backup plan (manual overrides)

---

##  Demo Presentation Tips

### What to Say
*"This is a smart vault security system with 4-layer authentication. Each layer uses different sensor modalities to verify user identity. Stage 1 uses knowledge-based authentication via keypad. Stage 2 verifies physical presence through motion detection. Stage 3 requires a physical magnetic key. Stage 4 uses proximity calibration to ensure precise user control. The system uses state machine architecture with timeout-based security and fail-safe lockdown mode."*

### What to Show
1. Start from IDLE state
2. Input password (demonstrate wrong code = retry)
3. Motion detection (wave hand)
4. Magnetic key (tap magnet)
5. Proximity challenge (show distance feedback)
6. SUCCESS - servo unlocks

### Backup Plan
If sensor fails during demo:
- "This sensor is calibrated for different environment"
- Have manual trigger ready (hidden button)
- Explain the INTENDED behavior via Serial Monitor readings

---

## 📊 Component Cost Estimate

| Item | Qty |
|------|-----|
| Arduino Uno | 1 |
| Keypad 4x4 | 1 |
| LCD I2C | 1 |
| MAX7219 Dot Matrix | 1 |
| HC-SR04 | 1 |
| PIR HC-SR501 | 1 |
| Hall Sensor | 1 |
| Servo SG90 | 1 |
| LEDs + Buzzer |
| Breadboard + Jumpers |

---


##  Security Features

- Password authentication (knowledge factor)
- Motion presence verification (liveness check)
- Physical key requirement (possession factor)
- Proximity calibration (precision requirement)
- Lockdown mode after failed attempts
- Timeout-based auto-restart
- State machine prevents bypass attacks

---

##  Known Limitations

- DHT11 not used (unreliable in short timeframe)
- Seven segments not used (pin constraint)
- IR remote not used (not essential for core flow)
- DC/Stepper motors not used (servo sufficient)
- Single vault instance (no multi-user support)
- No persistent storage (resets on power cycle)

---

##  License

Educational project for microcontroller course.  
Feel free to modify and extend.

---

##  Acknowledgments

- Arduino community for libraries
- Instructor for component provision
- Coffee for making this possible in 40 hours

---

##  Support

**If stuck during development:**
1. Check Serial Monitor output (9600 baud)
2. Re-run test sketches for failing component
3. Verify wiring against pin mapping
4. Check constants.h calibration values
5. Search error messages + library name online

**Emergency contact:** [Your contact info]

---

**Last updated:** 3 Dec 2024, 20:00 WITA  
**Status:**  Firmware complete, ready for testing  
**Next milestone:** Component testing by Day 2 morning