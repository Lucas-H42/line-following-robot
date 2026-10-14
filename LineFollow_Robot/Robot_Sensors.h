#ifndef ROBOT_SENSORS_H
#define ROBOT_SENSORS_H

#include <Arduino.h>

void SetupRobotSensors();
int GetLeftSensor();
int GetCentreSensor();
int GetRightSensor();
void RunSteering();

#endif