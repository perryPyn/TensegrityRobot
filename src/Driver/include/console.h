#ifndef CONSOLE_H
#define CONSOLE_H

#include <INST.h>
#include <HardwareSerial.h>

extern s16 position[4];
extern float alpha;
extern bool areServoSetup;

void getConsole(void);

#endif