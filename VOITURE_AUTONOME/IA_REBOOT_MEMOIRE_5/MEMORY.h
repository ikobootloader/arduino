#ifndef MEMORY_H
#define MEMORY_H
//////////////////
// 24LC256 >> ARDUINO
// WP | A0 | A1 | A2 >> GND 
// VCC >> 5V
// SCL >> A5
// SDA >> A4
// GND >> GND
//////////////////
/*
 * 0 à 4 > 5 angles > ex: 5,45,90,135,175
 * 0 à 3 > 4 actions > avancer, reculer, gauche, droite
 * Mémorisations : 
 * - action avancer + secondes écoulées 
 * - action reculer ou gauche ou droite + angle 
 * - action reflexe code 5 (si test score non réussi)
 * - action détection arrière code 6
 * 
 */

//Par défaut, la voiture avance
//Si la voiture avance pendant 100 secondes, la durée est mémorisée
const unsigned char compteurMemoMax = 99;                   //Réglée à 99
bool stopMemo = 0;                                          //Utile dans la foncion score
bool seconde = 0;                                           //Pour le cycle d'enregistrement
bool stopEcriture = 0;

void cycleMemoAuto()
{                                                           //Mémorisation automatique toutes les 100 secondes
  if(f.compteurIntervalle >= compteurMemoMax && stopEcriture != 1)
  {
    memo.ecrire(199);                                       //199 
    stopEcriture = 1;                                       //Eviter de mémoriser plusieurs fois de suite!
  }else
  {
    stopEcriture = 0;
  } 
  stopMemo = 0;                                             //Utile dans la fonction score  
}

//memorisation du tps parcouru pour l'action avancer / MAX 100s
void memoInstantTAvancer(){
   int cctntnJ1 = f.concatenation(1,f.compteurIntervalle);
   memo.ecrire(cctntnJ1);//concatenation action + délai écoulé en cours sur les 100secondes
}

//memorisation de l'action qui évite l'obstacle + position du SVM
void memoInstantT(unsigned char actJ, unsigned char posSVM){
   int cctntnJ2 = f.concatenation(actJ,posSVM);
   memo.ecrire(cctntnJ2);
}

//RECUPERER LES ACTIONS QUI FONCTIONNENT LE MIEUX SUR LES 30 DERNIERES VALEURS
//Malloc et realloc pour l'allocation du tableau cas0 font crasher le microcontrôleur !
int cas0[30] = {255,255,255,255,255,
                255,255,255,255,255,
                255,255,255,255,255,
                255,255,255,255,255,
                255,255,255,255,255,
                255,255,255,255,255};

int occurrencesSCORE(int angleEnJauge){

  //Définir pointeurs sur une adresse de départ et une adresse d'arrivée
  memo.adresseEepromMin = 0;
  memo.adresseEepromMax = 0;
  memo.pointer(30);

  int lireDonnees = 0;
  int operationSplit = 0;
  int cas0compte = 0;      

  for(int lecture1 = memo.adresseEepromMin;lecture1 < memo.adresseEepromMax; lecture1++){ //compter le nombre d'occurrences pour chaque action   
    lireDonnees = memo.lire(lecture1);
    operationSplit = lireDonnees % 10; //récupérer le DERNIER chiffre => position svm
    if(lireDonnees >= 20 && lireDonnees <= 44){//filtrer entre codes alloués aux actions|positions
      if(operationSplit == angleEnJauge)
      {
        cas0[cas0compte] = lireDonnees; 
        cas0compte++;
      }      
    }
  }   

  //on capture l'action la plus fréquente par position
  int valeurFrequenteCas0 = 0;
  //var pour resultat split
  int actionplusfrequente0 = 0;

  if(cas0compte != 0){
    valeurFrequenteCas0 = f.plusFrequentExclusion(cas0,cas0compte,255);
    //i(valeurFrequenteCas0)
    actionplusfrequente0 = valeurFrequenteCas0 / 10;

    return actionplusfrequente0;
  }else{
    return NULL;
  }

}

#endif   
