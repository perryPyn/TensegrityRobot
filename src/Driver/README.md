# Configuration et Référence du Driver Multi-Servo (SMS/STS)
> 🌍 Read in [English](README.md).
---

Ce dossier contient le driver bas niveau, la gestion du bus UART Half-Duplex, le traitement de la console de commande et les modèles cinématiques inverses pour le contrôle des 4 servomoteurs FEETECH (STS3215).

## Configuration du Bus de Communication

Le driver orchestre deux liaisons de communication série asynchrones sur l'Arduino Mega :
* **Bus Servomoteurs (`Serial1`) :** Liaison Half-Duplex cadencée à **1 000 000 bps**. L'instance globale `st` de la bibliothèque `SMS_STS` est liée à ce port.
* **Liaison Console (`Serial`) :** Liaison série USB vers l'ordinateur cadencée à **115 200 bps**.

### Paramètres Dynamiques par Défaut
* **Vitesse (`speed`) :** `1500` pas/s
* **Accélération (`acc`) :** `50` (unité interne Feetech)
* **Positions de pré-calibration (`precal`) :** `{4600, 5100, 4700, 1100}` (utilisées comme base lors de l'alignement mécanique).
* **Identifiants Servos :** Le bus cible de manière synchrone les IDs matériels `1`, `2`, `3` et `4`.

---

## Référence des Fonctions

### 1. Initialisation et Gestion Matérielle

#### `void initSerial()`
Initialise les ports `Serial` (115200 bauds) et `Serial1` (1000000 bauds). Assigne le pointeur de flux de la bibliothèque Feetech sur `Serial1`. Bloque l'exécution pendant 100 ms pour stabiliser la liaison.

#### `void initServoManual(s16 offset[4])`
Bloque l'exécution dans une boucle `while (!areServoSetup)`. Lit en continu les commandes de position brute via la console série et les applique aux moteurs sans offset. À la sortie de la boucle (réception de la commande `o`), elle calcule et incrémente les offsets finaux du système.

#### `void hardReset()`
Envoie une commande de réinitialisation d'usine complète en utilisant l'adresse de broadcast globale `254`. Nécessite un déverrouillage préalable de l'EPROM.

#### `void setID(u8 ID)`
Modifie l'identifiant d'un servo unique connecté en utilisant l'adresse de broadcast `254`. *Attention : un seul servo doit être présent sur le bus lors de cette opération.*

#### `void setTargetID(u8 ID, u8 targetID)`
Modifie l'ID du servo cible spécifié par `targetID` pour lui attribuer la nouvelle valeur `ID`.

#### `void setMode(u8 ID, int mode)`
Configure le mode de fonctionnement du servo dans son registre EPROM `SMS_STS_MODE` :
* `0` : Mode Position
* `1` / `2` : Mode Vitesse continue
* `3` : Mode Pas-à-pas / Étape

#### `void enableMultiLoop(u8 ID, u16 minAngle, u16 maxAngle)`
Configure les limites angulaires minimales et maximales en écrivant dans l'EPROM. Permet de passer le servo en mode multi-tours absolu (par exemple avec les valeurs `1, 1`).

---

### 2. Lecture des Données (Feedback)

#### `void ping(u8 ID)`
Envoie une requête Ping au servo `ID`. Affiche le résultat ou une erreur sur la console série.

#### `s16 getPosition(u8 ID)`
Interroge le servo pour obtenir la position absolue actuelle de son encodeur magnétique via la fonction `st.ReadPos()`. Retourne la valeur et l'affiche sur la console.

#### `s16 getLoad(u8 ID)`
Lit et retourne la charge mécanique (couple instantané) appliquée sur le moteur via `st.ReadLoad()`.

#### `void printPositions(s16 position[4])`
Formate et affiche une ligne dans la console série contenant les positions actuelles des 4 servos séparées par des barres verticales.

---

### 3. Contrôle des Mouvements

#### `void setPosition(u8 ID, s16 Position)`
Envoie une consigne de position asynchrone à un seul servo avec la vitesse et l'accélération globales du driver (`RegWritePosEx`), puis déclenche le mouvement via `RegWriteAction()`.

#### `void setPositionsRaw(s16 Position[4])`
Diffuse un paquet synchrone (`SyncWritePosEx`) contenant les positions brutes fournies directement aux 4 servos (IDs 1 à 4). Les offsets logiciels ne sont pas appliqués.

#### `void setPositions(s16 Position[4], s16 Offset[4])`
Calcule les positions corrigées (`Position[i] + Offset[i]`) et transmet un paquet synchrone aux 4 servos simultanément avec les paramètres de vitesse et d'accélération globaux.

---

### 4. Modèles Cinématiques et Utilitaires (`utils.cpp`)

#### `void computeSimplePosition(float alpha, s16 position[4])`
Calcule le modèle cinématique inverse simplifié sur un seul axe. Convertit l'angle de tangage `alpha` (en degrés) en longueurs de câbles théoriques, puis détermine les consignes en incréments pour les 4 servos.

#### `void computePosition(float alpha, float beta, s16 position[4])`
Calcule le modèle cinématique inverse complet prenant en compte le tangage `alpha` et le roulis `beta` (en degrés). Remplit le tableau `position` avec les coordonnées articulaires (incréments) requises pour les 4 servos.

#### `void demoAlphaBeta(int N, s16 a[], s16 b[])`
Génère une trajectoire de démonstration en quadrature de phase (signaux sinus et cosinus d'amplitude 25) répartie sur `N` échantillons pour tester le comportement dynamique.

---

## Gestion des Commandes Console (`console.cpp`)

Le driver intègre un parseur de chaînes de caractères basé sur le protocole `Clé=Valeur`.

* **`void handleServoCommand(s16 position[4])` :** Actif pendant la phase d'initialisation. Interprète les messages du type `p1=val` à `p4=val` pour modifier le tableau de position brut. La réception du caractère seul `o` passe la variable globale `areServoSetup` à `true` pour valider l'alignement.
* **`void handleAngleCommand()` :** Actif pendant la boucle principale. Interprète les messages du type `a=val` et `b=val` pour mettre à jour directement les variables globales d'angles `alpha` et `beta`.