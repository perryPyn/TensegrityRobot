#include "main.h"
#include "console.h"
#include "servo.h"
#include "utils.h"

float alpha = 0, beta = 0;
s16 offset[4] = {0, 0, 0, 0};
s16 position[4] = {0, 0, 0, 0};

// void setup() {
//   init();
//   initSerial();

//   initServoManual(offset);
// }

// void loop() {
//   handleAngleCommand();
//   computePosition(alpha, beta, position);

//   setPositions(position, offset);
//   printPositions(position);

//   delay(500);
// }

/* --------------------------------------------------- */
/* --------------- Code part for demo ---------------- */
/* --------------------------------------------------- */

int i = 0;
const int N = 20;
s16 a[N];
s16 b[N];

void setup() {
  init();
  initSerial();
  initServo(); // Should only be run once

  calibrationServo(offset);
  demoAlphaBeta(N, a, b);
}

void loop() {
  computePosition(a[i], b[i], position);
  setPositions(position, offset);
  printPositions(position);

  i = (i+1)%N;
  delay(180);
}

/* --------------------------------------------------- */

int main(void) {

  setup();

  while (1) {
    loop();
  }

  return 0;
}