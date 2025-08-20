// Arduino pin numbers
const int SW_pin = 8; // digital pin connected to switch output
const int J1_X = A0; // analog pin connected to X output
const int J1_Y = A1; // analog pin connected to Y output

const int SW2 = 9;
const int J2_X = A2;
const int J2_Y = A3;
const int LED = 12;

// JOY STICK CONSTAINTS
const int DOWN  = 250;   // X - Min 
const int TOP   = 750;   // X - Max
const int LEFT  = 250;   // Y - Min
const int RIGHT = 750;   // Y - Max

// Vertabrae 1 Range of Motion
int V1_DOWN   = 0;
int V1_TOP    = 180;
int V1_LEFT   = 0;
int V1_RIGHT  = 180;

// Vertabrae 2 Range of Motion
int V2_DOWN   = 0;
int V2_TOP    = 180;
int V2_LEFT   = 0;
int V2_RIGHT  = 180;

struct vert {
  int xMin;    // X MIN
  int xCurr;
  int xMax;  // X MAX
  int yMin;    // Y MIN
  int yCurr;
  int yMax;  // Y MAX
};

vert vert1;
vert vert2;

void setup() {
  pinMode(SW_pin, INPUT_PULLUP); // Use INPUT_PULLUP for the button
  pinMode(SW2, INPUT_PULLUP);
  pinMode(LED, OUTPUT);
  Serial.begin(9600); // Initialize serial communication
  digitalWrite(LED, HIGH);
  
  // Vert 1
  vert1.xMin    = V1_DOWN;
  vert1.xCurr   = 90;
  vert1.xMax    = V1_TOP;
  vert1.yMin    = V1_LEFT;
  vert1.yCurr   = 90;
  vert1.yMax    = V1_RIGHT;
  
  // Vert 2
  vert2.xMin    = V1_DOWN;
  vert2.xCurr   = 90;
  vert2.xMax    = V1_TOP;
  vert2.yMin    = V1_LEFT;
  vert2.yCurr   = 90;
  vert2.yMax    = V1_RIGHT;
}

void loop() {
  readJoystick1(J1_X, J1_Y);
  readJoystick2(J2_X, J2_Y);
  delay(100); // Small delay for stable readings
}

void readJoystick1(int xVal, int yVal) {
  if(analogRead(J1_X) < DOWN) {
    Serial.println("Joystick 1 - DOWN");
    vert1.xCurr--;
    checkVertLimits(vert1);
    Serial.println(vert1.xCurr);
  }

  if(analogRead(J1_X) > TOP) {
    Serial.println("Joystick 1 - TOP");
    vert1.xCurr++;
    checkVertLimits(vert1);
    Serial.println(vert1.xCurr);
  }

  if(analogRead(J1_Y) < LEFT) {
    Serial.println("Joystick 1 - LEFT");
    vert1.yCurr--;
    checkVertLimits(vert1);
    Serial.println(vert1.yCurr);
  }

  if(analogRead(J1_Y) > RIGHT) {
    Serial.println("Joystick 1 - RIGHT");
    vert1.yCurr++;
    checkVertLimits(vert1);
    Serial.println(vert1.yCurr);
  }
}

void readJoystick2(int xVal, int yVal) {
  if(analogRead(J2_X) < DOWN) {
    Serial.println("Joystick 2 - DOWN");
    vert2.xCurr--;
    checkVertLimits(vert2);
    Serial.println(vert2.xCurr);
  }

  if(analogRead(J2_X) > TOP) {
    Serial.println("Joystick 2 - TOP");
  }

  if(analogRead(J2_Y) < LEFT) {
    Serial.println("Joystick 2 - LEFT");
  }

  if(analogRead(J2_Y) > RIGHT) {
    Serial.println("Joystick 2 - RIGHT");
  }
}

void checkVertLimits(vert vert){
  // Make sure we stay within range of motion
  if(vert.xCurr < vert1.xMin) {
    vert1.xCurr = vert1.xMin;
  }

  if(vert.xCurr > vert1.xMax) {
    vert1.xCurr = vert1.xMax;
  }

  if(vert.yCurr < vert1.yMin) {
    vert1.yCurr = vert1.yMin;
  }

  if(vert.yCurr > vert1.yMax) {
    vert1.yCurr = vert1.yMax;
  }
}


  // Serial.print("Switch: ");
  // Serial.print(digitalRead(SW_pin)); // Read the button state (LOW when pressed)
  // Serial.print(" | ");
  // Serial.print("X-axis: ");
  // Serial.print(analogRead(X_pin));   // Read the X-axis analog value
  // Serial.print(" | ");
  // Serial.print("Y-axis: ");
  // Serial.print(analogRead(Y_pin));   // Read the Y-axis analog value
  // Serial.println(" | ");