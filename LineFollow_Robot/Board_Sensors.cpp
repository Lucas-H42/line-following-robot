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
constexpr int SERIAL_BAUD = 115200;

//Create component objects
BMP180I2C BMP(0x77);
MPU6050 IMU(Wire);
//SoftwareSerial GPSSerial(PA1, PA0);
//TinyGPSPlus GPS;

//The struct for telemetry data
BoardTelemetry telemetry;
//Set the activity bools to default off (cause nothing's been initialised yet)
bool serialIsActive = false;
bool bmpIsActive = false;
bool imuIsActive = false;
bool gpsIsActive = false;
bool radioIsActive = false;

//A METHOD CAN ONLY CALL OTHER METHODS ABOVE IT IN THE CODE

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
	telemetry.bmp.temp = BMP.readTemperature();
  //Get the pressure
  telemetry.bmp.pressure = BMP.readPressure() / 100;
  //Calculate the altitude
  telemetry.bmp.altitude = calcAltitude(telemetry.bmp.pressure);
}
void UseIMU() {
  IMU.update();

  telemetry.imu.temp = IMU.getTemp();

  telemetry.imu.angleX = IMU.getAngleX();
  telemetry.imu.angleY = IMU.getAngleY();
  telemetry.imu.angleZ = IMU.getAngleZ();

  telemetry.imu.accelX = IMU.getAccX();
  telemetry.imu.accelY = IMU.getAccY();
  telemetry.imu.accelZ = IMU.getAccZ();

  telemetry.imu.accelAngX = IMU.getGyroX();
  telemetry.imu.accelAngY = IMU.getGyroY();
  telemetry.imu.accelAngZ = IMU.getGyroZ();
}
void UseGPS() {

}

void TransmitData() {

}
void DisplayData() {
  if (bmpIsActive) {
    //Print the BMP data (recorded and calculated)
    Serial.print("Temperature(degC)(BMP180):");
    Serial.print(telemetry.bmp.temp);
    Serial.print(",");
    Serial.print("Pressure(hPa):");
    Serial.print(telemetry.bmp.pressure);
    Serial.print(",");
    Serial.print("Altitude(m):");
    Serial.print(telemetry.bmp.altitude);
    Serial.print(",");
  }

  if (imuIsActive) {
    //Print the IMU data
    Serial.print("Temperature(degC)(MPU5060):");
    Serial.print(telemetry.imu.temp);
    Serial.print(",");
    Serial.print("X Acceleration(m/s^2):");
    Serial.print(telemetry.imu.accelX);
    Serial.print(",");
    Serial.print("Y Acceleration(m/s^2):");
    Serial.print(telemetry.imu.accelY);
    Serial.print(",");
    Serial.print("Z Acceleration(m/s^2):");
    Serial.print(telemetry.imu.accelZ);
    Serial.print(",");
    Serial.print("X Angle/Pitch(deg):");
    Serial.print(telemetry.imu.angleX);
    Serial.print(",");
    Serial.print("Y Angle/Roll(deg):");
    Serial.print(telemetry.imu.angleY);
    Serial.print(",");
    Serial.print("Z Angle/Yaw(deg):");
    Serial.print(telemetry.imu.angleZ);
    Serial.print(",");
  }

  if (gpsIsActive) {

  }
}


//Check if the component has started (automatically chooses which setup to use)
bool IsComponentReady(auto &component) {
  return component.begin();
}
// Override for when ComponentSetup is called with Serial
bool IsComponentReady(HardwareSerial &component) {
  component.begin(SERIAL_BAUD);
  return component;
}
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
  if (StartComponent(IMU,"MPU6050")) {
    Serial.println("Calculating offsets, do not move the board...");
    delay(1000);
    IMU.calcOffsets();
    Serial.println("Calculation complete. MPU6050 initialised successfully.");
    imuIsActive = true;
  }

  //Set up BMP180
  Wire.begin();
  if (StartComponent(BMP,"BMP180")) {
    BMP.resetToDefaults();
    BMP.setSamplingMode(BMP180MI::MODE_UHR);
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