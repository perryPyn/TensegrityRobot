#include <SCServo.h>

SMS_STS sms_sts;

void setup()
{
  Serial.begin(1000000);
  sms_sts.pSerial = &Serial;
  delay(1000);
}

void loop()
{
  int Pos;
  int Speed;
  int Load;
  int Voltage;
  int Temper;
  int Move;
  int Current;
  if(sms_sts.FeedBack(1)!=-1){
    Pos = sms_sts.ReadPos(-1);  
    
    Speed = sms_sts.ReadSpeed(-1);
    Load = sms_sts.ReadLoad(-1);
    Voltage = sms_sts.ReadVoltage(-1);
    Temper = sms_sts.ReadTemper(-1);
    Move = sms_sts.ReadMove(-1);
    Current = sms_sts.ReadCurrent(-1);
    Serial.print("Position:");
    Serial.println(Pos);
    Serial.print("Speed:");
    Serial.println(Speed);
    Serial.print("Load:");
    Serial.println(Load);
    Serial.print("Voltage:");
    Serial.println(Voltage);
    Serial.print("Temper:");
    Serial.println(Temper);
    Serial.print("Move:");
    Serial.println(Move);
    Serial.print("Current:");
    Serial.println(Current);
    delay(10);
  }else{
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
  
  Voltage = sms_sts.ReadVoltage(1);   //Get the voltage feedback
  if(Voltage!=-1){
	Serial.print("Servo Voltage:");
    Serial.println(Voltage, DEC);
    delay(10);
  }else{
    Serial.println("read Voltage err");
    delay(500);
  }
  
  Temper = sms_sts.ReadTemper(1);   //Get the temperature feedback
  if(Temper!=-1){
    Serial.print("Servo temperature:");
    Serial.println(Temper, DEC);
    delay(10);
  }else{
    Serial.println("read temperature err");
    delay(500);    
  }

  Speed = sms_sts.ReadSpeed(1);   //Get the speed feedback
  if(Speed!=-1){
    Serial.print("Servo Speed:");
    Serial.println(Speed, DEC);
    delay(10);
  }else{
    Serial.println("read Speed err");
    delay(500);    
  }
  
  Load = sms_sts.ReadLoad(1);   //Get the load feedback
  if(Load!=-1){
    Serial.print("Servo Load:");
    Serial.println(Load, DEC);
    delay(10);
  }else{
    Serial.println("read Load err");
    delay(500);    
  }
  
  Current = sms_sts.ReadCurrent(1);   //Get the current feedback
  if(Current!=-1){
    Serial.print("Servo Current:");
    Serial.println(Current, DEC);
    delay(10);
  }else{
    Serial.println("read Current err");
    delay(500);    
  }

  Move = sms_sts.ReadMove(1);   //Get the movement feedback
  if(Move!=-1){
    Serial.print("Servo Move:");
    Serial.println(Move, DEC);
    delay(10);
  }else{
    Serial.println("read Move err");
    delay(500);    
  }
  Serial.println();
}