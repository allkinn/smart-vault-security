#ifndef ACTUATORS_H
#define ACTUATORS_H

void initActuators();
void lockVault();
void unlockVault();
void setLED(char color, bool state);
void blinkLED(char color, int times, int delayMs);
void beep(int frequency, int duration);
void playSuccess();
void playFail();
void playAlarm();

#endif