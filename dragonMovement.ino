#include <Servo.h>
Servo servo;
Servo servo2;
int servoPos = 0;
int topMax = 65;
int downMax = 120;


void setup() {
  Serial.begin(9600);
  servo.attach(6);
  servo.attach(9);
}

void loop() {
  // Up and down range = 65 and 120
  // left and right range = 65 and 102
  servo.write(75);
  servo2.write(90);
}
