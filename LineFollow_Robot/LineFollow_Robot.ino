const int TEST_DELAY = 50;
const int LOOP_DELAY = 1000;

/* 
Notes for self later:
  - Had to choose between one big .ino, multiple .ino's, and the .h/.cpp stuff
  - Had to make sure I wasn't going to fry the board with 5V in a 3.3V spot
  - Decided to add to git partway through (here)
*/

void setup() {
  /*
  setup() code logic:
    - activate the board & serial communication
    - make sure it's talking to the ground board - TO DO
    - test each of the systems (IMU, baro/temp, GPS, Telemetry)
    - send ready msg
  */

  //Setup Serial communication
  Serial.begin(9600);
  int serialCount = 1;
  while (!Serial) {
    delay(TEST_DELAY);
    serialCount++;
  }
  Serial.println("Board OKAY");
  Serial.print("Tried ");
  Serial.print(serialCount);
  Serial.println(" times");

  SetupWheels();
  //SetupBoardSensors();
  SetupRobotSensors();
}

void loop() {
  /*
  loop() code logic:
    - If manual mode
      - If no command received
        - Do current command
      - When command received
        - Execute new command
    - If auto-follow mode
      - If mode-switch received, switch
      - If line tracked by middle, go forward
      - If line tracked by side, turn until middle
      - If line not tracked, start search
        -If search complete and no line found, wait for 
  */

  delay(LOOP_DELAY);

  //SensorTestCycle();
  Serial.print("LeftLight:");
  Serial.print(GetLeftLine());
  Serial.print(",");
  Serial.print("CentreLight:");
  Serial.print(GetCentreLine());
  Serial.print(",");
  Serial.print("RightLight:");
  Serial.print(GetRightLine());
  Serial.println();
  
  RunSteering();
}