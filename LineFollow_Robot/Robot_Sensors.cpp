#include <Arduino.h>
#include "Wheel_Control.h"

#define LIGHT_L PA8
#define LIGHT_C PB1
#define LIGHT_R PB0
#define SONIC_TRIG PA6
#define SONIC_ECHO PA7

float duration;
float distance;
const float soundSpeed = 0.0343; //cm per microsecond

void SetupRobotSensors() {
  pinMode(LIGHT_L, INPUT);
  pinMode(LIGHT_C, INPUT);
  pinMode(LIGHT_R, INPUT);

  pinMode(SONIC_TRIG, OUTPUT);
  pinMode(SONIC_ECHO, INPUT);
}

int GetLeftSensor() {
  return digitalRead(LIGHT_L);
}
int GetCentreSensor() {
  return digitalRead(LIGHT_C);
}
int GetRightSensor() {
  return digitalRead(LIGHT_R);
}


//The check and movement logic
void RunSteering() {
  //If it's on the line, exit
  if (GetCentreSensor() && !GetLeftSensor() && !GetRightSensor()) {
    SetMovement(1,1);
  }

}

float GetDistance() {
  digitalWrite(SONIC_TRIG, LOW);
  delayMicroseconds(2);

  duration = pulseIn(SONIC_ECHO, HIGH);
  distance = soundSpeed * duration/2;
  return distance;
}