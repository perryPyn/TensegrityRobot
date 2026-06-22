#include "console.h"
#include "HardwareSerial.h"

void getConsole(s16 position[4]) {
  if (Serial.available() > 0) {
    String ligne = Serial.readStringUntil('\n');
    ligne.trim();

    int indexSeparateur = ligne.indexOf('=');
    if (indexSeparateur != -1) {
      String key = ligne.substring(0, indexSeparateur);
      String valStr = ligne.substring(indexSeparateur + 1);
      int val = valStr.toInt();

      if (key == "p1") {
        position[0] = (s16)val;
        Serial.print("-> Position 1 : ");
      } else if (key == "p2") {
        position[1] = (s16)val;
        Serial.print("-> Position 2 : ");
      } else if (key == "p3") {
        position[2] = (s16)val;
        Serial.print("-> Position 3 : ");
      } else if (key == "p4") {
        position[3] = (s16)val;
        Serial.print("-> Position 4 : ");
      } else if (key == "a") {
        alpha = (float)val;
      } else if (key == "o") {
        areServoSetup = true;
      }

      else {
        Serial.println("Error: Unknown Key");
      }
      Serial.println(val);
    }
  }
}