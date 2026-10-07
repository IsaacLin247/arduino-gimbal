/*
  Checks whether the SDA (A4) and SCL (A5) wires actually reach a powered MPU6050 module.
  MPU6050 breakout boards have pull-up resistors on SDA and SCL, so when the module
  is powered and the wires are connected, both lines sit near 3.3V or 5V.
  The Nano's own internal pull-ups are turned off here, so a low reading means
  the wire or the module power is the problem.
*/

void setup() {
  Serial.begin(115200);
  pinMode(A4, INPUT);  // no internal pull-up
  pinMode(A5, INPUT);
}

void report(const __FlashStringHelper *name, int pin) {
  float volts = analogRead(pin) * 5.0 / 1023.0;
  Serial.print(name);
  Serial.print(volts, 2);
  Serial.print(F(" V  "));
  if (volts > 2.5) Serial.println(F("OK, wire connected and module powered"));
  else Serial.println(F("LOW, wire not connected or module has no power"));
}

void loop() {
  report(F("SDA (A4): "), A4);
  report(F("SCL (A5): "), A5);
  Serial.println();
  delay(1000);
}
