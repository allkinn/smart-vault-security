#ifndef CONSTANTS_H
#define CONSTANTS_H

// ========== TUNABLE PARAMETERS ==========

// PASSWORD SETTINGS
#define PASSWORD_LENGTH     4
#define PASSWORD_CODE       "1234"  //  ADJUST: Change this
#define MAX_PASSWORD_FAILS  3

// STAGE TIMEOUTS (milliseconds)
#define PASSWORD_TIMEOUT    30000   //  ADJUST: 30 seconds
#define MOTION_TIMEOUT      10000   //  ADJUST: 10 seconds
#define MAGNETIC_TIMEOUT    15000   //  ADJUST: 15 seconds
#define PROXIMITY_TIMEOUT   20000   //  ADJUST: 20 seconds

// MOTION DETECTION
#define MOTION_WINDOW       5000    //  ADJUST: Must detect within 5sec

// PROXIMITY SETTINGS
#define PROX_MIN_DISTANCE   8       //  ADJUST: Minimum cm
#define PROX_MAX_DISTANCE   12      //  ADJUST: Maximum cm
#define PROX_HOLD_TIME      3000    //  ADJUST: Must hold 3 seconds

// SERVO SETTINGS
#define SERVO_LOCKED        0       //  ADJUST: Locked position (degrees)
#define SERVO_UNLOCKED      90      //  ADJUST: Unlocked position

// BUZZER FREQUENCIES
#define BUZZ_KEYPRESS       2000
#define BUZZ_SUCCESS        1500
#define BUZZ_FAIL           500
#define BUZZ_ALARM          800

// LED BLINK RATES
#define BLINK_FAST          100
#define BLINK_SLOW          500

// SYSTEM
#define SERIAL_BAUD         9600
#define LOCKDOWN_DURATION   60000   //  ADJUST: 1 minute lockdown

#endif