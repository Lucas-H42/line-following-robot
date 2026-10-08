#define L_FORWARD PB4
#define L_BACK PB5
#define R_FORWARD PC0
#define R_BACK PC1
//NOTE: R WHEEL BLUE WIRE NEEDS RE-SOLDERING

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

void SetMovement(int lWheel, int rWheel) {
  if (lWheel > 0) 
  {
    digitalWrite(L_BACK, LOW);
    digitalWrite(L_FORWARD, HIGH);
  } 
  else if (lWheel < 0) 
  {
    digitalWrite(L_FORWARD, LOW);
    digitalWrite(L_BACK, HIGH);
  } 
  else if (lWheel == 0) 
  {
    digitalWrite(L_FORWARD, LOW);
    digitalWrite(L_BACK, LOW);
  }

  if (rWheel > 0) 
  {
    digitalWrite(R_BACK, LOW);
    digitalWrite(R_FORWARD, HIGH);
  } 
  else if (rWheel < 0) 
  {
    digitalWrite(R_FORWARD, LOW);
    digitalWrite(R_BACK, HIGH);
  } 
  else if (rWheel == 0) 
  {
    digitalWrite(R_FORWARD, LOW);
    digitalWrite(R_BACK, LOW);
  }
}