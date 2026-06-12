#include <SCServo.h>

SMS_STS sms_sts;

void setup()
{
  Serial1.begin(1000000); // Vers Carte
  Serial.begin(115200); // Vers PC
  
  sms_sts.pSerial = &Serial1;
  delay(1000);
}

void loop()
{
  int Pos;
  Pos = sms_sts.ReadPos(1);
  Serial.print("Position Servo 1 : ");
  Serial.println(Pos);
  delay(100);

  Pos = sms_sts.ReadPos(2);
  Serial.print("Position Servo 2 : ");
  Serial.println(Pos);
  delay(100);
}