#include <Servo.h> // Include the Servo library

// Add Servo classes
Servo servo1; // Range of motion 65 - 105
Servo servo2; // Range of motion 65 - 115


void setup() {
  // Attach the servos 
  servo1.attach(12);
  servo2.attach(11);

  // Turn on the relay
  pinMode(9, HIGH);
}

void loop() {
  for (int angle = 65; angle <= 105; angle +=1) {
    servo1.write(angle);
    delay(15);
  }

  for (int angle = 105; angle >= 65; angle -=1){
    servo1.write(angle);
    delay(15);
  }

  for (int angle = 65; angle <= 115; angle +=1) {
    servo2.write(angle);
    delay(15);
  }

  for (int angle = 115; angle >= 65; angle -=1){
    servo2.write(angle);
    delay(15);
  }
}
