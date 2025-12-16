#include <Arduino.h>
#include <Servo.h>

// Configurable servo pins (set to -1 if not used)
const int SERVO_COUNT = 6;
const int servoPins[SERVO_COUNT] = {12, 11, 10, 9, 8, 7};

Servo servos[SERVO_COUNT];
int currentPos[SERVO_COUNT];

const int MIN_POS = 0;
const int MAX_POS = 180;

bool inSelection = true;
int selectedServo = -1; // 0-based index

void printSelectionPrompt() {
  Serial.print("Select servo (1-");
  Serial.print(SERVO_COUNT);
  Serial.print(") or type 'help': ");
}

void printControlPrompt() {
  Serial.print("Servo ");
  Serial.print(selectedServo + 1);
  Serial.print(" > Enter angle (0-180), 'pos', 'help' or 'q' to choose another servo: ");
}

void setup() {
  pinMode(13, OUTPUT);
  Serial.begin(9600);
  delay(100);

  for (int i = 0; i < SERVO_COUNT; ++i) {
    if (servoPins[i] >= 0) {
      servos[i].attach(servoPins[i]);
      currentPos[i] = 90; // default
      servos[i].write(currentPos[i]);
    } else {
      currentPos[i] = -1; // indicates unattached
    }
  }

  Serial.println("--- Multi-Servo Control Ready ---");
  Serial.println("Commands:");
  Serial.println("  select servo: type the servo number (1-6)");
  Serial.println("  In control: enter an angle (0-180) to move the selected servo");
  Serial.println("  Press 'q' in control mode to return and choose another servo");
  Serial.println("  'pos' shows current servo position, 'help' shows this help");
  printSelectionPrompt();
}

void loop() {
  if (!Serial.available()) return;

  String line = Serial.readStringUntil('\n');
  line.trim();
  if (line.length() == 0) {
    if (inSelection) printSelectionPrompt();
    else printControlPrompt();
    return;
  }

  // allow a few helpful shortcuts
  if (line.equalsIgnoreCase("help") || line.equalsIgnoreCase("?")) {
    if (inSelection) {
      Serial.println("Select a servo by typing its number (1-6). Example: 2");
      Serial.println("After selection you can type angles to move it or 'q' to go back");
      printSelectionPrompt();
    } else {
      Serial.println("Control mode commands:");
      Serial.println("  <angle>   - Move the selected servo to angle 0-180");
      Serial.println("  pos       - Show current position of selected servo");
      Serial.println("  q         - Return to servo selection");
      printControlPrompt();
    }
    return;
  }

  // If currently choosing a servo
  if (inSelection) {
    // try to parse number (servo index)
    char buf[line.length() + 1];
    line.toCharArray(buf, sizeof(buf));
    char *endptr;
    long val = strtol(buf, &endptr, 10);
    if (endptr != buf) {
      if (val >= 1 && val <= SERVO_COUNT) {
        selectedServo = (int)val - 1;
        inSelection = false;
        Serial.print("Selected servo ");
        Serial.println(val);
        // check if attached
        if (servoPins[selectedServo] < 0) {
          Serial.println("Warning: this servo has no assigned pin (not attached).");
        }
        printControlPrompt();
        return;
      }
    }

    Serial.println("Invalid selection. Type a number between 1 and " + String(SERVO_COUNT) + ".");
    printSelectionPrompt();
    return;
  }

  // We are in control mode for a selected servo
  if (line.equalsIgnoreCase("q")) {
    // exit to selection mode
    inSelection = true;
    selectedServo = -1;
    Serial.println("Exiting control mode. Choose another servo.");
    printSelectionPrompt();
    return;
  }

  if (line.equalsIgnoreCase("pos")) {
    if (currentPos[selectedServo] >= 0) {
      Serial.print("Current position of servo ");
      Serial.print(selectedServo + 1);
      Serial.print(": ");
      Serial.println(currentPos[selectedServo]);
    } else {
      Serial.println("Servo not attached / no position available.");
    }
    printControlPrompt();
    return;
  }

  // parse angle
  {
    char buf[line.length() + 1];
    line.toCharArray(buf, sizeof(buf));
    char *endptr;
    long val = strtol(buf, &endptr, 10);
    if (endptr == buf) {
      Serial.println("Invalid input. Type an angle (0-180), 'pos', 'help' or 'q'.");
      printControlPrompt();
      return;
    }

    if (val < MIN_POS) val = MIN_POS;
    if (val > MAX_POS) val = MAX_POS;

    if (servoPins[selectedServo] < 0) {
      Serial.println("Cannot move servo: no pin assigned to this servo.");
      printControlPrompt();
      return;
    }

    // move servo
    digitalWrite(13, HIGH);
    servos[selectedServo].write((int)val);
    delay(20);
    digitalWrite(13, LOW);

    currentPos[selectedServo] = (int)val;
    Serial.print("Moved servo ");
    Serial.print(selectedServo + 1);
    Serial.print(" to: ");
    Serial.println(currentPos[selectedServo]);
    printControlPrompt();
  }
}
