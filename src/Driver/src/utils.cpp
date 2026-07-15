#include "utils.h"

const float R = 45, r = 13.5;
const int H = 100;

void computePosition(float alpha, float beta, s16 position[4]) {
  alpha *= PI / 180;
  beta *= PI / 180;

  float l1 = sqrt(pow(R * sin(alpha) + H, 2) + pow(R * cos(alpha) - R, 2));

  float l2 =
      sqrt(pow(-R + R * cos(beta), 2) + pow(R * sin(beta) * cos(alpha) + H, 2) +
           pow(R * sin(beta) * sin(alpha), 2));

  float l3 = sqrt(pow(-R * cos(alpha) + R, 2) + pow(H - R * sin(alpha), 2));

  float l4 =
      sqrt(pow(R - R * cos(beta), 2) + pow(H - R * sin(beta) * cos(alpha), 2) +
           pow(R * sin(beta) * sin(alpha), 2));

  position[0] = ((H - l1) * MAX_INCREMENT) / (2 * PI * r);
  position[1] = ((H - l2) * MAX_INCREMENT) / (2 * PI * r);
  position[2] = ((H - l3) * MAX_INCREMENT) / (2 * PI * r);
  position[3] = ((H - l4) * MAX_INCREMENT) / (2 * PI * r);
}

void demoAlphaBeta(int N, s16 a[], s16 b[]) {
  for (int i = 0; i < 20; i++) {
    a[i] = 25 * sin(2 * PI * i / N);
    b[i] = 25 * cos(2 * PI * i / N);
  }
}
