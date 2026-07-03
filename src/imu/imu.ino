#include "Wire.h"
#include "SparkFun_MMA8452Q.h"
// Création de l'objet capteur avec l'adresse I2C 0x1C (car SA0 est relié à GND)
MMA8452Q accel;
void setup() {
  //Sert à démarer la communication entre le pc et la carte à un baud rate de 9600 (bits/sec)
Serial.begin(115200);
Serial.println("Initialisation du capteur..."); 

//Ouvre la communication en I2C
Wire.begin();

// Démarrage du capteur avec l'adresse spécifiée
  if (accel.begin(Wire, 0x1C) == false) {
    Serial.println("Capteur introuvable ! Vérifiez le câblage (SDA=20, SCL=21, SA0=GND).");
    while (1); // Bloque le programme ici si erreur
  }
  Serial.println("Capteur détecté avec succès !");
}
  
void loop() {
 if (accel.available()) {
    
    // Lecture des accélérations en "g" (1g = gravité terrestre)
    float x = accel.getCalculatedX();
    float y = accel.getCalculatedY();
    float z = accel.getCalculatedZ();

    // Calcul de l'inclinaison en degrés
    // Roulis : Inclinaison gauche/droite (autour de l'axe X)
    float roll = atan2(y, z) * 180.0 / PI;

    // Tangage : Inclinaison avant/arrière (autour de l'axe Y)
    float pitch = atan2(-x, sqrt(y * y + z * z)) * 180.0 / PI;

    // Affichage sur le moniteur série
    Serial.print("Accélération (g) -> X: "); Serial.print(x, 2);
    Serial.print("  Y: "); Serial.print(y, 2);
    Serial.print("  Z: "); Serial.print(z, 2);

    Serial.print("  |  Inclinaison (deg) -> Roulis: "); Serial.print(roll, 1);
    Serial.print("  Tangage: "); Serial.println(pitch, 1);
  }
  
  delay(100); 
}

