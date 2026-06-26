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

s16 a[20];
s16 b[20];
int i = 0;

void setup() {
  init();
  initSerial();

  initServoManual(offset);
  demoAlphaBeta(20, a, b);
}

void loop() {
  computePosition(a[i], b[i], position);
  setPositions(position, offset);
  printPositions(position);

  i = (i+1)%20;
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