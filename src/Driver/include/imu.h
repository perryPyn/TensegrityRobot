#ifndef IMU_H
#define IMU_H

#include <Arduino.h>
#include <SparkFun_MMA8452Q.h>
#include <Wire.h>

void initIMU();
void readIMU(float &pitch, float &roll);

#endif
#define IMU_H