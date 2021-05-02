Nomenclature L298N

/*
 *BRANCHEMENTS PAR DEFAUT
 *enAPin = 6; // Contrôle de vitesse PWM du moteur gauche
 *in1Pin = 7; // Moteur gauche Direction 1
 *in2Pin = 5; // Moteur gauche Direction 2
 *in3Pin = 4; // Moteur droit Direction 1
 *in4Pin = 2; // Moteur droit Direction 2
 *enBPin = 3; // Contrôle de vitesse PWM du moteur droit
*/

//Class             Objet
VOITURE_CONTROLES   VOITURE;

  //Utilisation minimisée du code (non obligatoire)
  #define AVANCER VOITURE.locomotion(AVANCER,255)
  #define RECULER VOITURE.locomotion(RECULER,255)
  #define GAUCHE VOITURE.locomotion(GAUCHE,255)
  #define DROITE VOITURE.locomotion(DROITE,255)
  #define ARRET VOITURE.locomotion(ARRET,0)

  //Paramétrage par défaut
  VOITURE.setupPins();
  
  //Paramétrage manuel: VOITURE.setupPins(enAPin,in1Pin,in2Pin,in3Pin,in4Pin,enBPin)
  Exemple: VOITURE.setupPins(6,7,5,4,2,3);
  
  //Paramétrage par nombre ou mot
  //0 ou AVANT | 1 ou ARRIERE | 2 ou GAUCHE | 3 ou DROITE | 4 ou ARRET
  //Exemple: VOITURE.locomotion(0,255) <=> VOITURE.locomotion(AVANCER,255)
  //VOITURE.locomotion(0,255);
  VOITURE.locomotion(AVANCER,255);
  
  
  
  
