/****************************************************
 * VOITURE AUTONOME - Version 1
 * 
 * ::PRINCIPE::
 * Il y a 4 réactions différentes possibles face à un obstacle :
 * AVANCER || RECULER || GAUCHE || DROITE
 * Par défaut, pour chaque angle (amplitude) balayé par le servomoteur 
 * c'est l'action AVANCER qui possède le meilleur score (1).
 * Lorsque la voiture s'approche d'un obstacle, elle teste l'action
 * qui possède le meilleur score selon l'angle en cours de balayage
 * Si l'action permet au véhicule d'éviter l'obstacle, elle conserve son score à 1
 * Si l'action ne permet pas au véhicule d'éviter l'obstacle,
 * d'autres actions sont testées. C'est l'action qui permet au véhicule
 * d'éviter l'obtacle qui obtient un score à un 1. Toutes les autres actions affichent un score de 0
 * 
 * by ikobootloader
 *
 * License GPLv3 
 ***************************************************/

//CAPTEUR A ULTRASON
#include <HCSR04.h>
const unsigned char trigPin = 13;
const unsigned char echoPin = 12;
//DISTANCE MAX AUTORISEE AVANT REACTION
const unsigned char maxDistance = 30; //
UltraSonicDistanceSensor ultrason(trigPin, echoPin);
/***************************************************/
//CONTROLE DES MOTEURS
#include <Voiture.h>
//Class             Objet
VOITURE_CONTROLES   VOITURE; 
#define AVANCER VOITURE.locomotion(AVANCER,255)
#define RECULER VOITURE.locomotion(RECULER,255)
#define GAUCHE VOITURE.locomotion(GAUCHE,255)
#define DROITE VOITURE.locomotion(DROITE,255)
#define ARRET VOITURE.locomotion(ARRET,0)
/***************************************************/
//CONTROLE DU SERVOMOTEUR
#include <Servomoteur.h>
#define amplitude servo.amplitude
//Class       Ojbet
SERVOMOTEUR   servo;
/***************************************************/
//SYSTEME DE SCORE
#include "score.h"
/***************************************************/
//SIMPLIFICATION DE L'UTILISATION DU PORT SERIE
#define iSet     Serial.begin(9600);
#define i(texte) Serial.println(texte);
/***************************************************/

void setup() {
  //Port Série (uniquement pour les tests)
  iSet
  //Paramétrage par défaut des moteurs
  VOITURE.setupPins();
  //Paramétrage par défaut des moteurs
  servo.setupServo();
  //Petit délai avant le go
  delay(2000);
}

void loop() {

  //Oscillateur du servomoteur
  servo.oscillateur(170);
  //Balayage du servomoteur
  servo.balayage(amplitude);
  //Obstacle
  while(ultrason.measureDistanceCm() >= 0 && ultrason.measureDistanceCm() <= maxDistance){ 
    score(amplitude);
  }
  //Par défaut,la voiture avance
  AVANCER;

}
