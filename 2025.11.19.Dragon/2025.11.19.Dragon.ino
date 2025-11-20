#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

#define SERVO_MIN 150   // pulse for 0°
#define SERVO_MAX 600   // pulse for 180°

int servo1 = 0;   // channel 0
int servo2 = 1;   // channel 1

// Angle limits
int s1_min = 65, s1_max = 105;
int s2_min = 65, s2_max = 115;

int angleToPulse(int angle) {
  return map(angle, 0, 180, SERVO_MIN, SERVO_MAX);
}

void setup() {
  pwm.begin();
  pwm.setPWMFreq(50);
}

// Move servo to angle within its limits
void setServo(int channel, int angle, int minA, int maxA) {
  angle = constrain(angle, minA, maxA);
  pwm.setPWM(channel, 0, angleToPulse(angle));
}

void loop() {
  // Example movement
  setServo(servo1, 105, s1_min, s1_max);  
  setServo(servo2, 115, s2_min, s2_max);

  delay(1000);

  setServo(servo1, 65, s1_min, s1_max);
  setServo(servo2, 65, s2_min, s2_max);

  delay(1000);
}