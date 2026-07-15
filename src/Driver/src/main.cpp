#include "main.h"
#include "console.h"
#include "imu.h"
#include "pid.h"
#include "servo.h"
#include "utils.h"
#include <Arduino.h>
#include <HardwareSerial.h>

const float Te = 0.02f;
float targetAlpha = 0, targetBeta = 0;
s16 offset[4] = {500, 700, 800, 2900};
s16 position[4] = {0, 0, 0, 0};
pid pidAlpha;
pid pidBeta;

unsigned long lastLoopTime = 0;

// const int N = 20;
// s16 a[N], b[N];
// int i = 0;

void setup() {
  float kp = 0.048, ki = 0.140f, kd = 0.0168f, limit = 30.0f;

  init();
  initSerial();
  initIMU();

  initPID(&pidAlpha, kp, ki, kd, limit);
  initPID(&pidBeta, kp, ki, kd, limit);

  Serial.println("targetAlpha,rawAlpha,cmdAlpha,targetBeta,rawBeta,cmdBeta");

  calibrationServo(offset);

  // demoAlphaBeta(N, a, b);
}

void loop() {
  unsigned long currentTime = millis();

  // Set loop frequency to 50 Hz
  if (currentTime - lastLoopTime >= LOOP_PERIOD) {
    handleAngleCommand(&targetAlpha, &targetBeta);

    // targetAlpha = a[i];
    // targetBeta = b[i];

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

    // i = (i + 1) % N;
  }
}

int main() {

  setup();

  while (1) {
    loop();
  }

  return 0;
}
