#ifndef SERVO_H
#define SERVO_H

#include <USBAPI.h>
#include <Arduino.h>
#include <SCServo.h>

void initSerial(void);
void initServo(s16 offset[4]);
void hardReset(void);
void setID(u8 ID);
void setMode(u8 ID, int mode);
void enableMultiLoop(u8 ID, u16 maxAngle);
void simpleMove(u8 ID);
void ping(u8 ID);
s16 getPosition(u8 ID);
void setPosition(u8 ID, s16 Position);
void setPositions(s16 Position[4]);

#endif