#ifndef LED_H
#define LED_H

/*
 * 
 * VERT = OK
 * ROUGE = OBSTACLE
 * JAUNE = PARCOURS/ROUTINE
 * 
 */

void allumerRouge(){
 digitalWrite(A3, HIGH);//ROUGE 
}

void eteindreRouge(){
 digitalWrite(A3, LOW);//ROUGE   
}

void allumerVert(){
 digitalWrite(11, HIGH);//VERT
}

void eteindreVert(){
 digitalWrite(11, LOW);//VERT
}

void allumerJaune(){
 digitalWrite(8, HIGH);//JAUNE
}

void eteindreJaune(){
 digitalWrite(8, LOW);//JAUNE
}


#endif
