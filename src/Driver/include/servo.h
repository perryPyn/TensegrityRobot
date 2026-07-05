#ifndef SERVO_H
#define SERVO_H

#include "console.h"
#include "utils.h"
#include <Arduino.h>
#include <HardwareSerial.h>
#include <SCServo.h>

void initSerial(void);
void initServo(void);
void calibrationServo(s16 offset[4]);
void hardReset(void);
void setID(u8 ID);
void setTargetID(u8 ID, u8 targetID);
void setMode(u8 ID, int mode);
void enableMultiLoop(u8 ID, u16 minAngle, u16 maxAngle);
// void enableTorque(u8 ID, u8 state);
void ping(u8 ID);
s16 getPosition(u8 ID);
s16 getLoad(u8 ID);
void setPosition(u8 ID, s16 Position);
void setPositionsRaw(s16 Position[4]);
void setPositions(s16 Position[4], s16 Offset[4]);
void printPositions(s16 position[4]);

#endif