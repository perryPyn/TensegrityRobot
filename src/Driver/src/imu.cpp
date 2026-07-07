#include "imu.h"

MMA8452Q accel;

static float filteredAlpha = 0, filteredBeta = 0;

void initIMU() {
  Wire.begin();
  if (accel.begin(Wire, 0x1C) == false) {
    Serial.println("Capteur introuvable");
    while (1) {
    }
  }
  // Serial.println("Capteur détecté avec succès !");
}

void readIMU(float *pitch, float *roll) {
  if (accel.available()) {
    accel.read();

    float ax = accel.getCalculatedX();
    float ay = accel.getCalculatedY();
    float az = accel.getCalculatedZ();

    float rawAlpha = atan2(ay, az) * 180.0f / PI;
    float rawBeta = atan2(-ax, sqrt(ay * ay + az * az)) * 180.0f / PI;

    filteredAlpha = (GAMMA * rawAlpha) + ((1.0f - GAMMA) * filteredAlpha);
    filteredBeta = (GAMMA * rawBeta) + ((1.0f - GAMMA) * filteredBeta);
  }

  *pitch = filteredAlpha;
  *roll = filteredBeta;
}
