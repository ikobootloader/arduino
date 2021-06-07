#ifndef INFRAROUGE_H
#define INFRAROUGE_H

const unsigned char infra = A1;
//0 = mur

//Si détection arrière, renvoie true
int detectionArriere(){
  int valeurIF = digitalRead(infra);
  if(valeurIF == 0){
    return true;
  }else{
    return false;
  }
}

#endif
