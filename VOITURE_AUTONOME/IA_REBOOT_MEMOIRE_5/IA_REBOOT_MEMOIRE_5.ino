/****************************************************
 * VOITURE AUTONOME - Version 1.1
 * Mod Score + Mémorisation + Parcours + Autonomie 
 * 
 * ::SCORE::
 * Il y a 4 réactions différentes possibles face à un obstacle :
 * AVANCER || RECULER || GAUCHE || DROITE
 * Par défaut, pour chaque angle (amplitude) balayé par le servomoteur 
 * c'est l'action AVANCER qui possède le meilleur score (3).
 * Lorsque la voiture s'approche d'un obstacle, elle teste l'action
 * qui possède le meilleur score selon l'angle en cours de balayage
 * Si l'action permet au véhicule d'éviter l'obstacle, elle conserve son score à 3
 * Si l'action ne permet pas au véhicule d'éviter l'obstacle,
 * d'autres actions sont testées. C'est l'action qui permet au véhicule
 * d'éviter l'obtacle qui obtient un score égal un 3. Les autres scores sont diminués de 1.
 * le score le plus bas est zéro.
 * 
 * ::MEMORISATION::
 * Le parcours de la voiture est intégralement mémorisé.
 * Codification des coordonnnées : (voir en-tête de MEMORY.h)
 * L'action qui permet à la voiture d'éviter un obstacle est mémorisée.
 * A posteriori, L'action qui apparaît le plus souvent en mémoire,(celle qui a permis 
 * d'éviter un obstacle) modifie le score automatiquement : l'idée est qu'une stratégie  
 * d'évitement qui apparaît souvent en mémoire est probablement La meilleure stratégie.
 * Cette stratégie peut changer de valeur au gré des résultats des tests de la fonction score.
 * 
 * ::PARCOURS::
 * Le parcours étant intégralement sauvegardé en mémoire, la voiture 
 * peut détecter si une séquence d'actions est en train de se répéter. 
 * La détection s'effectue sur 3 actions.
 * Dans ce cas, la voiture réexécute toutes les actions qui s'ensuivent 
 * dans une limite de 7 actions pour ce programme.
 * Et cela indéfiniment sauf si un obstacle apparaît.
 * 
 * ::AUTONOMIE::
 * 
 * 
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
//PHOTORESISTOR
#include "PHOTORESISTOR.h"
/***************************************************/
//CAPTEUR A ULTRASON
#include <HCSR04.h>
const unsigned char trigPin = 13;
const unsigned char echoPin = 12;
//DISTANCE MAX AUTORISEE AVANT REACTION
const unsigned char maxDistance = 20; //30
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
//CAPTEUR INFRAROUGE
#include "INFRAROUGE.h"
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
//LED
#include "LED.h"
/***************************************************/
//SYSTEME DE SCORE
#include "SCORE.h"
/***************************************************/
//SYSTEME DE RECONNAISSANCE DE PARCOURS
#include "PARCOURS.h"
/***************************************************/
//Balayage de sécurité
bool scanner = 0;
unsigned char attente = 0;
/***************************************************/

void setup() 
{  
  iSet                                //Initialisation du Port Série (uniquement pour les tests)
  VOITURE.setupPins();                //Paramétrage par défaut des moteurs
  pinMode(pResistor, INPUT);          //Activer capteur photoresistance
  pinMode(infra, INPUT);              //Activer capteur infrarouge
  servo.setupServo();                 //Paramétrage par défaut du servomoteur
  memo.setupWire();                   //Intialisation du port I2C pour l'EEPROM
  memo.effacer(0,300);                //Effacer 300 données dans l'EEPROM (à modifier selon la durée des tests) 
  delay(2000);                        //Délai avant l'activation du loop
  pinMode(A3, OUTPUT);                //LED rouge
  pinMode(8, OUTPUT);                 //LED jaune
  pinMode(11, OUTPUT);                //LED verte
}

void loop() 
{ 
  /*=========================================================*/ 
  seconde = f.frequence(1000);        //Création d'un cycle d'enregistrement automatique en mémoire > renvoie TRUE tous les x secondes
  f.intervalle(seconde,100);          //Compter jusqu'à 100 et réinitialiser le compteur f.compteurIntervalle
  cycleMemoAuto();                    //Enregistrement auto de l'action AVANCER toutes les 100 secondes si l'action n'est pas interrompue
  /*=========================================================*/
  servo.oscillateur(120);             //Création d'un oscillateur pour le servomoteur
  servo.balayage(amplitude);          //Balayage du servomoteur
  /*=========================================================*/ 
  //verificationScore(amplitude);       //Test
  if(ultrason.measureDistanceCm() >= 0 && ultrason.measureDistanceCm() <= maxDistance)
  {                                   //Obstacle détecté
    eteindreJaune();                  //LED
    eteindreVert();                   //LED
    allumerRouge();                   //LED
    souvenirScore(amplitude);         //Identifier en mémoire l'action récurrente en fonction de l'angle balayé >> réinitialise le tableau matriceSCORE
    //verificationScore(amplitude);     //Test 
    score(amplitude);                 //Tests d'actions et attribution d'un score aux actions d'évitement d'obstacle
    scanner = 1;                      //On active un balayage du servomoteur de 10 loops/angles sans bouger
    attente = 0;                      //Réinitialisation du compteur de balayage de 10 loops/angles si un obstacle est détecté
    ntvrl = 0;                        //Réinitialiser le compteur de la fonction executionParcours()
    cmptrExecution = 3;               //Réinitialiser le compteur pour ne pas sauter d'étapes de parcours à la prochaine détection
  }
  eteindreRouge();                    //LED
  //verificationScore(amplitude);       //Test
  /*=========================================================*/
  memoParcours();                     //Recherche d'une séquence de déplacement similaire à celle en cours d'exécution > renvoie TRUE
  /*=========================================================*/
  //SECURITE: Si obstacle, scanner l'environnement avant de reprendre la route
  if(scanner == 1){attente++;f.compteurIntervalle = 0;}
  if(attente == 10 || scanner == 0 && memoParcours() != 1 && detectionArriere() == false)
  {     
    allumerVert();                    //LED                      
    attente = 0;                      //Réinitialisation du compteur de balayage de 10 loops/angles au bout de 10 loops
    scanner = 0;                      //Désactiver le balayage du servomoteur de 10 loops
    AVANCER;                          //Par défaut, la voiture avance !
  }
  if(detectionArriere() == true)
  {                                   //Si détection arrière
    memoInstantTAvancer();            //Mémorisation parcours déjà effectué
    f.compteurIntervalle = 0;         //Réinitialisation de compteurIntervalle
    GAUCHE;                           //Mouvement réflexe gauche
    memo.ecrire(6);                   //Mémorisation
  }
  /*=========================================================*/  
  executionParcours();                //Execution d'un parcours reconnu à partir des données EEPROM si memoParcours() est à TRUE
  /*=========================================================*/
}
