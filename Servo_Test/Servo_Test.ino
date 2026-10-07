/*
  Servo test for the gimbal (no IMU needed).
  Sends all three servos to 90, 45, 90, 135 degrees, holding each for 3 seconds.
    180-degree (positional) servos: move to each angle and STOP and hold there.
    360-degree (continuous rotation) servos: keep SPINNING at 45 and 135, and stop (or creep) at 90.
*/

#include <Servo.h>

Servo servo0;  // Yaw   D10
Servo servo1;  // Pitch D9
Servo servo2;  // Roll  D8

const int angles[] = {90, 45, 90, 135};

void setup() {
  Serial.begin(115200);
  servo0.attach(10);
  servo1.attach(9);
  servo2.attach(8);
}

void loop() {
  for (int i = 0; i < 4; i++) {
    Serial.print(F("All servos -> "));
    Serial.print(angles[i]);
    Serial.println(F(" deg (should move there and hold still)"));
    servo0.write(angles[i]);
    servo1.write(angles[i]);
    servo2.write(angles[i]);
    delay(3000);
  }
}
