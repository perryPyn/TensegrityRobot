#include "main.h"
#include "Arduino.h"
#include "console.h"
#include "servo.h"
#include "utils.h"

float alpha = 0, beta = 0;
s16 offset[4] = {1370, 740, 60, 1340};
s16 position[4] = {300, 300, -300, -300};

void setup() {
  init();
  initSerial();
}

void loop() {
  // handleAngleCommand();
  // computePosition(alpha, beta, position);

  handleServoCommand(position);
  setPositions(position, offset);
  printPositions(position);

  delay(500);
}

int main() {

  setup();

  while (1) {
    loop();
  }

  return 0;
}