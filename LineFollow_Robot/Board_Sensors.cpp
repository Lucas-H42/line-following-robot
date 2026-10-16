//The libraries for sensor and transmitter components
#include <Arduino.h>
#include <MPU6050_light.h>
#include <BMP180I2C.h>
#include <RF24.h>
#include <TinyGPSPlus.h>
#include <Wire.h>
#include "Board_Sensors.h"

constexpr int TEST_DELAY = 50;
constexpr int MAX_TEST = 100;

//Create component objects
BMP180I2C bmp(0x77);
MPU6050 imu(Wire);
//SoftwareSerial gpsSerial(PA1, PA0);
//TinyGPSPlus gps;

//The struct for telemetry data
BoardTelemetry telemetry;

//A METHOD CAN ONLY CALL OTHER METHODS ABOVE IT IN THE CODE

//Add publicly callable methods to get specific vals?
//ie. air pressure or temp so robot_sensors.cpp can calculate speed of sound
//ohhhh right speed of sound, thats how i got into this 3-hour rabbit hole where i
//wanted to optimise a completely unecessary thing
//i probably should do that...
//ah well, future me problem

float calcAltitude(float pressurePa) {
  float hPa = 0;
  float altitudeFeet = 0;
  float altitudeMeters = 0;
  hPa = 0.01 * pressurePa;
  altitudeFeet = (1 - pow(hPa / 1013.25, 0.190284)) * 145366.45;
  altitudeMeters = 0.3048 * altitudeFeet;
  return altitudeMeters;
}

void UseBMP() {
  //Get the temperature
	telemetry.bmpTemp = bmp.readTemperature();
  //Get the pressure
  telemetry.pressure = bmp.readPressure() / 100;
  //Calculate the altitude
  telemetry.altitude = calcAltitude(telemetry.pressure);
}
void UseIMU() {
  imu.update();

  telemetry.mpuTemp = imu.getTemp();

  telemetry.angleX = imu.getAngleX();
  telemetry.angleY = imu.getAngleY();
  telemetry.angleZ = imu.getAngleZ();

  telemetry.accelX = imu.getAccX();
  telemetry.accelY = imu.getAccY();
  telemetry.accelZ = imu.getAccZ();

  telemetry.accelAngX = imu.getGyroX();
  telemetry.accelAngY = imu.getGyroY();
  telemetry.accelAngZ = imu.getGyroZ();
}
void UseGPS() {

}

void TransmitData() {

}
void DisplayData() {
  if (bmpIsActive) {
    //Print the BMP data (recorded and calculated)
    Serial.print("Temperature(degC)(BMP180):");
    Serial.print(telemetry.bmpTemp);
    Serial.print(",");
    Serial.print("Pressure(hPa):");
    Serial.print(telemetry.pressure);
    Serial.print(",");
    Serial.print("Altitude(m):");
    Serial.print(telemetry.altitude);
    Serial.print(",");
  }

  if (imuIsActive) {
    //Print the IMU data
    Serial.print("Temperature(degC)(MPU5060):");
    Serial.print(telemetry.mpuTemp);
    Serial.print(",");
    Serial.print("X Acceleration(m/s^2):");
    Serial.print(telemetry.accelX);
    Serial.print(",");
    Serial.print("Y Acceleration(m/s^2):");
    Serial.print(telemetry.accelY);
    Serial.print(",");
    Serial.print("Z Acceleration(m/s^2):");
    Serial.print(telemetry.accelZ);
    Serial.print(",");
    Serial.print("X Angle/Pitch(deg):");
    Serial.print(telemetry.angleX);
    Serial.print(",");
    Serial.print("Y Angle/Roll(deg):");
    Serial.print(telemetry.angleY);
    Serial.print(",");
    Serial.print("Z Angle/Yaw(deg):");
    Serial.print(telemetry.angleZ);
    Serial.print(",");
  }

  if (gpsIsActive) {

  }
}


//Check if the component has started (automatically chooses which setup to use)
bool IsComponentReady(auto &component) {
  return component.begin();
}
// Serial is set up in LineFollow_Robot.cpp, so not needed here
// bool IsComponentReady(HardwareSerial &component) {
//   component.begin(115200);
//   return component;
// }
// Leave SoftwareSerial off for now, cause do I really need the gps? (Also it clashes with C++20)
// bool IsComponentReady(SoftwareSerial &component) {
//   component.begin(9600);
//   return true;
// }

//To start a component, pass it and its name
bool StartComponent(auto &component, const String &componentName) {
  //Try test for the first time
  int counter = 1;
  Serial.print("Attempting to start ");
  Serial.println(componentName);
  //If it's not ready
  while (!IsComponentReady(component)) {
    //Test repeatedly, showing an error every 100 tries
    if (counter % 100 == 0) {
      Serial.print("Failed ");
      Serial.print(counter);
      Serial.println(" times");
    }
    if (counter >= MAX_TEST) { //If it fails too main times, cancel
      Serial.print("Failed to start ");
      Serial.println(componentName);
      return false;
    }
    delay(TEST_DELAY);
    counter++;
  }
  //When it's ready, show success
  Serial.print(componentName);
  Serial.print(" ready. ");
  Serial.print("Tried ");
  Serial.print(counter);
  Serial.println(" time(s).");
  return true;
}

void SetupBoardSensors() {
  //Set up MPU6050
  if (StartComponent(imu,"MPU6050")) {
    Serial.println("Calculating offsets, do not move the board...");
    delay(1000);
    imu.calcOffsets();
    Serial.println("Calculation complete. MPU6050 initialised successfully.");
    imuIsActive = true;
  }

  //Set up BMP180
  Wire.begin();
  if (StartComponent(bmp,"BMP180")) {
    bmp.resetToDefaults();
    bmp.setSamplingMode(BMP180MI::MODE_UHR);
    Serial.println("BMP180 initialised successfully.");
    bmpIsActive = true;
  }
}

void SensorTestCycle() {
  if (bmpIsActive)
  { UseBMP(); }
  if (imuIsActive)
  { UseIMU(); }
  if (gpsIsActive)
  { UseGPS(); }
  if (radioIsActive)
  { TransmitData(); }
  if (serialIsActive) {
    Serial.println("Testing cycle: ");
    DisplayData();
    Serial.println();
  }
}