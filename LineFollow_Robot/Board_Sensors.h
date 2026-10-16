#pragma once
#ifndef BOARD_SENSORS_H
#define BOARD_SENSORS_H

#include <Arduino.h>

struct BoardTelemetry {
    float bmpTemp;
    float pressure;
    float altitude;
    float mpuTemp;
    float angleX;
    float angleY;
    float angleZ;
    float accelX;
    float accelY;
    float accelZ;
    float accelAngX;
    float accelAngY;
    float accelAngZ;
};
extern BoardTelemetry telemetry;

void SetupBoardSensors();
void SensorTestCycle();

#endif