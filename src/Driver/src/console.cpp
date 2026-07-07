#include "console.h"

void handleInitCommand(bool *areServoSetup) {
  if (Serial.available() > 0) {
    // Vérifie le premier caractère sans vider le buffer série
    if (Serial.peek() == 'o') {
      String ligne = Serial.readStringUntil('\n');
      ligne.trim();

      if (ligne == "o") {
        *areServoSetup = true;
        Serial.println("Setup servo ... OK");
      }
    }
  }
}

void handleServoCommand(s16 position[4]) {
  if (Serial.available() > 0) {
    // Vérifie si la commande commence par 'p' avant de lire
    if (Serial.peek() == 'p') {
      String ligne = Serial.readStringUntil('\n');
      ligne.trim();

      int indexSeparateur = ligne.indexOf('=');
      if (indexSeparateur != -1) {
        String key = ligne.substring(0, indexSeparateur);
        int val = ligne.substring(indexSeparateur + 1).toInt();

        if (key.length() == 2) {
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
}

void handleAngleCommand(float *alpha, float *beta) {
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
        *alpha = (float)val;
      } else if (key == "b") {
        *beta = (float)val;
      } else {
        Serial.println("Error: Not an angle command");
      }
    } else {
      Serial.println("Error: Missing '='");
    }
  }
}
