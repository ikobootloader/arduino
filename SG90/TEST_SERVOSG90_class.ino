//SERVO
#include <Servomoteur.h>

//SIMPLIFICATION DE L'UTILISATION DU PORT SERIE
#define iSet     Serial.begin(9600);
#define i(texte) Serial.println(texte);


#define amplitude servo.amplitude

/*
 * Un objet créé à partir de la bibliothèque Servo se nomme servomoteur
 * A partir de cet objet, il est possble d'utiliser toutes les méthodes
 * proposées par la bibliothèque Servo : https://www.arduino.cc/reference/en/libraries/servo/
 * Attention à ne pas confondre...
 */

//Class       Ojbet
SERVOMOTEUR   servo;


void setup() {

  iSet
  servo.setupServo();
 
}
 
void loop(){

  //Initialiser l'oscillateur en déinissant une vitesse (obligatoire!)
  //servo.oscillateur(500);
  
  //Activer le balayage du servomoteur 
  //servo.balayage(amplitude); //ou// servo.balayage(servo.amplitude);

  //Initialisation des angles par l'utilisateur (Toujours 5 entrées!)
  //sinon lecteur des angles par défaut : 5,45,90,135,175
  //servo.angles(0,100,120,140,170);

  //TEST
  //i(servo.oscillateur(1000))

  servo.oscillateur(1000);
  servo.balayage(amplitude);

}
