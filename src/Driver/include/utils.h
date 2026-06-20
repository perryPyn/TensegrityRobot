#ifndef UTILS_H
#define UTILS_H

#include <Arduino.h>
#include <INST.h>

#define MAX_INCREMENT 4096

void setup(void);
void loop(void);

void computePosition(float alpha, s16 position[4]);

void demoAlpha(void);

#endif