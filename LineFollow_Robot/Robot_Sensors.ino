#define LIGHT_L PA8
#define LIGHT_C PB1
#define LIGHT_R PB0
#define SONIC_TRIG PA6
#define SONIC_ECHO PA7

int MAX_SEARCH = 50;
bool hasSearched = false;

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
    SetMovement(0,1); //If left is triggered, go left
  } else if (GetRightLine() & !GetLeftLine()) {
    SetMovement(1,0); //If right is triggered, go right
  } else if (GetCentreLine()) { 
    SetMovement(1,1); //If the centre sensor is on the line (and neither of the others happened), just keep going
  } else if (!hasSearched) {
    LineSearch(); //If anything else (nothing, or some weird unexpected combo), look for a new line
  } else {
    SetMovement(0,0);
  }
}

void LineSearch() {
  int search = 0;
  SetMovement(1,-1);
  while (search < MAX_SEARCH && !GetLeftLine() && !GetCentreLine() && !GetRightLine()) {
    delay(50);
    Serial.print("Search count: ");
    Serial.println(search);
    search++;
  }
  SetMovement(0,0);
  while (!GetCentreLine()) {
    if (GetLeftLine()) {
      SetMovement(-1,1);
    } else if (GetRightLine()) {
      SetMovement(1,-1);
    }
    delay(10);
    SetMovement(0,0);
  }
  hasSearched = true;
}