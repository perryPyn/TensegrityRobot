#ifndef CONSOLE_H
#define CONSOLE_H

#include <HardwareSerial.h>
#include <INST.h>

void handleInitCommand(bool *areServoSetup);
void handleServoCommand(s16 position[4]);
void handleAngleCommand(float *alpha, float *beta);

#endif
