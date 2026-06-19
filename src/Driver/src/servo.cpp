#include "servo.h"
#include "Arduino.h"
#include "HardwareSerial.h"
#include "console.h"

SMS_STS st;
u16 speed = 1500;
byte acc = 30;

bool areServoSetup = false;

void initSerial() {
  /*
   * Initialization of the communication. TX/RX on the USB port and TX1/RX1 to
   * the linker.
   */

  Serial1.begin(1000000); // To linker
  Serial.begin(115200);   // To laptop

  st.pSerial = &Serial1;
  delay(100);
}

void initServo(s16 offset[4]) {
  while (!areServoSetup) {
    getConsole();
    setPositions(position);\
    delay(200);
  }
  offset[0] = getPosition(1);
  offset[1] = getPosition(2);
  offset[2] = getPosition(3);
  offset[3] = getPosition(4);
}

void hardReset() {
  st.unLockEprom(254);
  st.Reset(254);
  st.LockEprom(254);
}

void setID(u8 ID) {
  /*
   * Change the ID of the connected servo.
   * They should be done one at a time.
   */

  st.unLockEprom(254);
  delay(20);

  st.writeByte(254, SMS_STS_ID, ID);
  delay(100);

  st.LockEprom(ID);
  delay(20);

  ping(ID);
}

void setMode(u8 ID, int mode) {
  /*
   * Change the mode between position (0) and speed (1/2) and stepper (3)
   * control.
   */

  st.unLockEprom(ID);
  delay(20);

  st.writeByte(ID, SMS_STS_MODE, mode);
  delay(100);

  st.LockEprom(ID);
  delay(20);
}

void enableMultiLoop(u8 ID, u16 maxAngle) {
/*
* Changes the maximum rotation angle of the designated servo
*/

  st.unLockEprom(ID);
  delay(20);

  st.writeWord(ID, 9, 0);
  delay(100);

  st.writeWord(ID, 11, 4096 * 2);
  delay(100);

  st.LockEprom(ID);
  delay(20);
}

void simpleMove(u8 ID) {
  st.WritePosEx(4, 0, speed, acc);
  delay(5000);

  st.WritePosEx(4, 8000, speed, acc);
  delay(5000);
}

void ping(u8 ID) {
  int ID_ping = st.Ping(ID);
  if (ID_ping != -1) {
    Serial.print("Servo ID : ");
    Serial.println(ID_ping, DEC);
    delay(100);
  } else {
    Serial.println("Ping servo ID error!");
    delay(2000);
  }
}

s16 getPosition(u8 ID) {
  /*
   * Print the current position of target servo.
   */

  int position = st.ReadPos(ID);
  Serial.print("Position Servo ");
  Serial.print(ID);
  Serial.print(" : ");
  Serial.println(position);

  return position;
}

void setPosition(u8 ID, s16 Position) {
  /*
   * Move the motor to desired position with pre-determined Speed and ACC.
   */

  st.RegWritePosEx(ID, Position, speed, acc);
  st.RegWriteAction();
}

void setPositions(s16 Position[4]) {
  /*
   * Move the motors to desired positions with pre-determined Speed and ACC.
   */

  u8 ID[4] = {1, 2, 3, 4};
  u16 Speed[4] = {speed, speed, speed, speed};
  byte ACC[4] = {acc, acc, acc, acc};

  st.SyncWritePosEx(ID, 4, Position, Speed, ACC);
}