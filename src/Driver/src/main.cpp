#include "main.h"
#include "Arduino.h"
#include "HardwareSerial.h"
#include "pid.h"

const float Te = 0.02f;
float targetAlpha = 0, targetBeta = 0;
s16 offset[4] = {0, 0, 0, 0};
s16 position[4] = {0, 0, 0, 0};
pid pidAlpha;
pid pidBeta;

unsigned long lastLoopTime = 0;

void setup() {
  init();
  initSerial();
  initIMU();

  initPID(&pidAlpha, 1.5f, 0.1f, 0.05f, 15.0f);
  initPID(&pidBeta, 1.5f, 0.1f, 0.05f, 15.0f);

  Serial.println("targetAlpha,rawAlpha,cmdAlpha,targetBeta,rawBeta,cmdBeta");
}

void loop() {
  unsigned long currentTime = millis();

  if (currentTime - lastLoopTime >= LOOP_PERIOD) {
    // handleAngleCommand(&targetAlpha, &targetBeta);

    float rawAlpha = 0, rawBeta = 0;
    readIMU(&rawAlpha, &rawBeta);

    float cmdAlpha = computePID(&pidAlpha, targetAlpha, rawAlpha, Te);
    float cmdBeta = computePID(&pidBeta, targetBeta, rawBeta, Te);

    computePosition(cmdAlpha, cmdBeta, position);
    setPositions(position, offset);
    // printPositions(position);

    Serial.print(targetAlpha);
    Serial.print(",");
    Serial.print(rawAlpha);
    Serial.print(",");
    Serial.print(cmdAlpha);
    Serial.print(",");
    Serial.print(targetBeta);
    Serial.print(",");
    Serial.print(rawBeta);
    Serial.print(",");
    Serial.println(cmdBeta);
  }
}

int main() {

  setup();

  while (1) {
    loop();
  }

  return 0;
}
