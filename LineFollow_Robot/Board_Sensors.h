#pragma once
#ifndef BOARD_SENSORS_H
#define BOARD_SENSORS_H

#include <Arduino.h>

struct BMP180Data {
    float temp;
    float pressure;
    float altitude;
};
struct MPU6050Data {
    float temp;
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
struct GPSData {
    float latitude;
    float longitude;
    //other things here
    float altitude;
};
struct RF24Data {
    //stuff here ig
};
struct ActiveStatus {
    bool serial = false;
    bool bmp = false;
    bool imu = false;
    bool gps = false;
    bool radio = false;
};
struct BoardTelemetry {
    BMP180Data bmp;
    MPU6050Data imu;
    GPSData gps;
    RF24Data radio;
    ActiveStatus isActive;
};
extern BoardTelemetry telemetry;

bool StartComponent(auto &component, const String &componentName);
void SetupBoardSensors();
void SensorTestCycle();

#endif