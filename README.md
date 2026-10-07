# Arduino Gimbal

Self-stabilizing 3-axis servo gimbal for an Arduino Nano with an MPU6050 IMU.
Based on the HowToMechatronics DIY Arduino Gimbal project and the MPU6050_DMP6 example from i2cdevlib.

## What's in here

- `Arduino_Gimbal/`: main gimbal sketch
- `libraries/`: the libraries the sketch needs (MPU6050 1.4.5 with I2Cdev, Servo 1.3.0)
- `I2C_Scanner/`: checks that the Nano can see the MPU6050
- `IMU_Wire_Test/`: checks that the SDA and SCL wires reach a powered MPU6050
- `Servo_Test/`: checks the servos hold position (180 degree servos, not 360 degree)

## Wiring

| Part | Pin |
|---|---|
| MPU6050 VCC | 5V |
| MPU6050 GND | GND |
| MPU6050 SDA | A4 |
| MPU6050 SCL | A5 |
| MPU6050 INT | D2 |
| Yaw servo signal | D10 |
| Pitch servo signal | D9 |
| Roll servo signal | D8 |

Servos run from a 5V buck converter. Its GND must connect to the Nano GND.

## Setup (Arduino IDE)

1. Clone or download this repo.
2. In the Arduino IDE, open File > Preferences and set Sketchbook location to the cloned `arduino-gimbal` folder, then restart the IDE.
   The IDE then finds the bundled libraries automatically.
   (Or copy the two folders in `libraries/` into your existing `Documents/Arduino/libraries` folder instead.)
3. Open `Arduino_Gimbal/Arduino_Gimbal.ino`.
4. Tools > Board > Arduino Nano. Tools > Port > your Nano's port.
5. Upload. If it stalls, set Tools > Processor > ATmega328P (Old Bootloader) and upload again.
6. Serial Monitor at 115200 baud shows the IMU yaw, pitch and roll.

Close the Serial Monitor before uploading, or the upload fails with "port busy".

## Settings

At the top of `Arduino_Gimbal.ino`:

```cpp
const bool STABILIZE_YAW = true;
const bool STABILIZE_PITCH = false;
const bool STABILIZE_ROLL = false;
```

Axes set to `false` hold at 90 degrees. Keep the gimbal still and level for the first 5 to 10 seconds after power on while it calibrates.
