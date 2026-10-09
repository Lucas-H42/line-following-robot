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
  //If it doesn't detect anything, don't do anything
  if (!GetCentreLine() && !GetLeftLine() && !GetRightLine()) { 
    SetMovement(0,0); 
  } else if (GetLeftLine() && !GetRightLine()) {
    SetMovement(0,1); //If left is triggered, go left
  } else if (GetRightLine() & !GetLeftLine()) {
    SetMovement(1,0); //If right is triggered, go right
  } else if (GetCentreLine()) { 
    SetMovement(1,1); //If the centre sensor is on the line (and neither of the others happened), just keep going
  }
}