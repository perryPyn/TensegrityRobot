#ifndef CONSOLE_H
#define CONSOLE_H

#include <INST.h>
#include <HardwareSerial.h>

extern float alpha;
extern bool areServoSetup;

void getConsole(s16 position[4]);

#endif