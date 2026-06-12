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
  st.RegWritePosEx(2, 4095, 3400, 50);
  st.RegWriteAction();
  delay(1884);

  st.RegWritePosEx(2, 0, 3400, 50);
  st.RegWriteAction();
  delay(1884);
}
