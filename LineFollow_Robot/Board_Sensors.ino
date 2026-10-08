//The libraries for sensor and transmitter components
#include <Arduino.h>
#include <TinyGPSPlus.h>
#include <MPU6050_light.h>
#include <BMP180I2C.h>
#include <RF24.h>
#include <RF24_config.h>
#include <nRF24L01.h>
#include <printf.h>
#include "Wire.h"

//Create component objects
BMP180I2C barometer(0x77);
MPU6050 IMU(Wire);
//SoftwareSerial gpsSerial(PA1, PA0);
//TingGPSPlus gps;

//Constant variables
const String BMP_ID = "BMP180";
const String MPU_ID = "MPU6050";
const String GPS_ID = "TinyGPS";
const String RADIO_ID = "RF24";
//Variables for measurements
float temp;
float pressure;
float velocity;
float altitude;
float compassBearing;
float angleX;
float angleY;
float angleZ;
float accelX;
float accelY;
float accelZ;
float accelAngX;
float accelAngY;
float accelAngZ;

void SetupBoardSensors() {
  //Set up MPU6050
  StartComponent(MPU_ID);
  Serial.println("Calculating offsets, do not move the board...");
  delay(1000);
  IMU.calcOffsets();
  Serial.println("Calculation complete. MPU6050 initialised successfully.");

  //Set up BMP180
  Wire.begin();
  StartComponent(BMP_ID);
  barometer.resetToDefaults();
	barometer.setSamplingMode(BMP180MI::MODE_UHR);
  Serial.println("BMP180 initialised successfully.");
}

void SensorTestCycle() {
  Serial.println("Testing cycle: ");
  UseBMP();
  //UseMPU();
  //UseGPS();
  //TransmitData();
  Serial.println();
}

void UseBMP() {
  //Get and print the temperature
  Serial.print("Temperature(degC):");
	temp = barometer.readTemperature();
  Serial.print(temp);
  Serial.print(",");

  //Get and print the pressure
  Serial.print("Pressure(hPa):");
  pressure = barometer.readPressure() / 100;
  Serial.print(pressure);
  Serial.print(",");
}

void UseMPU() {

}

void TransmitData() {
}

//To start a component, name component
void StartComponent(String component) {
  //Try test for the first time
  int counter = 1;
  Serial.print("Attempting to start ");
  Serial.println(component);
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
  Serial.print(component);
  Serial.print(" ready. ");
  Serial.print("Tried ");
  Serial.print(counter);
  Serial.println(" time(s).");
}

//Check if the component of the appropriate name has started
bool IsComponentReady(String componentName) {
  if (componentName == MPU_ID && IMU.begin()) {
    return true;
  } 
  else if (componentName == BMP_ID && barometer.begin()) {
    return true;
  }
  /*else if (componentName == GPS_ID && ) {
    return true;
  }
  else if (componentName == RADIO_ID && ) {
    return true;
  }*/
  else {
    return false;
  }
}

float calcAltitude(int pressurePa) {
  float hPa = 0;
  float altitudeFeet = 0;
  float altitudeMeters = 0;
  hPa = 0.01 * pressurePa;
  altitudeFeet = ((1 - pow((hPa / 1013.25), 0.190284)) * 145366.45);
  altitudeMeters = 0.3048 * altitudeFeet;
  return(altitudeMeters);
}