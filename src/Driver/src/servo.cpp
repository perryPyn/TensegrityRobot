#include "servo.h"
#include "HardwareSerial.h"
#include "console.h"
#include "imu.h"

SMS_STS st;
u16 speed = 1500;
byte acc = 50;

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

void initServo() {
  for (u8 i = 1; i < 5; i++) {
    setMode(i, 0);
    enableMultiLoop(i, 1, 1);
  }
}

void calibrationServo(s16 offset[4]) {
  MMA8452Q accel;

  Serial.println("==== Entering servo setup ====");
  s16 position[4] = {offset[0], offset[1], offset[2], offset[3]};

  while (!areServoSetup) {
    handleInitCommand(&areServoSetup);
    handleServoCommand(position);

    setPositionsRaw(position);

    float rawAlpha = 0, rawBeta = 0;
    readIMU(&rawBeta, &rawAlpha);
    Serial.print("alpha -> ");
    Serial.print(rawAlpha);
    Serial.print(" | beta -> ");
    Serial.println(rawBeta);

    delay(200);
  }
  offset[0] = position[0];
  offset[1] = position[1];
  offset[2] = position[2];
  offset[3] = position[3];

  Serial.println("==== Exiting servo setup ====");
}

void hardReset() {
  st.unLockEprom(254);
  delay(20);

  st.Reset(254);
  delay(100);

  st.LockEprom(254);
  delay(20);
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

void setTargetID(u8 ID, u8 targetID) {
  /*
   * Change the ID of the connected servo.
   * They should be done one at a time.
   */

  st.unLockEprom(targetID);
  delay(20);

  st.writeByte(targetID, SMS_STS_ID, ID);
  delay(100);

  st.LockEprom(ID);
  delay(20);

  ping(ID);
}

void setMode(u8 ID, int mode) {
  /*
   * Change the mode between position (0), speed (1/2) and stepper (3) control.
   */

  st.unLockEprom(ID);
  delay(20);

  st.writeByte(ID, SMS_STS_MODE, mode);
  delay(100);

  st.LockEprom(ID);
  delay(20);

  Serial.print("Changed servo ");
  Serial.print(ID);
  Serial.print(" mode for ");
  Serial.print("Changed servo");
  Serial.println(mode);
}

void enableMultiLoop(u8 ID, u16 minAngle, u16 maxAngle) {
  /*
   * Changes the rotation range of the designated servo.
   * (1,1) for multi-turn with negatives values.
   */

  st.unLockEprom(ID);
  delay(20);

  st.writeWord(ID, SMS_STS_MIN_ANGLE_LIMIT_L, MAX_INCREMENT * minAngle);
  delay(100);

  st.writeWord(ID, SMS_STS_MAX_ANGLE_LIMIT_L, MAX_INCREMENT * maxAngle);
  delay(100);

  st.LockEprom(ID);
  delay(20);

  Serial.print("Enabled multi-loop mode for servo ");
  Serial.println(ID);
}

// void enableTorque(u8 ID, u8 state) {
//   // st.writeByte(ID, SMS_STS_TORQUE_ENABLE, state);
//   st.EnableTorque(ID, state);

//   Serial.print("Torque : ");
//   Serial.println(st.readByte(ID, SMS_STS_TORQUE_ENABLE));
// }

void ping(u8 ID) {
  /*
   * Check communication with servo with target ID
   */

  int ID_ping = st.Ping(ID);
  if (ID_ping != -1) {
    Serial.print("Pinging servo ID : ");
    Serial.println(ID_ping, DEC);
  } else {
    Serial.print("Pinging servo ID : ");
    Serial.print(ID, DEC);
    Serial.println(" error!");
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

s16 getLoad(u8 ID) {
  /*
   * Print the current load of target servo.
   */

  int load = st.ReadLoad(ID);
  Serial.print("Load Servo ");
  Serial.print(ID);
  Serial.print(" : ");
  Serial.println(load);

  return load;
}

void setPosition(u8 ID, s16 Position) {
  /*
   * Move the motor to desired position with pre-determined Speed and ACC.
   */

  st.RegWritePosEx(ID, Position, speed, acc);
  st.RegWriteAction();
}

void setPositionsRaw(s16 Position[4]) {
  /*
   * Move the motors to desired positions with pre-determined Speed and ACC.
   */

  u8 ID[4] = {1, 2, 3, 4};
  u16 Speed[4] = {speed, speed, speed, speed};
  byte ACC[4] = {acc, acc, acc, acc};

  st.SyncWritePosEx(ID, 4, Position, Speed, ACC);
}

void setPositions(s16 Position[4], s16 Offset[4]) {
  /*
   * Move the motors to desired positions with pre-determined Speed and ACC,
   * knowing the offset.
   */

  u8 ID[4] = {1, 2, 3, 4};
  u16 Speed[4] = {speed, speed, speed, speed};
  byte ACC[4] = {acc, acc, acc, acc};

  s16 correctedPosition[4] = {
      Position[0] + Offset[0],
      Position[1] + Offset[1],
      Position[2] + Offset[2],
      Position[3] + Offset[3],
  };

  st.SyncWritePosEx(ID, 4, correctedPosition, Speed, ACC);
}

void printPositions(s16 position[4]) {
  Serial.print(" | ");
  Serial.print(position[0]);
  Serial.print(" | ");
  Serial.print(position[1]);
  Serial.print(" | ");
  Serial.print(position[2]);
  Serial.print(" | ");
  Serial.print(position[3]);
  Serial.println(" | ");
}
