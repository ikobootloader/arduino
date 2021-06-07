#ifndef SCORE_H
#define SCORE_H

int reaction = false; //si "true" action a fonctionné pour contourner l'obstacle 
int matriceSCORE[5][4][2] = {{{1,0},{2,0},{3,0},{4,0}}, //0°
                            {{1,0},{2,0},{3,0},{4,0}},  //45°
                            {{1,0},{2,0},{3,0},{4,0}},  //90°
                            {{1,0},{2,0},{3,0},{4,0}},  //135°
                            {{1,0},{2,0},{3,0},{4,0}}}; //180°

int progressif(int actP)
{ //protection contre collision lors des tests de mouvement
  if(actP == 0 || actP == 1){
      unsigned int prdtCrx = 0;      
      ultrason.measureDistanceCm() == -1 ? prdtCrx = 0 : prdtCrx = ultrason.measureDistanceCm();
      prdtCrx = map(prdtCrx,0,20,0,100);//ajout le 18/05/2021
      if(prdtCrx <= 20){
        VOITURE.locomotion(actP,255),delay(prdtCrx);   
      }else{
        VOITURE.locomotion(actP,255),delay(150);//150 au 16/04/21
      }
  }
  if(ultrason.measureDistanceCm() >= maxDistance/2){
    if(actP == 2 || actP == 3){
      VOITURE.locomotion(actP,255),delay(300);  
    }
  }
}

//RECHERCHER ACTION CORRESPONDANTE
int actionTrouvee(int reference)
{ //progressif(reference-1);//Simplifiation : -1 pour correspondance avec numérotation de VOITURE.locomotion()
  switch (reference)
  {
  case 1:    //avant;
    i("TEST AVANT!")
    progressif(0);       
    break;
  case 2:    //arriere;
    i("TEST ARRIERE!")
    progressif(1);
    break;
  case 3:    //droite;
    i("TEST GAUCHE!")
    progressif(2);
    break;
  case 4:    //gauche;
    i("TEST DROIT!")
    progressif(3);
    break;
  }
}

//Recomposer matriceSCORE
void recompositionMatrice(int pSVM, int boucle){

  unsigned char valeurHaute1 = 0;
  unsigned char valeurHaute2 = 0;
  unsigned char valeurHaute3 = 0;  
  
  for(unsigned char f = 0; f <= 3;f++){
    if(matriceSCORE[pSVM][f][1] == 3 && f != boucle){
      matriceSCORE[pSVM][f][1] = 2;
      valeurHaute2 = f;
    }
  }  
  for(unsigned char g = 0; g <= 3;g++){
    if(matriceSCORE[pSVM][g][1] == 2 && g != valeurHaute2){
      matriceSCORE[pSVM][g][1] = 1;
      valeurHaute3 = g;
    }
  }
  for(unsigned char hh = 0; hh <= 3;hh++){
    if(matriceSCORE[pSVM][hh][1] == 1){
      valeurHaute1++;
    }
  }
  for(unsigned char h = 0; h <= 3;h++){
    if(matriceSCORE[pSVM][h][1] == 1){
      if(h != valeurHaute3 && valeurHaute1 != 1){
         matriceSCORE[pSVM][h][1] = 0;                   
      }
    }
  }         
  
}

//Vérification en mémoire de la valeur récurrente pour la position en cours de balayage
int souvenirAction = 0;
void souvenirScore(int pstnSVM){
   souvenirAction = occurrencesSCORE(pstnSVM);//VERIFICATION EEPROM
   //l'action la plus fréquente pour un type de position est présumée être la meilleure ! 
   //modification des valeurs dans matriceSCORE en conséquence
   bool pasDeChangement = 0;
   unsigned char valeurHaute = 0;
    if(souvenirAction != 0){
      //Vérifier correspondance matriceSCORE et mémoire
      //Si la correspondance existe sur le score le plus haut, alors on ne modifie pas la matriceSCORE
      for(int k = 0; k <= 3; k++){
        if(matriceSCORE[pstnSVM][k][0] == souvenirAction && matriceSCORE[pstnSVM][k][1] == 3){
          pasDeChangement = 1;
        }
      }
      //Modifier la matriceSCORE en fonction du résultat de occurrencesSCORE(pstnSVM)
      if(pasDeChangement == 0){
        for(int chercheP = 0; chercheP <= 3; chercheP++){
          if(matriceSCORE[pstnSVM][chercheP][0] == souvenirAction){
            valeurHaute = chercheP;
            matriceSCORE[pstnSVM][chercheP][1] = 3;
          }
        } 

        //Recomposer matriceSCORE
        recompositionMatrice(pstnSVM,valeurHaute);       
      }      
    }  
}

//SCORE
int actPrinc = 0;
void score(int positionSM){

  // mémorisation action AVANCER + quantité de secondes a l'instant où détection d'obstacle
  if(stopMemo != 1){memoInstantTAvancer();} 
  
  // VARIABLES DE SCORE
  actPrinc = 0;  
  reaction = false;

  //Respecter classement
  bool pasDeChangement3 = 0;
  bool pasDeChangement4 = 0;
  unsigned char valeurHaute0 = 0;

   ARRET,delay(500);//ARRET ROUES 

    //JAUGE
    for(int seq = 3; seq >= 0; seq--){//Points
      for(int chkJ = 0; chkJ <= 3; chkJ++){//Actions
        if(matriceSCORE[positionSM][chkJ][1] == seq && reaction == false && matriceSCORE[positionSM][chkJ][0] != actPrinc){

            actionTrouvee(matriceSCORE[positionSM][chkJ][0]);//action en test!          
            //i(actPrinc)
            ARRET,delay(500);//ARRET ROUES 
            if(ultrason.measureDistanceCm() > maxDistance){ //si distance sup à limite fixée 

              for(unsigned char e = 0; e <= 3;e++)
              {//Vérifier si l'action possède déjà un score à 3
                if(matriceSCORE[positionSM][e][1] == 3){
                  valeurHaute0 = e;
                }
              }
                
              matriceSCORE[positionSM][chkJ][1] = 3; //i("ACTION PRINCIPALE A FONCTIONNE")  
                                    
              // mémorisation action + position SVM
              if(matriceSCORE[positionSM][chkJ][0] != 1){//si différent de l'action avancer
                memoInstantT(matriceSCORE[positionSM][chkJ][0],positionSM); // ORIGINE DU BUG ???               
              }  
                  
              //Recomposer matriceSCORE
              //Ne pas checker si même action est répéter pour éviter l'obstacle !!
              if(chkJ != valeurHaute0)
              {//Si l'action qui évite l'obstacle est différente de celle qui possède un score à 3
                recompositionMatrice(positionSM,chkJ);
              }
                            
              reaction = true;
            }else{ 
              reaction = false;
              actPrinc = matriceSCORE[positionSM][chkJ][0];//conserver la valeur de l'action principale pour ne pas la retester, du moins 1er          
            } 
         }
      }
    }    
    
    //SI AUCUNE SOLUTION TROUVEE
    if(reaction == false){//A L ISSU DES TESTS PRECEDENTS
      //i("RIEN A FONCTIONNE")
      //Cheat Code!! => reflexe !
      for(unsigned char prg = 0;prg <= 250;prg++){//en test prise en compte recul
        if(digitalRead(infra) == true){
         RECULER,delay(1);            
        }
      }
      
      GAUCHE,delay(300);
      ARRET,delay(500);   
      memo.ecrire(5);// Mémorisation de l'échec du test 
    } 

    //reset compteur mémorisation auto
    f.compteurIntervalle = 0;
    stopMemo = 1;
    
}

//VERIFICATION DU SCORE
void verificationScore(int pos){
  switch (pos)
  {
  case 0:    //avant;
    i("0°") 
    break;
  case 1:    //arriere;
    i("45°")
    break;
  case 2:    //droite;
    i("90°")
    break;
  case 3:    //gauche;
    i("135°")
    break;
  case 4:    //gauche;
    i("180°")
    break;   
  default:    //arret
    //
    break;
  } 
  Serial.println(F("________________________"));
  for(int test = 0;test <= 3;test++){i(matriceSCORE[pos][test][1])}  
  Serial.println(F("________________________"));    
}

#endif
