#include <Wire.h>     //I2C library

//////////////////
// 24LC256 >> ARDUINO
// WP | A0 | A1 | A2 >> GND 
// VCC >> 5V
// SCL >> A5
// SDA >> A4
// GND >> GND
//////////////////

//#include <ArduinoSTL.h>

#include <EEPROMTOOLS.h>


void setup() {

  //LECTURE POUR TESTS
  Serial.begin(9600);

  // INITIALISATION
  Wire.begin();
  Wire.setClock(400000); //https://www.arduino.cc/en/Reference/WireSetClock

  //ECRITURE POUR TESTS 
  writeEEPROM(rom, 0, 10 ); 
  writeEEPROM(rom, 1, 7 ); 
  writeEEPROM(rom, 2, 4 );
  writeEEPROM(rom, 3, 59 );
  writeEEPROM(rom, 4, 12 );

}

void loop() {

  // TESTS
   Serial.println(F("________________________"));
   Serial.println(readEEPROM(rom, 0), DEC);
   Serial.println(readEEPROM(rom, 1), DEC);
   Serial.println(readEEPROM(rom, 2), DEC);
   Serial.println(readEEPROM(rom, 3), DEC);
   Serial.println(readEEPROM(rom, 4), DEC);
   Serial.println(F("________________________")); 
   delay(3000);  

   //test
   int read0,read1,read2,read3,read4 = 0;
   read0 = readEEPROM(rom, 0), DEC;
   read1 = readEEPROM(rom, 1), DEC;
   read2 = readEEPROM(rom, 2), DEC;
   read3 = readEEPROM(rom, 3), DEC;
   read4 = readEEPROM(rom, 4), DEC;
   int tailletab[5] = {read0,read1,read2,read3,read4};
   int resultatTaille = 0;
   int resultat = 0;

   //resetEEPROM(0, 5);//fonctionne!
   // taille du tableau
   resultatTaille = SIZE_ARR(tailletab); //FONCTIONNE !!!
   // valeur mini du tableau
   //resultat = mini(tailletab,resultatTaille);  //FONCTIONNE !!!
   // valeur maxi du tableau
   //resultat = maxi(tailletab,resultatTaille);  //FONCTIONNE !!!
   // tri croissant
   //sortAsc(tailletab,resultatTaille);   //FONCTIONNE !!!
   // tri decroissant
   //sortDesc(tailletab,resultatTaille);   //FONCTIONNE !!!
   // REVERSE
   //rev(tailletab,5);  //FONCTIONNE !!!

   //savoir si adresses qui se suivent possédent la même valeur
   //resultat = addSmVal(12, 0, 2); //FONCTIONNE !!!

   //compter le nombre de fois qu'une valeur identique est enregistrée sur une plage d'adresses
    //trouver le nombre d'occurrence
   //resultat = occ(12,0,4);   //FONCTIONNE !!!  

    //Retrouver adresse correspondante
   //resultat = AddVal(12, 0, 4);    //FONCTIONNE !!! 

   // TROUVER DES ADRESSES AVEC LA MEME VALEUR
   //int *p = seqMmVal(12, 0, 4);   //FONCTIONNE !!! 
   //Serial.println(p[0]); 

   //créer un tableau 1D
  //int *t = arrVal(0,2); //FONCTIONNE !!!

     // création d'une matrice 2D
   int **t = matrix2D(0,4,5); //FONCTIONNE !!!
   Serial.println(t[0][1]); 
  

}
