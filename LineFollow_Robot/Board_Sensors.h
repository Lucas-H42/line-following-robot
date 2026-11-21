#pragma once
#ifndef BOARD_SENSORS_H
#define BOARD_SENSORS_H

#include <Arduino.h>

struct SerialData {
    bool isActive = false;

    const int BAUD = 115200;
};
struct BMP180Data {
    bool isActive = false;

    float temp{};
    float pressure{};
    float altitude{};
};
struct MPU6050Data {
    bool isActive = false;

    float temp{};
    float angleX{};
    float angleY{};
    float angleZ{};
    float accelX{};
    float accelY{};
    float accelZ{};
    float accelAngX{};
    float accelAngY{};
    float accelAngZ{};
};
struct GPSData {
    bool isActive = false;

    float latitude{};
    float longitude{};
    //other things here
    float altitude{};
};
struct RF24Data {
    bool isActive = false;

    //stuff here ig
};
struct BoardTelemetry {
    SerialData serial;
    BMP180Data bmp;
    MPU6050Data imu;
    GPSData gps;
    RF24Data radio;
};
extern BoardTelemetry telemetry;

bool StartComponent(auto &component, const String &componentName);
void SetupBoardSensors();
void SensorTestCycle();

#endif