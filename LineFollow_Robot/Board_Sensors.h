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
struct BoardTelemetry {
    BMP180Data bmp;
    MPU6050Data imu;
    GPSData gps;
    RF24Data radio;

};
extern BoardTelemetry telemetry;

//Bools to know if things are active
extern bool serialIsActive;
extern bool bmpIsActive;
extern bool imuIsActive;
extern bool gpsIsActive;
extern bool radioIsActive;

bool StartComponent(auto &component, const String &componentName);
void SetupBoardSensors();
void SensorTestCycle();

#endif