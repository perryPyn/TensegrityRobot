#include <SCServo.h>

SMS_STS st;

void setup()
{
  Serial.begin(1000000);
  st.pSerial = &Serial;
  delay(1000);
}

void loop()
{
  st.WheelMode(1);
}
