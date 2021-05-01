#ifndef SCORE_H
#define SCORE_H

int reaction = false; //si "true" action a fonctionné pour contourner l'obstacle 
int matriceSCORE[5][4][2] = {{{1,1},{2,0},{3,0},{4,0}}, //0°
                            {{1,1},{2,0},{3,0},{4,0}},  //45°
                            {{1,1},{2,0},{3,0},{4,0}},  //90°
                            {{1,1},{2,0},{3,0},{4,0}},  //135°
                            {{1,1},{2,0},{3,0},{4,0}}};  //180°

int progressif(int actP){ //protection contre collision lors des tests de mouvement
  if(ultrason.measureDistanceCm() >= maxDistance/3){//TODO: tester fonction map pour delai / maxDistance
    if(actP == 0 || actP == 1){
      VOITURE.locomotion(actP,255),delay(150);  //100 de base au 16/04 
    }else if(actP == 2 || actP == 3){
      VOITURE.locomotion(actP,255),delay(250);  
    }
  }
}
//RECHERCHER ACTION CORRESPONDANTE
int actionTrouvee(int reference){
  //progressif(reference-1);//Simplifiation : -1 pour correspondance avec numérotation de VOITURE.locomotion()
  switch (reference)
  {
  case 1:    //avant;
    Serial.println("TEST AVANT!");
      progressif(0);       
    break;
  case 2:    //arriere;
    Serial.println("TEST ARRIERE!");
    progressif(1);
    break;
  case 3:    //droite;
    Serial.println("TEST GAUCHE!");
    progressif(2);
    break;
  case 4:    //gauche;
    Serial.println("TEST DROIT!");
    progressif(3);
    break;
  }
}

//SCORE
void score(int positionSM){
   // VARIABLES DE JAUGE
  int actPrinc = 0;  
  reaction = false;

   ARRET,delay(500);//ARRET ROUES 

    //JAUGE
    for(int seq = 1; seq >= 0; seq--){
      for(int chkJ = 0; chkJ <= 3; chkJ++){
        if(matriceSCORE[positionSM][chkJ][1] == seq && reaction == false && matriceSCORE[positionSM][chkJ][0] != actPrinc){
            actionTrouvee(matriceSCORE[positionSM][chkJ][0]);//action!          
            //i(actPrinc)
            ARRET,delay(500);//ARRET ROUES 
            if(ultrason.measureDistanceCm() > maxDistance){ //si distance sup ou égal à limite fixée        
              matriceSCORE[positionSM][chkJ][1] = 1; //i("ACTION PRINCIPALE A FONCTIONNE")              
              reaction = true;
            } else{ //si distance sup ou égal à limite fixée         
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
    } 

}

//VERIFICATION DE LA JAUGE
void verificationScore(int pos){
  switch (pos)
  {
  case 0:    //avant;
    Serial.println("0°");    
    break;
  case 1:    //arriere;
    Serial.println("45°");
    break;
  case 2:    //droite;
    Serial.println("90°");
    break;
  case 3:    //gauche;
    Serial.println("135°");
    break;
  case 4:    //gauche;
    Serial.println("180°");
    break;   
  default:    //arret
    //
    break;
  } 
  Serial.println(F("________________________"));
  for(int test = 0;test <= 3;test++){Serial.println(matriceSCORE[pos][test][1]);}  
  Serial.println(F("________________________"));    
}

#endif
