#include "main.h"
#include "console.h"
#include "imu.h"
#include "pid.h"
#include "servo.h"
#include <Arduino.h>
#include <HardwareSerial.h>

const float Te = 0.02f;
float targetAlpha = 0, targetBeta = 0;
s16 offset[4] = {300, 500, 400, 2680};
s16 position[4] = {0, 0, 0, 0};
pid pidAlpha;
pid pidBeta;

unsigned long lastLoopTime = 0;

void setup() {
  float kp = 0.049f, ki = 0.140f, kd = 0.0168f, limit = 15.0f;

  init();
  initSerial();
  initIMU();

  initPID(&pidAlpha, kp, ki, kd, limit);
  initPID(&pidBeta, kp, ki, kd, limit);

  Serial.println("targetAlpha,rawAlpha,cmdAlpha,targetBeta,rawBeta,cmdBeta");

  // calibrationServo(offset);
}

void loop() {
  unsigned long currentTime = millis();

  // Set loop frequency to 50 Hz
  if (currentTime - lastLoopTime >= LOOP_PERIOD) {
    handleAngleCommand(&targetAlpha, &targetBeta);

    // Get raw angles mesurement
    float rawAlpha = 0, rawBeta = 0;
    readIMU(&rawBeta, &rawAlpha);
    rawAlpha *= -1;
    rawBeta *= -1;

    // Correct target angle with mesurement
    float cmdAlpha =
        targetAlpha + computePID(&pidAlpha, targetAlpha, rawAlpha, Te);
    float cmdBeta = targetBeta + computePID(&pidBeta, targetBeta, rawBeta, Te);

    // Apply command
    computePosition(cmdAlpha, cmdBeta, position);
    setPositions(position, offset);
    // printPositions(position);

    // Data for serial plotter
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
