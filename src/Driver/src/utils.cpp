#include "utils.h"

void computePosition(float alpha, s16 position[4]) {
  /*
   * α ∈ [0,45] (deg)
   * returns the position of the three servo
   */

  alpha *= PI / 180;

  float barrelRadius = 1;
  float wireLength = 11;

  float epsilon = 0;
  float plateRadius = 5;
  float plateHeight = 10;
  float plateRadiusE = plateRadius - epsilon;

  float b = plateHeight - plateRadiusE * sin(alpha);
  float d = plateRadiusE * (1 - cos(alpha));
  float e = plateHeight + plateRadius * sin(alpha);

  float wireLength1 = sqrt(pow(b, 2) + pow(d, 2));
  float wireLength3 = sqrt(pow(e, 2) + pow(d, 2));

  position[0] =
      ((wireLength - wireLength1) * MAX_INCREMENT) / (2 * PI * barrelRadius);
  position[1] =
      ((wireLength - wireLength1) * MAX_INCREMENT) / (2 * PI * barrelRadius);
  position[2] =
      ((wireLength - wireLength3) * MAX_INCREMENT) / (2 * PI * barrelRadius);
  position[3] =
      ((wireLength - wireLength3) * MAX_INCREMENT) / (2 * PI * barrelRadius);

  Serial.print(position[0]);
  Serial.print(" | ");
  Serial.print(position[1]);
  Serial.print(" | ");
  Serial.print(position[2]);
  Serial.print(" | ");
  Serial.print(position[3]);
  Serial.println(" | ");
}