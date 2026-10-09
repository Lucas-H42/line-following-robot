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
  //If it doesn't detect anything, don't do anything
  if (!GetCentreSensor() && !GetLeftSensor() && !GetRightSensor()) { 
    SetMovement(0,0); 
  } else if (GetLeftSensor() && !GetRightSensor()) {
    SetMovement(0,1); //If left is triggered, go left
  } else if (GetRightSensor() & !GetLeftSensor()) {
    SetMovement(1,0); //If right is triggered, go right
  } else if (GetCentreSensor()) { 
    SetMovement(1,1); //If the centre sensor is on the line (and neither of the others happened), just keep going
  }
}