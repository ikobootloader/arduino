<h1>Nomenclature Servomoteur SG90</h1>

//Class       Ojbet<br>
SERVOMOTEUR   servo;<br>
<br>
//Simplification de l'utilisation de la méthode (non obligatoire)<br>
#define amplitude servo.amplitude<br>
<br>
  //Setup<br>
  servo.setupServo(0);<br>
  <br>
  //Initialiser l'oscillateur en déinissant une vitesse (obligatoire!)<br>
  //servo.oscillateur(500);<br>
  <br>
  //Activer le balayage du servomoteur <br>
  //servo.balayage(amplitude); //ou// servo.balayage(servo.amplitude);<br>
<br>
  //Initialisation des angles par l'utilisateur (Toujours 5 entrées!)<br>
  //sinon lecteur des angles par défaut : 5,45,90,135,175<br>
  //servo.angles(0,100,120,140,170);<br>
<br>
  //TEST<br>
  i(servo.oscillateur(1000))<br>
<br>
  //servo.oscillateur(1000);<br>
  servo.balayage(amplitude);<br>
  <br>
  
  