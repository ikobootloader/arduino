#ifndef MEMOIRE_H
#define MEMOIRE_H

#include "Arduino.h"

/* 
* 
* OUTILS POUR LE CONTROLE DES MOTEURS RELIES AU L298N
* 
*/

class MEMOIRE{

  public:

	MEMOIRE();
	~MEMOIRE();
	void effacer(int x, int y);
	void ecrire(int adresseAppareil, unsigned int adresseEeprom, byte donnee);
	byte lire(int adresseAppareil, unsigned int adresseEeprom);
        
};


#endif