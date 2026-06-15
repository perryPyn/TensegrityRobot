#include "Arduino.h"
#include <servo.h>

SMS_STS st;

void initSerial() {
    Serial1.begin(1000000); // Vers Carte
    Serial.begin(115200);   // Vers PC

    st.pSerial = &Serial1;
    delay(1000);
}

void hardReset() {
  st.unLockEprom(254);
  st.Reset(254);
  st.LockEprom(254);
}

void setID(int targetID) {
    st.unLockEprom(254);
    st.writeByte(254, SMS_STS_ID, targetID);
    st.LockEprom(targetID);

    ping(targetID);
}

void setMode(int targetID, int mode) {
    delay(1000);
    st.unLockEprom(targetID);
    delay(1000);
    st.writeByte(targetID, SMS_STS_MODE, mode);
    delay(1000);
    st.LockEprom(targetID);
    delay(1000);
}

void simpleMove(int ID) {
    st.RegWritePosEx(ID, 4095, 3400, 50);
    st.RegWriteAction();
    delay(1884);

    st.RegWritePosEx(ID , 0, 3400, 50);
    st.RegWriteAction();
    delay(1884);
}

void ping(int ID) { 
    int ID_ping = st.Ping(ID);
    if(ID_ping!=-1)
    {
        Serial.print("Servo ID : "); 
        Serial.println(ID_ping, DEC);
        delay(100); 
    }
    else{ 
        Serial.println("Ping servo ID error!"); 
        delay(2000); 
    } 
}

void getPosition(int ID) {
    int Pos = st.ReadPos(ID);
    Serial.print("Position Servo ");
    Serial.print(ID);
    Serial.print(" : ");
    Serial.println(Pos);
    delay(100);
}

void setPosition(int ID, s16 Position) {
    st.RegWritePosEx(ID, Position, 3400, 50);
    st.RegWriteAction();
}

void setPositions(s16 Position[3]) {
    byte ID[3]   = {1,2,3};
    u16 Speed[3] = {3400,3400,3400};
    byte ACC[3]  = {50,50,50};

    st.SyncWritePosEx(ID, 3, Position, Speed, ACC);
    delay(2000);
}