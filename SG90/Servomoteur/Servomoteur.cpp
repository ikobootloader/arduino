/**********************************************************************************************
 * Arduino SG90 TOOLS - Version 1
 * by ikobootloader
 *
 * License GPLv3
 **********************************************************************************************/
#include "Arduino.h"
#include <Servo.h>
#include "Servomoteur.h"

//Class	Objet
Servo 	servomoteur;

SERVOMOTEUR::SERVOMOTEUR(){};

/////// SETUP ///////

void SERVOMOTEUR::setupServo()
{//Setup par défaut
	servomoteur.attach(_servoPin);
}

void SERVOMOTEUR::setupServo(const unsigned char servoPin)
{//Sélection du pin par l'utilisateur
	servomoteur.attach(servoPin);
}

void SERVOMOTEUR::setupServo(const unsigned char servoPin, unsigned char angle)
{//Sélection du pin et de l'angle par l'utilisateur
	servomoteur.attach(servoPin);
	servomoteur.write(angle);
}

/////// FONCTIONS ///////

signed char SERVOMOTEUR::amplitude = -1; //Varie avec la fonction oscillateur
bool SERVOMOTEUR::etat = false;

unsigned char SERVOMOTEUR::oscillateur(int delai)
{
  if(etat == false && amplitude <= 5)
  {//5 positions => Se référer à la matrice d'angles
    amplitude++;
    if(amplitude == 5){
      etat = true;
      amplitude--;
    }
  }
  if(etat == true){
    amplitude--;
    if(amplitude == 0){
      etat = false;
    }
  } 
  delay(delai);
  return amplitude;
}

unsigned char SERVOMOTEUR::angles(const unsigned char angle0, const unsigned char angle1, const unsigned char angle2, const unsigned char angle3, const unsigned char angle4)
{
	this->tabAngles[0] = angle0;
	this->tabAngles[1] = angle1;
	this->tabAngles[2] = angle2;
	this->tabAngles[3] = angle3;
	this->tabAngles[4] = angle4;
}

int SERVOMOTEUR::balayage(unsigned char angle){ //SVM EN ACTION!!	
	servomoteur.write(this->tabAngles[angle] != 0xFF ? this->tabAngles[angle] : _tabAngles[angle]);
}

/////// DESTRUCTEUR ///////

SERVOMOTEUR::~SERVOMOTEUR(){};

		