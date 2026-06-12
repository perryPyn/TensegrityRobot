#include <SCServo.h>

SMS_STS sms_sts;

void setup()
{
  Serial1.begin(1000000); // Vers Carte
  Serial.begin(115200); // Vers PC
  
  sms_sts.pSerial = &Serial1;
  delay(1000);
}

int ServoID = 1;
void loop()
{
  int Pos;
  if(sms_sts.FeedBack(ServoID) == -1){
    Serial.println("Erreur : Pas de communication avec le Servo");
    return;
  }

  Pos = sms_sts.ReadPos(ServoID);
  if(Pos == -1){
    Serial.println("Erreur de lecture de position");
    return;
  }
  
  Serial.print("Position Servo : ");
  Serial.println(Pos);
  delay(100);
}