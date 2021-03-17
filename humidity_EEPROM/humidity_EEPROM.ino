//////////////////
// 24LC256 >> ARDUINO
// WP | A0 | A1 | A2 >> GND 
// VCC >> 5V
// SCL >> A5
// SDA >> A4
// GND >> GND
//////////////////


#include <Wire.h>     //I2C library
//ENREGISTREMENTS DES VALEURS DHT22
#include <EEPROMTOOLS.h>
//LCD
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 20, 4);
//CAPTEUR
#include "DHT.h"   // Librairie des capteurs DHT
#define DHTPIN 2    // Changer le pin sur lequel est branché le DHT
#define DHTTYPE DHT22      // DHT 22  (AM2302)

int v = 0;
int search = 0;
int result = 0;
//const short int index[] = { 0, 32000};

DHT dht(DHTPIN, DHTTYPE); 

void setup() {

  lcd.init(); // initialisation de l'afficheur
  
  //LECTURE POUR TESTS
  Serial.begin(9600);

  // INITIALISATION
  Wire.begin();
  Wire.setClock(400000); //https://www.arduino.cc/en/Reference/WireSetClock

  dht.begin();

  //resetEEPROM(0,100);

}

void loop() {

   //RESET COMPTE A REBOURS
   if(v==10){v=0;}
   //ENREGISTREMENT TOUS LES 36000/2
   v = v+1;

   //Serial.print(v);
  
  // TESTS
   Serial.println(F("________________________"));
   Serial.println(readEEPROM(rom, 0), DEC);
   Serial.println(readEEPROM(rom, 1), DEC);
   Serial.println(readEEPROM(rom, 2), DEC);
   Serial.println(readEEPROM(rom, 3), DEC);
   Serial.println(readEEPROM(rom, 4), DEC);
   Serial.println(readEEPROM(rom, 5), DEC);
   Serial.println(readEEPROM(rom, 6), DEC);
   Serial.println(readEEPROM(rom, 7), DEC);
   Serial.println(readEEPROM(rom, 8), DEC);
   Serial.println(readEEPROM(rom, 9), DEC);
   Serial.println(readEEPROM(rom, 10), DEC);
   Serial.println(F("________________________"));

  //CAPTEUR DDHT22
  // Délai de 2 secondes entre chaque mesure. La lecture prend 250 millisecondes
  delay(2000);

  // Lecture du taux d'humidité
  float h = dht.readHumidity();
  int hum = round(h); //retirer la décimale pour enregistrement
  // Lecture de la température en Celcius
  float t = dht.readTemperature();
  int temp = round(t); //retirer la décimale pour enregistrement
  // Pour lire la température en Fahrenheit
  float f = dht.readTemperature(true);
  
  // Stop le programme et renvoie un message d'erreur si le capteur ne renvoie aucune mesure
  if (isnan(h) || isnan(t) || isnan(f)) {
    //Serial.println("Echec de lecture !");
     lcd.backlight();
     // Envoi du message
     lcd.setCursor(0, 0);
     lcd.print("Echec de lecture !");   
    return;
  }

  // Calcul la température ressentie. Il calcul est effectué à partir de la température en Fahrenheit
  // On fait la conversion en Celcius dans la foulée
  float hi = dht.computeHeatIndex(f, h);
  
   // AFFICHAGE
   lcd.backlight();
   // Envoi du message
   lcd.setCursor(0, 0);
   lcd.print(" Hum: ");
   lcd.print(h);
   lcd.print("%");
   lcd.setCursor(0,1);
   lcd.print(" Temp: ");
   lcd.print(t);
   lcd.print("*C");
   
   /**Serial.print("Humidite: "); 
  Serial.print(h);
  Serial.print(" %\t");
  Serial.print("Temperature: "); 
  Serial.print(t);
  Serial.print(" *C ");
  Serial.print("Temperature ressentie: ");
  Serial.print(dht.convertFtoC(hi));
  Serial.println(" *C");**/

     //
   if(v==5){
      Serial.println("Enregistrement!");
      for(int i = 0;i<=32000;i++){ //32700
        search = readEEPROM(rom, i), DEC; 
        if(search!=255){
            result = i+1;
        }
      }
      //Serial.println(result);
      writeEEPROM(rom, result, hum);  //
   }

}
