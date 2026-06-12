#define S_RXD 18
#define S_TXD 19
#include <SCServo.h>

SMS_STS sms_sts;

void setup()
{
  Serial1.begin(1000000, SERIAL_8N1, S_RXD, S_TXD);
  Serial.begin(115200);
  sms_sts.pSerial = &Serial1;
  delay(1000);
}

void loop()
{
  int Pos;
  if(sms_sts.FeedBack(1)!=-1){
    Pos = sms_sts.ReadPos(-1);\
    Serial.print("Position:");
    Serial.println(Pos);
    delay(10);
  }else{ \
    Serial.println("FeedBack err");
    delay(500);
  }
  
  Pos = sms_sts.ReadPos(1);  // Get the position feedback
  if(Pos!=-1){
    Serial.print("Servo position:");
    Serial.println(Pos, DEC);
    delay(10);
  }else{
    Serial.println("read position err");
    delay(500);
  }
  Serial.println();
}