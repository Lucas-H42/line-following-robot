#include "Robot_Sensors.h"
#include "Wheel_Control.h"

#define LIGHT_L PA8
#define LIGHT_C PB1
#define LIGHT_R PB0
#define SONIC_TRIG PA6
#define SONIC_ECHO PA7

void SetupRobotSensors() {
  pinMode(LIGHT_L, INPUT);
  pinMode(LIGHT_C, INPUT);
  pinMode(LIGHT_R, INPUT);

  pinMode(SONIC_TRIG, OUTPUT);
  pinMode(SONIC_ECHO, INPUT);
}

int GetLeftLine() {
  return !digitalRead(LIGHT_L);
}
int GetCentreLine() {
  return !digitalRead(LIGHT_C);
}
int GetRightLine() {
  return !digitalRead(LIGHT_R);
}

//The check and movement logic
void RunSteering() {
  if (GetLeftLine() && !GetRightLine()) {
    Serial.println("Steering LEFT");
    SetMovement(10,40); //If left is triggered, go left
  } else if (GetRightLine() & !GetLeftLine()) {
    Serial.println("Steering RIGHT");
    SetMovement(40,10); //If right is triggered, go right
  } else if (GetCentreLine()) {
    Serial.println("Steering CENTER");
    SetMovement(40,40); //If the centre sensor is on the line (and neither of the others happened), just keep going
  } else {
    Serial.println("STATIONARY");
    SetMovement(0,0); //If anything else (nothing, or some weird unexpected combo), don't do anything
  }
}