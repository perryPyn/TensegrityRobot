#include <SCServo.h>

SMS_STS sms_sts;

const int targetID = 3;

void setup()
{
  Serial1.begin(1000000);
  sms_sts.pSerial = &Serial1;
  delay(1000);
  sms_sts.unLockEprom(254);
  sms_sts.writeByte(254, SMS_STS_ID, targetID);
  sms_sts.LockEprom(targetID);
}

void loop()
{ 
  // Checking
  sms_sts.RegWritePosEx(targetID, 4095, 3400, 50);
  sms_sts.RegWriteAction();
  delay(1884);

  sms_sts.RegWritePosEx(targetID, 0, 3400, 50);
  sms_sts.RegWriteAction();
  delay(1884);
}
