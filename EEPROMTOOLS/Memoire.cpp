#include "Arduino.h"
#include <Wire.h>
#include "MEMOIRE.h"

//Avec laide de https://www.instructables.com/Reading-and-Writing-donnee-to-External-EEPROM-Using-/
//La licence publique générale GPLv3 est revendiquée pour ce script
//////////////////
// 24LC256 >> ARDUINO
// WP | A0 | A1 | A2 >> GND 
// VCC >> 5V
// SCL >> A5
// SDA >> A4
// GND >> GND
//////////////////

#define rom 0x50    //adresse of 24LC256 eeprom chip

MEMOIRE::MEMOIRE(){}

// RESET EEPROM
// 24LC256 >> 32767 adressees
void MEMOIRE::effacer(int x, int y){
  for(short int r = x; r <= y ;r++) ecrire(rom,r,255);
}

// ECRIRE/WRITE
void MEMOIRE::ecrire(int adresseAppareil, unsigned int adresseEeprom, byte donnee) 
{
  Wire.beginTransmission(adresseAppareil);
  Wire.write((int)(adresseEeprom >> 8));   // MSB
  Wire.write((int)(adresseEeprom & 0xFF)); // LSB
  Wire.write(donnee);
  Wire.endTransmission();
 
  delay(5);
}

// LIRE/READ
byte MEMOIRE::lire(int adresseAppareil, unsigned int adresseEeprom) 
{
  byte retourneDonnee = 0xFF;
 
  Wire.beginTransmission(adresseAppareil);
  Wire.write((int)(adresseEeprom >> 8));   // MSB
  Wire.write((int)(adresseEeprom & 0xFF)); // LSB
  Wire.endTransmission();
 
  Wire.requestFrom(adresseAppareil,1);
 
  if (Wire.available()) retourneDonnee = Wire.read();
 
  return retourneDonnee;
}

MEMOIRE::~MEMOIRE(){}