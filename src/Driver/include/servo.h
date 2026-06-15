#ifndef SERVO_H
#define SERVO_H

#include <SCServo.h>

void initServo(void);
void setID(int targetID);
void simpleMove(int ID);
void ping(int ID);
void getPosition(int ID);
void setPosition(int ID, s16 Position);
void setPositions(s16 Position[3]);

#endif