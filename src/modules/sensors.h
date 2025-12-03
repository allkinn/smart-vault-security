#ifndef SENSORS_H
#define SENSORS_H

void initSensors();
bool checkMotion();
bool checkMagnetic();
float getDistance();
bool isInProximityRange();

#endif