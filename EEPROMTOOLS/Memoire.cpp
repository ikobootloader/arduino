/**********************************************************************************************
 * Arduino EEPROM 24LC256 TOOLS - Version 2
 * by ikobootloader
 *
 * License GPLv3
 **********************************************************************************************/
#include "Arduino.h"
#include <Wire.h>
#include "Memoire.h"

//Avec l'aide de https://www.instructables.com/Reading-and-Writing-data-to-External-EEPROM-Using-/
//La licence publique générale GPLv3 est revendiquée pour ce script
//////////////////
// 24LC256 >> ARDUINO
// WP | A0 | A1 | A2 >> GND 
// VCC >> 5V
// SCL >> A5
// SDA >> A4
// GND >> GND
//////////////////

//0x50 => adresse de la puce 24LC256

int MEMOIRE::increment = 0;

MEMOIRE::MEMOIRE(){}

void MEMOIRE::setupWire(){
  // INITIALISATION I2C
  Wire.begin();
  Wire.setClock(400000); //https://www.arduino.cc/en/Reference/WireSetClock
}

// ECRIRE
void MEMOIRE::ecrire(int adresseEeprom, unsigned char donnee) 
{
	//éviter les réécritures inutiles !
	if(lire(adresseEeprom) != donnee){
		  Wire.beginTransmission(0x50);
		  Wire.write((int)(adresseEeprom >> 8));   // MSB
		  Wire.write((int)(adresseEeprom & 0xFF)); // LSB
		  Wire.write(donnee);
		  Wire.endTransmission(); 
		  delay(5);
	 }
}

// ECRIRE AVEC ADRESSAGE AUTOMATIQUE A PARTIR DU COMPTEUR MEMOIRE::increment
void MEMOIRE::ecrire(unsigned char donnee) 
{
	if(lire(MEMOIRE::increment) != donnee){
		ecrire(MEMOIRE::increment,donnee);
		MEMOIRE::increment++;
	}
}

// LIRE UNE ADRESSE
unsigned char MEMOIRE::lire(int adresseEeprom) 
{
  byte retourneDonnee = 0xFF;
  Wire.beginTransmission(0x50);
  Wire.write((int)(adresseEeprom >> 8));   // MSB
  Wire.write((int)(adresseEeprom & 0xFF)); // LSB
  Wire.endTransmission();
 
  Wire.requestFrom(0x50,1);
 
  if (Wire.available()) retourneDonnee = Wire.read();
 
  return retourneDonnee;
}

//LIRE PLAGE D'ADRESSES SUR PORT SERIE
int MEMOIRE::serial(int adresseEepromDebut, int adresseEepromFin) 
{
	for(int r = adresseEepromDebut; r <= adresseEepromFin; r++){
		Serial.println(lire(r));
	}
}

// RESET EEPROM
// 24LC256 >> 32767 adressees
void MEMOIRE::effacer(int x, int y){
  for(short int r = x; r <= y ;r++){
	if(lire(r) != 255){ecrire(r,255);}
  }
}

MEMOIRE::~MEMOIRE(){}