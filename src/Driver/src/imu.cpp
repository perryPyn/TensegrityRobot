#include "imu.h"

MMA8452Q accel;

void initIMU() {
  /*
   *SDA=20, SCL=21, SA0=GND
   */

  Wire.begin();
  if (accel.begin(Wire, 0x1C) == false) {
    Serial.println("Capteur introuvable");
    while (1) {
    }
  }
  Serial.println("Capteur détecté avec succès !");
}

void readIMU(float &pitch, float &roll) {
  if (accel.available()) {

    float x = accel.getCalculatedX();
    float y = accel.getCalculatedY();
    float z = accel.getCalculatedZ();

    float roll = atan2(y, z) * 180.0 / PI;

    float pitch = atan2(-x, sqrt(y * y + z * z)) * 180.0 / PI;

    Serial.print("Accélération (g) -> X: ");
    Serial.print(x, 2);
    Serial.print("  Y: ");
    Serial.print(y, 2);
    Serial.print("  Z: ");
    Serial.print(z, 2);

    Serial.print("  |  Inclinaison (deg) -> Roulis: ");
    Serial.print(roll, 1);
    Serial.print("  Tangage: ");
    Serial.println(pitch, 1);
  }
}