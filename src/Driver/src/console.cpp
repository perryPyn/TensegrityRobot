#include "console.h"

void getConsole() {
    if (Serial.available() > 0) {
        String ligne = Serial.readStringUntil('\n');
        ligne.trim();

        int indexSeparateur = ligne.indexOf('=');
        if (indexSeparateur != -1) {
            String key = ligne.substring(0, indexSeparateur);
            String valStr = ligne.substring(indexSeparateur + 1);
            int val = valStr.toInt();

            if (key == "p1") {
                targetPosition[0] = (s16)val;
                Serial.print("-> Position 1 : ");
                Serial.println(targetPosition[0]);
            } else if (key == "p2") {
              targetPosition[1] = (s16)val;
              Serial.print("-> Position 2 : ");
              Serial.println(targetPosition[1]);
            } else if (key == "p3") {
              targetPosition[2] = (s16)val;
              Serial.print("-> Position 3 : ");
              Serial.println(targetPosition[2]);
            } else {
                Serial.println("Error: Unknown Key");
            }
        }
    }
}