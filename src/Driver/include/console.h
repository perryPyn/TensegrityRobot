#ifndef CONSOLE_H
#define CONSOLE_H

#include <INST.h>
#include <HardwareSerial.h>

extern float alpha,beta;
extern bool areServoSetup;
extern s16 p5;

void getConsole(s16 position[4]);
void handleServoCommand(s16 position[4]);
void handleAngleCommand(void);

#endif