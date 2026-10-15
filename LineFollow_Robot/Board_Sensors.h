#pragma once
#ifndef BOARD_SENSORS_H
#define BOARD_SENSORS_H

#include <Arduino.h>

extern float bmpTemp;
extern float pressure;
extern float altitude;
extern float mpuTemp;
extern float angleX;
extern float angleY;
extern float angleZ;
extern float accelX;
extern float accelY;
extern float accelZ;
extern float accelAngX;
extern float accelAngY;
extern float accelAngZ;

void SetupBoardSensors();
void SensorTestCycle();

#endif