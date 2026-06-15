#ifndef SERVO_H
#define SERVO_H

#include <SCServo.h>

void initSerial(void);
void hardReset(void);
void setID(int targetID);
void setMode(int targetID, int mode);
void simpleMove(int ID);
void ping(int ID);
void getPosition(int ID);
void setPosition(int ID, s16 Position);
void setPositions(s16 Position[3]);

void testMode2(void);

#endif