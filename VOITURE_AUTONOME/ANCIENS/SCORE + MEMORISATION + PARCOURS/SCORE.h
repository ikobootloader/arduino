#ifndef SCORE_H
#define SCORE_H

int reaction = false; //si "true" action a fonctionné pour contourner l'obstacle 
int matriceSCORE[5][4][2] = {{{1,1},{2,0},{3,0},{4,0}}, //0°
                            {{1,1},{2,0},{3,0},{4,0}},  //45°
                            {{1,1},{2,0},{3,0},{4,0}},  //90°
                            {{1,1},{2,0},{3,0},{4,0}},  //135°
                            {{1,1},{2,0},{3,0},{4,0}}}; //180°

int progressif(int actP)
{ //protection contre collision lors des tests de mouvement
  if(ultrason.measureDistanceCm() >= maxDistance/3){//TODO: tester fonction map pour delai / maxDistance
    if(actP == 0 || actP == 1){
      VOITURE.locomotion(actP,255),delay(150);  //100 de base au 16/04 
    }else if(actP == 2 || actP == 3){
      VOITURE.locomotion(actP,255),delay(250);  
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

//Vérification en mémoire de la valeur récurrente pour la position en cours de balayage
int souvenirAction = 0;
void souvenirScore(int pstnSVM){
   souvenirAction = occurrencesSCORE(pstnSVM);
   //VERIFICATION EEPROM
   //l'action la plus fréquente pour un type de position est présumée être la meilleure ! 
   //changer les valeurs dans matriceSCORE en conséquence
    if(souvenirAction != 0){
      for(int chercheP = 0; chercheP <= 3; chercheP++){
        if(matriceSCORE[pstnSVM][chercheP][0] == souvenirAction){
          matriceSCORE[pstnSVM][chercheP][1] = 1;
        }else{
          matriceSCORE[pstnSVM][chercheP][1] = 0;
        }
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

   ARRET,delay(500);//ARRET ROUES 

    //JAUGE
    for(int seq = 1; seq >= 0; seq--){
      for(int chkJ = 0; chkJ <= 3; chkJ++){
        if(matriceSCORE[positionSM][chkJ][1] == seq && reaction == false && matriceSCORE[positionSM][chkJ][0] != actPrinc){
            actionTrouvee(matriceSCORE[positionSM][chkJ][0]);//action!          
            //i(actPrinc)
            ARRET,delay(500);//ARRET ROUES 
            if(ultrason.measureDistanceCm() > maxDistance){ //si distance sup à limite fixée        
              matriceSCORE[positionSM][chkJ][1] = 1; //i("ACTION PRINCIPALE A FONCTIONNE")      
              // mémorisation action + position SVM
              if(matriceSCORE[positionSM][chkJ][0] != 1){//si différent de l'action avancer
                memoInstantT(matriceSCORE[positionSM][chkJ][0],positionSM); // ORIGINE DU BUG ???               
              }                      
              reaction = true;
            } else{ //si distance inf à limite fixée         
              matriceSCORE[positionSM][chkJ][1] = 0;//-1 action antérieur //i("ACTION PRINCIPALE N'A PAS FONCTIONNE")
              reaction = false;
              if(seq == 1){
                actPrinc = matriceSCORE[positionSM][chkJ][0];//conserver la valeur de l'action principale pour ne pas la retester, du moins 1er
                //i(actPrinc)
              }             
            } 
         }
      }
    }    
    
    //ATTENTION : SI AUCUNE SOLUTION TROUVEE TOUTES LES VALEURS SONT A 0 DANS matriceSCORE !!!
    if(reaction == false){//A L ISSU DES TESTS PRECEDENTS
      //i("RIEN A FONCTIONNE")
      //Cheat Code!! => reflexe !     
      RECULER,delay(500);
      GAUCHE,delay(200);
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
