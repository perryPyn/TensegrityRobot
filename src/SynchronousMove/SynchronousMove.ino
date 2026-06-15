#include <SCServo.h>
SMS_STS st;

byte ID[2];
s16 Position[2];
u16 Speed[2];
byte ACC[2];

void setup()
{
  Serial1.begin(1000000);
  st.pSerial = &Serial1;
  delay(1000);
  ID[0] = 1;   // Save the IDs of the servos that need to be controlled into the ID[]
  ID[1] = 2;   // Save the IDs of the servos that need to be controlled into the ID[]
  Speed[0] = 3400;  // Set the servo speed, Speed[0] should correspond to the servo with ID[0]
  Speed[1] = 3400;  // Set the servo speed, Speed[1] should correspond to the servo with ID[1] 
  ACC[0] = 50;   // Set the start/stop acceleration. The smaller the value, the lower the acceleration. The maximum value that can be set is 150.
  ACC[1] = 50;
}

void loop()
{
  Position[0] = 3000;  // Set the target position for the servo with ID[0] (which has an ID of 1) to a range of 0-4095
  Position[1] = 3000;  // Set the target position for the servo with ID[0] (which has an ID of 1) to a range of 0-4095
  st.SyncWritePosEx(ID, 2, Position, Speed, ACC);//servo(ID1/ID2) speed=3400，acc=50，move to position=3000.
  delay(2000);

  Position[0] = 100;
  Position[1] = 100;
  st.SyncWritePosEx(ID, 2, Position, Speed, ACC);//servo(ID1/ID2) speed=3400，acc=50，move to position=100.
  delay(2000);
}