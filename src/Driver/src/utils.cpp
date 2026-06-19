#include "utils.h"
#include "console.h"
#include "servo.h"

float alpha = 0;
s16 offset[4] = {0, 0, 0, 0};
s16 position[4] = {2302, 2596, 2803, 0};

void setup() {
  init();
  initSerial();

  // enableMultiLoop(1, 3 * 4096);
  // enableMultiLoop(2, 3 * 4096);
  // enableMultiLoop(3, 3 * 4096);
  // enableMultiLoop(4, 3 * 4096);

  initServo(offset);
}

void loop() {
  getConsole();
  computePosition(alpha, position);

  setPositions(position);
  delay(2000);
}

void computePosition(float alpha, s16 position[4]) {
  /*
   * α ∈ [0,45] (deg)
   * returns the position of the three servo
   */

  alpha *= PI / 180;

  float barrelRadius = 1;
  float wireLength = 1;

  float epsilon = 0;
  float plateRadius = 1;
  float plateHeight = 1;
  float plateRadiusE = plateRadius - epsilon;

  float b = plateHeight - plateRadiusE * sin(alpha);
  float d = plateRadiusE * (1 - cos(alpha));
  float e = plateHeight + plateRadius * sin(alpha);

  float wireLength1 = sqrt(pow(b, 2) + pow(d, 2));
  float wireLength3 = sqrt(pow(e, 2) + pow(d, 2));

  position[0] =
      ((wireLength - wireLength1) * MAX_INCREMENT) / (2 * PI * barrelRadius) +
      offset[0];
  position[1] =
      ((wireLength - wireLength1) * MAX_INCREMENT) / (2 * PI * barrelRadius) +
      offset[1];
  position[2] =
      ((wireLength - wireLength3) * MAX_INCREMENT) / (2 * PI * barrelRadius) +
      offset[2];
  position[3] =
      ((wireLength - wireLength3) * MAX_INCREMENT) / (2 * PI * barrelRadius) +
      offset[3];

  Serial.print(position[0]);
  Serial.print(" | ");
  Serial.print(position[1]);
  Serial.print(" | ");
  Serial.print(position[2]);
  Serial.print(" | ");
  Serial.print(position[3]);
  Serial.println(" | ");
}