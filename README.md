# TensegrityRobot
<img width="444" height="576" alt="imageCoude" src="https://github.com/user-attachments/assets/cbadc10f-2ef4-4826-b198-b3c750269679" />

## 📖 À propos du projet
L’objectif de ce projet est de créer un bras robotique poly-articulé basé sur le principe de tenségrité en faisant le design 3D et en le contrôlant avec des servomoteurs. Pour commencer nous avons donc réalisé un prototype d'articulation de type coude.
## 🛠️ Matériel requis
* 1x Arduino Mega
* 4x Servomoteurs FEETECH STS3215
* Alimentation externe : Adaptateur secteur universel AC réglable 12W (reglé sur 7.5 V)
## 📐 Principe mathématique
L'objectif est de définir l'orientation de la plateforme mobile selon deux axes de rotation :
* **$\alpha$ :** Le Tangage 
* **$\beta$ :** Le Roulis
Connaissant le rayon de la base ($R = 47.5$ mm) et la hauteur au repos ($H = 12$ mm), le microcontrôleur calcule en temps réel la distance euclidienne exacte requise entre les 4 points d'ancrage de la base ($P_1$ à $P_4$) et ceux de la plateforme mobile ($B_1$ à $B_4$).

Ces calculs permettent de déterminer la longueur de consigne de chaque câble que les servomoteurs doivent ensuite atteindre :
* $P_1B_1 = \sqrt{(R - R\cos(\alpha)\cos(\beta))^2 + (R\cos(\alpha)\sin(\beta))^2 + (R\sin(\alpha) + H)^2}$
* $P_2B_2 = \sqrt{(R\cos(\beta) - R)^2 + (R\sin(\beta))^2 + H^2}$
* $P_3B_3 = \sqrt{(R\cos(\alpha)\sin(\beta))^2 + (R\cos(\alpha)\cos(\beta) - R)^2 + (R\sin(\alpha) + H)^2}$
* $P_4B_4 = \sqrt{(R - R\cos(\beta))^2 + (R\sin(\beta))^2 + H^2}$
