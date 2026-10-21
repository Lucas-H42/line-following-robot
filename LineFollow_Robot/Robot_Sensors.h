#ifndef ROBOT_SENSORS_H
#define ROBOT_SENSORS_H

#include <Arduino.h>

void SetupRobotSensors();
int GetLeftLine();
int GetCentreLine();
int GetRightLine();
void RunSteering();

#endif