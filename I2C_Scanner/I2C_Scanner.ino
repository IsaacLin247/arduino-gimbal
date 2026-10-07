/*
  I2C scanner for checking the MPU6050 wiring.
  Lists every device found on the I2C bus (SDA = A4, SCL = A5 on the Nano)
  and reads the WHO_AM_I register of anything at the MPU6050 addresses.
*/

#include <Wire.h>

void setup() {
  Serial.begin(115200);
  Wire.begin();
  Wire.setWireTimeout(3000, true);  // don't hang forever if SDA/SCL are shorted or stuck
}

void loop() {
  Serial.println(F("Scanning I2C bus..."));
  int found = 0;
  for (byte addr = 1; addr < 127; addr++) {
    Wire.beginTransmission(addr);
    byte err = Wire.endTransmission();
    if (err == 0) {
      found++;
      Serial.print(F("  Device found at 0x"));
      if (addr < 16) Serial.print('0');
      Serial.print(addr, HEX);
      if (addr == 0x68 || addr == 0x69) {
        // WHO_AM_I register 0x75: 0x68 = MPU6050, 0x70 = MPU6500, 0x71 = MPU9250, 0x98 = MPU6886/clone
        Wire.beginTransmission(addr);
        Wire.write(0x75);
        Wire.endTransmission(false);
        Wire.requestFrom(addr, (byte)1);
        if (Wire.available()) {
          byte who = Wire.read();
          Serial.print(F("  WHO_AM_I = 0x"));
          Serial.print(who, HEX);
          if (who == 0x68) Serial.print(F(" (genuine MPU6050)"));
          else Serial.print(F(" (not a genuine MPU6050, clone or different chip)"));
        }
      }
      Serial.println();
    } else if (err == 5) {
      Serial.println(F("  Bus timeout: SDA/SCL stuck or shorted, check wiring"));
      break;
    }
  }
  if (found == 0) Serial.println(F("  No I2C devices found. Check VCC, GND, SDA->A4, SCL->A5."));
  Serial.println();
  delay(3000);
}
