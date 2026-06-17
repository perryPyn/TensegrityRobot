#include "utils.h"
#include "console.h"
#include "servo.h"

float alpha = 0;
s16 position[3] = {0, 0, 0};

void setup() {
  init();
  initSerial();
}

void loop() {
  getConsole();
  computePosition(alpha, position);

  setPositions(position);
  delay(300);
}

void computePosition(float alpha, s16 position[3]) {
  /*
   * α ∈ [0,90] (deg)
   * returns the position of the three servo
   */

  alpha *= PI / 180;

  float barrelRadius = 1;
  float wireLength = 1;

  float epsilon = 0.01;
  float plateRadius = 1;
  float plateHeight = 1;
  float plateRadiusE = plateRadius - epsilon;

  float b = plateHeight - plateRadiusE * sin(alpha);
  float d = plateRadiusE * (1 - cos(alpha));
  float e = plateHeight + plateRadius * sin(alpha);

  float wireLength1 = sqrt(pow(b, 2) - pow(d, 2));
  float wireLength3 = sqrt(pow(e, 2) + pow(d, 2));

  position[0] =
      ((wireLength - wireLength1) * MAX_INCREMENT) / (2 * PI * barrelRadius);
  position[1] =
      ((wireLength - wireLength1) * MAX_INCREMENT) / (2 * PI * barrelRadius);
  position[2] =
      ((wireLength - wireLength3) * MAX_INCREMENT) / (2 * PI * barrelRadius);

  Serial.print("p1 = ");
  Serial.print(position[0]);
  Serial.print(" | p2 = ");
  Serial.print(position[1]);
  Serial.print(" | p3 = ");
  Serial.println(position[2]);
}