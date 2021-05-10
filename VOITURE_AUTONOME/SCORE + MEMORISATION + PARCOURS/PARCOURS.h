#ifndef PARCOURS_H
#define PARCOURS_H
//PARCOURS
/*
 * SI x DERNIERES ACTIONS RESSEMBLENT A UNE SEQUENCE D'UN PARCOURS 
 * LE ROBOT EXECUTE CETTE SEQUENCE DU PARCOURS 
 */

//Init
int tabParcours[10] = {0,0,0,0,0,
                       0,0,0,0,0}; //définir limite max parcours
int tabqDAtP[3] = {0,0,0}; //Récupére les 3 dernières données qui devront être comparées

bool memoParcours(){//Renvoie true si parcours détecté

  //Init variables  
  unsigned char incrPrcrs = 0;
  int lireDernieresDonnees = 0;
  int varAddPcrs = 0;

  //Définir pointeurs sur adresses début et fin à traiter
  //Définir pointeurs sur une adresse de départ et une adresse d'arrivée
  memo.adresseEepromMin = 0;
  memo.adresseEepromMax = 0;
  memo.pointer(10);//quantité de données récupérée dans la mémoire

  //Enregistrer x dernières valeurs de l'eeprom dans tabParcours[]
  incrPrcrs = 0;
  for(int lecture3 = memo.adresseEepromMin;lecture3 <= memo.adresseEepromMax; lecture3++){
    lireDernieresDonnees = memo.lire(lecture3); 
    if(lireDernieresDonnees != 255){
      tabParcours[incrPrcrs] = lireDernieresDonnees; //enregistrement des 10 valeurs eeprom dans tableau
      incrPrcrs++;     
    }
  }

  //CHERCHER MOTIFS DE PARCOURS
   //enregistrer dernières valeurs
   tabqDAtP[0] = tabParcours[7];
   tabqDAtP[1] = tabParcours[8];
   tabqDAtP[2] = tabParcours[9];

  //boucle comparaison tabqDAtP[] (3 valeurs) & tabParcours[] (3 premières valeurs)
  varAddPcrs = 0;
  for(int lecture4 = 0; lecture4 <= 2; lecture4++){
    if(tabqDAtP[lecture4] == tabParcours[lecture4] && tabParcours[varAddPcrs] != 0){//vérification des correspondances
      varAddPcrs++;
    } 
  }
  //si varAddPcrs == 3 alors renvoie true 
  if(varAddPcrs == 3){
    //i("motif detecte")
    return true;
  }else{
    return false;
  }
  
}

void contenutabParcours(){
  //Vérification du tableau tabParcours pour les tests
  for(int zx = 0;zx <= 9;zx++){
    i("tabParcours")
     i(zx)
    i(tabParcours[zx])
  }
  
}

/*
 * 
 * si memoParcours() retourne true : 
 * => executer parcours contenu dans tabParcours[] 
 * => enregistrer dans memoire à chaque passage d'une valeur de tabParcours[]
 * => si obstacle, cette fonction devrait stopper. les autres fonctions reprennent le relai
 * 
 */ 

//Minuterie
unsigned long trm = 0;
bool minuterie(unsigned long terme)
{//Créer une fréquence
  if(millis() - trm >= terme) {
    trm = millis();
    return true;//
  }else{
    return false; 
  }
}

long int ntvrl = 0;//compteur

void ntvrlPrcrs(int freq2, int up)
{//Créer un intervalle de temps à partir de la fonction f.frequence()
  if(freq2 == 1)
    ntvrl++;
}


//executer parcours contenu dans tabParcours[] à partir de tabParcours[3] et reboucler à partir de tabParcours[3]
//+ enregistrer dans memoire à chaque passage d'une valeur de tabParcours[]
int cmptrExecution = 3; //Compteur prend 1 à chaque loop
unsigned long couperNombre = 0;
bool tempoParcours = 0;

void executionParcours(){

  //Init 
  bool memoParcoursBool = memoParcours();
  
  if(memoParcoursBool == true){ //Si détection du parcours  

    f.compteurIntervalle = 0;//reset compteur de l'enregistrement auto toutes les 199 secondes
  
     unsigned char parcoursEtape = tabParcours[cmptrExecution];    
     int calculPrcrs = parcoursEtape / 10;    
     couperNombre = 0;
     /*
     split le résultat de tabParcours[cmptrExecution]
     fixer le temps à partir des infos avec millis()
     Enregistrer l'action si pas d'obstacle
    //split action:
    //10 à 19 ET 110 à 199 => avancer + tps en seconde
    //20 à 24 | 30 à 34 | 40 à 44 => action + angle => delay(250)
     */  
     
     //Moulinette de décomposition des données EEPROM 
     if(parcoursEtape >= 10 && parcoursEtape <= 19){
        couperNombre = (parcoursEtape % 10) + 1; //+1 car 0 à 99 pour 100s
        AVANCER;
      }else if(parcoursEtape >= 110 && parcoursEtape <= 199){      
        couperNombre = (parcoursEtape % 100) + 1; //+1 car 0 à 99 pour 100s  
        AVANCER;
      }else if(calculPrcrs >= 2 && calculPrcrs <= 4){
        couperNombre = 1;
        VOITURE.locomotion(calculPrcrs,255);
      }else if(calculPrcrs == 5){//Réfléchir sur l'intérêt de réaliser le réflexe ???
        couperNombre = 0;//Pas d'assignation de temps ! les delay s'en chargent     
        RECULER,delay(500);
        GAUCHE,delay(200);
        ARRET,delay(500);
      }  
  
      tempoParcours = minuterie(1000); //tempoParcours est à true > on change d'étape
      ntvrlPrcrs(tempoParcours,couperNombre);//+1 à ntvrl
  
      if(ntvrl >= couperNombre){//les durées ne seront pas parfaitement respectées !!
        trm = 0;
        ntvrl = 0; //reset compteur intervalle
        memo.ecrire(parcoursEtape);//Enregistrement EEPROM au terme du délai
        cmptrExecution++; //Lorsque le temps du mouvement est écoulé, on passe à l'action suivante
      }
      //on sort de la fonction si un obstacle est détecté 
      //je pense que le passage à la fonction score() suffira à changer l'état de la fonction memoParcours() en false
      if(cmptrExecution == 9){cmptrExecution = 3;}//Reset du compteur 

  }

}

#endif  
