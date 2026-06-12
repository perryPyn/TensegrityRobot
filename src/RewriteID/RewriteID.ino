#include <SCServo.h>

SMS_STS sms_sts;

const int targetID = 2;

void setup()
{
  Serial.begin(1000000);
  sms_sts.pSerial = &Serial;
  delay(1000);
  sms_sts.unLockEprom(254);
  sms_sts.writeByte(254, SMS_STS_ID, targetID);
  sms_sts.LockEprom(targetID);
}

void loop()
{

}
