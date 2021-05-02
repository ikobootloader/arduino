/****************************************************
 * VOITURE AUTONOME - Version 1
 * Mod Score + Mémorisation
 * 
 * ::SCORE::
 * Il y a 4 réactions différentes possibles face à un obstacle :
 * AVANCER || RECULER || GAUCHE || DROITE
 * Par défaut, pour chaque angle (amplitude) balayé par le servomoteur 
 * c'est l'action AVANCER qui possède le meilleur score (1).
 * Lorsque la voiture s'approche d'un obstacle, elle teste l'action
 * qui possède le meilleur score selon l'angle en cours de balayage
 * Si l'action permet au véhicule d'éviter l'obstacle, elle conserve son score à 1
 * Si l'action ne permet pas au véhicule d'éviter l'obstacle,
 * d'autres actions sont testées. C'est l'action qui permet au véhicule
 * d'éviter l'obtacle qui obtient un score égal un 1. Tous les autres actions affichent un score à 0
 * 
 * ::MEMORISATION::
 * Le parcours de la voiture est intégralement mémorisé.
 * Codification : (voir en-tête de MEMORY.h)
 * L'action qui permet à la voiture d'éviter est obstacle est mémorisée.
 * A posteriori, L'action qui apparaît le plus souvent en mémoire,(celle qui a permis 
 * d'éviter un obstacle) modifie le score automatiquement : l'idée est qu'une stratégie  
 * d'évitement qui apparaît souvent en mémoire est probablement La meilleure stratégie.
 * Cette stratégie peut changer de valeur au gré des résultats des tests de la fonction score.
 * 
 * by ikobootloader
 *
 * License GPLv3 
 ***************************************************/

//SIMPLIFICATION DE L'UTILISATION DU PORT SERIE
#define iSet     Serial.begin(9600);
#define i(texte) Serial.println(texte);
/***************************************************/
//FONCTIONS
#include <Fonctions.h>
//Class   Objet
FONCTIONS f; 
/***************************************************/
//CAPTEUR A ULTRASON
#include <HCSR04.h>
const unsigned char trigPin = 13;
const unsigned char echoPin = 12;
//DISTANCE MAX AUTORISEE AVANT REACTION
const unsigned char maxDistance = 25; //
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
#include <Memoire.h>
//Class   Objet
MEMOIRE   memo;
#include "MEMORY.h"
/***************************************************/
//SYSTEME DE SCORE
#include "SCORE.h"
/***************************************************/
//Balayage de sécurité
bool scanner = 0;
unsigned char attente = 0;

void setup() {
  //Port Série (uniquement pour les tests)
  iSet
  //Paramétrage par défaut des moteurs
  VOITURE.setupPins();
  //Paramétrage par défaut des moteurs
  servo.setupServo();
  //Petit délai avant le go
  //Setup de Wire
  memo.setupWire();
  //RESET
  memo.effacer(0,200);
  
  delay(2000);
}

void loop() {

  //Création d'un cycle d'enregistrement automatique en mémoire
  seconde = f.frequence(1000);
  f.intervalle(seconde,100); //Réglée à 100
  //Enregistrement auto du parcours toutes les 100 secondes si AVANCER en continu
  cycleMemoAuto();
  /*=========================================================*/
  //Création d'un oscillateur pour le servomoteur
  servo.oscillateur(140);
  //Balayage du servomoteur
  servo.balayage(amplitude);
  /*=========================================================*/
  //Obstacle
  while(ultrason.measureDistanceCm() >= 0 && ultrason.measureDistanceCm() <= maxDistance){
    souvenirScore(amplitude); //Identifier en mémoire l'action récurrente en fonction de l'angle balayé >> réinitialise le tableau matriceSCORE
    score(amplitude);//tests d'actions
    scanner = 1;
    attente = 0;
  }
  /*=========================================================*/
  //Par défaut,la voiture avance
  //SECURITE:
  //Si obstacle : scanner l'environnement avant de reprendre la route
  if(scanner == 1){attente++;}
  if(attente == 10 || scanner == 0){
    attente = 0;
    scanner = 0;
    AVANCER;  
  }


}
