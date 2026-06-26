# Bras articulé fonctionnant avec le principe de tenségrité
> 🌍 Read in [English](README.md).
---


<p align="center">
  <img width="444" height="576" alt="imageCoude" src="./assets/Robot1.jpeg" />
  <br>
  <em>Figure 1 : Prototype du robot par tenségrité avec ses 4 servomoteurs.</em>
</p>

## À propos du projet
L’objectif de ce projet est de créer un bras robotique poly-articulé basé sur le principe de tenségrité. Tous les fichiers pour l'impression 3D sont disponible dans [`/CAD`](./CAD). Le driver est disponible dans [`/Driver`](./src/Driver)


## Matériel
* Arduino Mega
* 4x Servomoteurs FEETECH STS3215
* Alimentation externe : Adaptateur secteur universel AC réglable 12 W, 7.5 V
> ⚠️ **Note sur l'alimentation :** Le principe de tenségrité impose une tension mécanique constante sur les câbles. Les moteurs consomment du courant même au maintien. Une alimentation de 7.5 V capable de délivrer au moins 4 A à 5 A est fortement recommandée pour éviter les chutes de tension lors des mouvements simultanés.


## Principe mathématique
L'objectif est de définir l'orientation de la plateforme mobile selon deux axes de rotation :

| Variable | Description |
| :--- | :--- |
| $\alpha$ | Angle de tangage |
| $\beta$ | Angle de roulis |
| $R$ | Rayon de la base (47.5 mm) |
| $H$ | Distance entre les deux plateaux (85 mm) |
| $r$ | Rayon du tambour d'enroulement (12.5 mm) |
| $nb\_inc$ | Nombre d'incréments par tour du STS3215 (4096) |
| $l_i$ | longueur des cables à chaque point d'ancrage |

* On calcule la longueur de consigne de chaque câble :
  * $l_1 = \sqrt{(R\sin(\alpha)+H)^2 + (R\cos(\alpha)-R)^2}$
  * $l_2 = \sqrt{(R\cos(\beta)-R)^2 + (R\sin(\beta)\cos(\alpha)+H)^2 + (R\sin(\beta)\cos(\alpha))^2}$
  * $l_3 = \sqrt{(R - R\cos(\alpha))^2 + (H-R\sin(\alpha))^2}$
  * $l_4 = \sqrt{(R - R\cos(\beta))^2 + (H - R\sin(\beta)\cos(\alpha))^2 + (R\sin(\beta)\cos(\alpha))^2}$

* On peut ensuite déterminer la position angulaire des servomoteurs en terme d'incréments :
  * $p_i  = \frac{H-l_i}{2\pi r}\times nb\_inc$

## Configuration logicielle et Bus
Les servomoteurs FEETECH STS3215 sont chaînés sur un bus série asynchrone à un fil (Half-Duplex) connecté au port `Serial1` de l'Arduino Mega.

* **Baudrate du bus servos :** 1 000 000 bps
* **Baudrate de la console PC :** 115200 bps
* **Identifiants des servos :** `1`, `2`, `3` et `4`

## Interface de commande (Série)
Le robot écoute les commandes texte sur le port de communication USB (`Serial` à 115200 bauds). Les commandes disponibles sont :

* **Mode Configuration / Calibration :**
  * `p1=val`, `p2=val`, `p3=val`, `p4=val` : Ajuste la position brute (en incréments) de chaque servomoteur pour aligner la structure.
  * `o` : Valide la configuration actuelle, enregistre les offsets et lance l'application principale.

* **Mode Fonctionnement :**
  * `a=val` : Modifie l'angle d'inclinaison $\alpha$ (tangage).
  * `b=val` : Modifie l'angle d'inclinaison $\beta$ (roulis).
