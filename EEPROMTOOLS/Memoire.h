#ifndef MEMOIRE_H
#define MEMOIRE_H

#include "Arduino.h"

/* 
* 
* OUTILS POUR LE CONTROLE DE L'EEPROM 24LC256
* 
*/

class MEMOIRE{

  public:

	MEMOIRE();
	~MEMOIRE();
	void setupWire();
	static int increment;
	void ecrire(int, unsigned char);
	void ecrire(unsigned char);
	unsigned char lire(int);
	int serial(int, int);
	void effacer(int, int);	
        
};


#endif