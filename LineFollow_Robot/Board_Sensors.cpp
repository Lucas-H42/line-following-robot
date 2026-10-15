//The libraries for sensor and transmitter components
#include <Arduino.h>
#include <MPU6050_light.h>
#include <BMP180I2C.h>
#include <RF24.h>
#include <TinyGPSPlus.h>
#include <Wire.h>
#include "Board_Sensors.h"

constexpr int TEST_DELAY = 50;

//Create component objects
BMP180I2C bmp(0x77);
MPU6050 imu(Wire);
//SoftwareSerial gpsSerial(PA1, PA0);
//TinyGPSPlus gps;

//Bools to check if things are active???
//Variables for measurements - all unused ik i should do smth abt that
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
  altitudeFeet = ((1 - pow((hPa / 1013.25), 0.190284)) * 145366.45);
  altitudeMeters = 0.3048 * altitudeFeet;
  return(altitudeMeters);
}

void UseBMP() {
  //Get and print the temperature
  Serial.print("Temperature(degC):");
	bmpTemp = bmp.readTemperature();
  Serial.print(bmpTemp);
  Serial.print(",");

  //Get and print the pressure
  Serial.print("Pressure(hPa):");
  pressure = bmp.readPressure() / 100;
  Serial.print(pressure);
  Serial.print(",");

  //Get and print the altitude
  Serial.print("Altitude(m):");
  altitude = calcAltitude(pressure);
  Serial.print(altitude);
  Serial.print(",");
}

void UseIMU() {
  imu.update();

  mpuTemp = imu.getTemp();

}

void TransmitData() {

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

//To start a component, name component
void StartComponent(auto &component, const String &componentName) {
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
    delay(TEST_DELAY);
    counter++;
  }
  //When it's ready, show success
  Serial.print(componentName);
  Serial.print(" ready. ");
  Serial.print("Tried ");
  Serial.print(counter);
  Serial.println(" time(s).");
}

void SetupBoardSensors() {
  //Set up MPU6050
  StartComponent(imu,"MPU6050");
  Serial.println("Calculating offsets, do not move the board...");
  delay(1000);
  imu.calcOffsets();
  Serial.println("Calculation complete. MPU6050 initialised successfully.");

  //Set up BMP180
  Wire.begin();
  StartComponent(bmp,"BMP180");
  bmp.resetToDefaults();
  bmp.setSamplingMode(BMP180MI::MODE_UHR);
  Serial.println("BMP180 initialised successfully.");
}

void SensorTestCycle() {
  Serial.println("Testing cycle: ");
  UseBMP();
  //UseIMU();
  //UseGPS();
  //TransmitData();
  Serial.println();
}