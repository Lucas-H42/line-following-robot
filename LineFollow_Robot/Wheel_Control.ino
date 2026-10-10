#define L_FORWARD PB4
#define L_BACK PB5
#define R_FORWARD PC0
#define R_BACK PC1
#define L_SPEED PC6
#define R_SPEED PC7
//NOTE: R WHEEL BLUE WIRE NEEDS RE-SOLDERING
//ADD wires from pins defined above to ENA and ENB

const int MAX_SPEED = 255;
const float WHEEL_MAX = 100;
const float WHEEL_MIN = -1 * WHEEL_MAX;

void SetupWheels() {
  pinMode(L_FORWARD, OUTPUT);
  pinMode(L_BACK, OUTPUT);
  pinMode(R_FORWARD, OUTPUT);
  pinMode(R_BACK, OUTPUT);

  digitalWrite(L_FORWARD, LOW);
  digitalWrite(L_BACK, LOW);
  digitalWrite(R_FORWARD, LOW);
  digitalWrite(R_BACK, LOW);
}

void SetMovement(int lWheel, int rWheel) { //Values can be -100 to 100
  if (lWheel > 0) {
    digitalWrite(L_BACK, LOW);
    digitalWrite(L_FORWARD, HIGH);
  } else if (lWheel < 0) {
    digitalWrite(L_FORWARD, LOW);
    digitalWrite(L_BACK, HIGH);
  } else if (lWheel == 0) {
    digitalWrite(L_FORWARD, LOW);
    digitalWrite(L_BACK, LOW);
  }
  analogWrite(L_SPEED, abs(constrain(lWheel, WHEEL_MIN, WHEEL_MAX)) * MAX_SPEED/WHEEL_MAX);

  if (rWheel > 0) {
    digitalWrite(R_BACK, LOW);
    digitalWrite(R_FORWARD, HIGH);
  } else if (rWheel < 0) {
    digitalWrite(R_FORWARD, LOW);
    digitalWrite(R_BACK, HIGH);
  } else if (rWheel == 0) {
    digitalWrite(R_FORWARD, LOW);
    digitalWrite(R_BACK, LOW);
  }
  analogWrite(R_SPEED, abs(constrain(rWheel, WHEEL_MIN, WHEEL_MAX)) * MAX_SPEED/WHEEL_MAX);
}