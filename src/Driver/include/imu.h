#ifndef IMU_H
#define IMU_H

#include <Arduino.h>
#include <SparkFun_MMA8452Q.h>
#include <Wire.h>

#define GAMMA 0.10

void initIMU();
void readIMU(float *pitch, float *roll);

#endif
