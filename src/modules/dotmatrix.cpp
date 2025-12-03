#include "dotmatrix.h"
#include "../config/pins.h"
#include <MD_MAX72xx.h>

//  ADJUST: Hardware type - try different types if display is wrong
// Options: PAROLA_HW, GENERIC_HW, ICSTATION_HW, FC16_HW
#define HARDWARE_TYPE MD_MAX72XX::FC16_HW
#define MAX_DEVICES 1

MD_MAX72XX mx = MD_MAX72XX(HARDWARE_TYPE, DOTMATRIX_CS, MAX_DEVICES);

void initDotMatrix() {
  mx.begin();
  mx.clear();
  mx.control(MD_MAX72XX::INTENSITY, 8); //  ADJUST: Brightness 0-15
}

void showIdle() {
  // Scrolling dot
  mx.clear();
  //  CUSTOMIZE: Add animation
}

void showPassword() {
  // Key icon - simple pattern
  mx.clear();
  byte keyIcon[] = {0x00, 0x3C, 0x42, 0x42, 0x7E, 0x18, 0x18, 0x00};
  for (int i = 0; i < 8; i++) {
    mx.setColumn(i, keyIcon[i]);
  }
}

void showMotion() {
  // Walking person - simple pattern
  mx.clear();
  byte walkIcon[] = {0x18, 0x18, 0x3C, 0x18, 0x5A, 0x18, 0x24, 0x42};
  for (int i = 0; i < 8; i++) {
    mx.setColumn(i, walkIcon[i]);
  }
}

void showMagnetic() {
  // Magnet icon
  mx.clear();
  byte magnetIcon[] = {0x7E, 0x81, 0x81, 0x81, 0x81, 0x42, 0x24, 0x18};
  for (int i = 0; i < 8; i++) {
    mx.setColumn(i, magnetIcon[i]);
  }
}

void showProximity() {
  // Target/radar icon
  mx.clear();
  byte targetIcon[] = {0x18, 0x24, 0x42, 0x99, 0x99, 0x42, 0x24, 0x18};
  for (int i = 0; i < 8; i++) {
    mx.setColumn(i, targetIcon[i]);
  }
}

void showSuccess() {
  // Checkmark
  mx.clear();
  byte checkIcon[] = {0x00, 0x01, 0x02, 0x04, 0x88, 0x50, 0x20, 0x00};
  for (int i = 0; i < 8; i++) {
    mx.setColumn(i, checkIcon[i]);
  }
}

void showFail() {
  // X mark
  mx.clear();
  byte xIcon[] = {0x00, 0x82, 0x44, 0x28, 0x10, 0x28, 0x44, 0x82};
  for (int i = 0; i < 8; i++) {
    mx.setColumn(i, xIcon[i]);
  }
}

void showLockdown() {
  // Skull - simple pattern
  mx.clear();
  byte skullIcon[] = {0x3C, 0x42, 0xA5, 0x81, 0xA5, 0x99, 0x42, 0x3C};
  for (int i = 0; i < 8; i++) {
    mx.setColumn(i, skullIcon[i]);
  }
}

void updateAnimation() {
  //  CUSTOMIZE: Add scrolling/animation logic if needed
}