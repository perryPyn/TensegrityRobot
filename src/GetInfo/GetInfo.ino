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
  if(sms_sts.FeedBack(1) != -1){
    Pos = sms_sts.ReadPos(1);
    
    if(Pos != -1){
      Serial.print("Position Servo");
      Serial.println(Pos);
    } else {
      Serial.println("Erreur de lecture de position");
    }
  } else { 
    Serial.println("Erreur : Pas de communication avec le Servo");
  }
  
  delay(100);
}