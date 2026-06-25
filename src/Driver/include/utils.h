#ifndef UTILS_H
#define UTILS_H

#include <Arduino.h>
#include <INST.h>

#define MAX_INCREMENT 4095

void computeSimplePosition(float alpha, s16 position[4]);
void computePosition(float alpha, float beta, s16 position[4]);

void demoAlphaBeta(int N, s16 a[], s16 b[]);

#endif