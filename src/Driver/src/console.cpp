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
      } else if (key == "p2") {
        position[1] = (s16)val;
      } else if (key == "p3") {
        position[2] = (s16)val;
      } else if (key == "p4") {
        position[3] = (s16)val;
        // } else if (key == "p5") {
        //   p5 = (s16)val;
      } else if (key == "a") {
        alpha = (float)val;
      } else if (key == "b") {
        beta = (float)val;
      } else if (key == "o") {
        areServoSetup = true;
      }

      else {
        Serial.println("Error: Unknown Key");
      }
      // Serial.println(val);
    }
  }
}

void handleServoCommand(s16 position[4]) {
  if (Serial.available() > 0) {
    String ligne = Serial.readStringUntil('\n');
    ligne.trim();

    if (ligne.length() == 0)
      return;

    if (ligne == "o") {
      areServoSetup = true;
      Serial.println("Setup servo ... OK");
      return;
    }

    int indexSeparateur = ligne.indexOf('=');
    if (indexSeparateur != -1) {
      String key = ligne.substring(0, indexSeparateur);
      int val = ligne.substring(indexSeparateur + 1).toInt();

      if (key[0] == 'p' && key.length() == 2) {
        int index = key[1] - '1'; // Convertit '1'-'4' en index 0-3
        if (index >= 0 && index < 4) {
          position[index] = (s16)val;
        } else {
          Serial.println("Error: Invalid Servo Index");
        }
      } else {
        Serial.println("Error: Not a servo command");
      }
    } else {
      Serial.println("Error: Missing '='");
    }
  }
}

void handleAngleCommand() {
  if (Serial.available() > 0) {
    String ligne = Serial.readStringUntil('\n');
    ligne.trim();

    if (ligne.length() == 0)
      return;

    int indexSeparateur = ligne.indexOf('=');
    if (indexSeparateur != -1) {
      String key = ligne.substring(0, indexSeparateur);
      int val = ligne.substring(indexSeparateur + 1).toInt();

      if (key == "a") {
        alpha = (float)val;
      } else if (key == "b") {
        beta = (float)val;
      } else {
        Serial.println("Error: Not an angle command");
      }
    } else {
      Serial.println("Error: Missing '='");
    }
  }
}