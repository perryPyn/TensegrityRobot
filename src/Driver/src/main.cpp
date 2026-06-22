#include "main.h"
#include "console.h"
#include "servo.h"
#include "utils.h"

float alpha = 0;
s16 offset[4] = {0, 0, 0, 0};
s16 position[4] = {0, 0, 0, 0};

void setup() {
  init();
  initSerial();

  // enableMultiLoop(1, 3 * 4096);
  // enableMultiLoop(2, 3 * 4096);
  // enableMultiLoop(3, 3 * 4096);
  // enableMultiLoop(4, 3 * 4096);

  initServoManual(offset);
}

void loop() {
  getConsole(position);
  computePosition(alpha, position);

  setPositions(position, offset);

  getLoad(1);

  delay(2000);
}

int main(void) {

  setup();

  while (1) {
    loop();
  }

  return 0;
}