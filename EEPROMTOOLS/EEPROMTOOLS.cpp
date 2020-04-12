/**********************************************************************************************
 * Arduino EEPROM 24LC256 TOOLS - Version 1.2
 * by ikobootloader
 *
 * License to define..
 **********************************************************************************************/

#include <Arduino.h>
#include <Wire.h>
#include "EEPROMTOOLS.h"

// WITH HELP FROM https://www.hobbytronics.co.uk/arduino-external-eeprom
//////////////////
// 24LC256 >> ARDUINO
// WP | A0 | A1 | A2 >> GND 
// VCC >> 5V
// SCL >> A5
// SDA >> A4
// GND >> GND
//////////////////

#define rom 0x50    //Address of 24LC256 eeprom chip

///////////////////     ARRAY     /////////////////////

// CREATE AN ARRAY 1D
// arrVal(address to start, address to end)
int arrVal(int a, int b){
  int *t =  malloc(b - a);
  int ct, v = 0;
  for(short int i = a; i <= b; i++){
    v = readEEPROM(rom, i), DEC;
    t[ct++] = v;
  }
  return t;
}

// ARRAY SIZE
#define SIZE_ARR(arr) (sizeof((arr))/sizeof(((arr)[0])))

// FIND MIN
// mini(array,size of array)
int mini(int *t,int n){
  int o = *t;
  while(--n)
    if(*(++t) < o) o = *t;
  return o;
}

// FIND MAX
// maxi(array,size of array)
int maxi(int *t,int n){
  int o = *t;
  while(--n)
    if(*(++t) > o) o = *t;
  return o;
}

// SORT ASCENDING
// sortAsc(array,size of array)
int sortAsc(int t[], int s){     
	 int x, y, z;
     for (y=0; y<s; y++)    
        for(z=y; z<s; z++)
            if(t[z]<t[y]){
                x = t[y]; t[y] = t[z]; t[z] = x;
            }
}

// SORT DESCENDING
// sortDesc(array,size of array)
int sortDesc(int t[], int s){     
	 int x, y, z;
     for (y=0; y<s; y++)    
        for(z=y; z<s; z++)
            if(t[z]>t[y]){ x = t[y]; t[y] = t[z]; t[z] = x; }
}

// REVERSE ARRAY
// rev(array,size of array)
void rev(int t[], int x){
  int y[x];
  for (int i = 0; i < x; i++) y[x - 1 - i] = t[i];
  for (int i = 0; i < x; i++) t[i] = y[i];
}

///////////////////     MATRIX     /////////////////////

// CREATE A MATRIX 2D
// int tab[n][n]
// matrix2D(address to start, address to end, size of array)
int matrix2D(int a, int b, int c){
    int n = 2;
    int m = c;
    int **t;
    t = malloc(sizeof(int*)*n);
    for(int i=0;i<n;i++){
      t[i] = malloc(sizeof(int)*m);
    }  
    int ct1, ct2, v = 0;
    for(short int j = a; j <= b ;j++){
      v = readEEPROM(rom, j), DEC;
      t[0][ct1++] = j;
      t[1][ct2++] = v;
    }   
    return t;
}

///////////////////     SEARCHING DATAS     /////////////////////

// KNOW IF SAME VALUE IS STRICTLY PRESENT IN X ADDRESSES
// addSmVal(value to find, address to start, address to end)
// return 0 or 1
int addSmVal(int a, int b, int c){
  int c1, c2, s, booleen = 0;
  for(short int i = b; i <= c ;i++){
      s = readEEPROM(rom, i), DEC;
      c1++;
      if(s == a){c2++;}
	}
   if(c1 == c2){booleen = 1;}
   return booleen;  
}

// COUNT OCCURRENCES
// occ(value to find, address to start, address to end)
int occ(int a, int b, int c){
  int s, c1 = 0;
  for(short int i = b; i <= c ;i++){
      s = readEEPROM(rom, i), DEC;
      if(s == a){c1++;}
    }
    return c1;  
}

// FIND AN ADDRESS BY A VALUE
// but several addresses may have the same value. It brings the last one.
// AddVal(value to find, address to start, address to end)
int AddVal(int a, int b, int c){
  int s, r = 0;
  for(short int i = b; i <= c ;i++){
      s = readEEPROM(rom, i), DEC;
      if(s == a){r = i;}
    }
   return r;
}

// FIND ADRESSES WITH THE SAME VALUE
// function create an array
// seqMmVal(value to find, address to start, address to end)
int *seqMmVal(int a, int b, int c){
  int s, c1, c2 = 0; 
  for(short int i = b; i <= c ;i++){
      s = readEEPROM(rom, i), DEC;
      if(s == a){c1++;}
    }
  s = 0;
  int *r = malloc(c1);
  for(short int i = b; i <= c ;i++){
      s = readEEPROM(rom, i), DEC;
      if(s == a){r[c2++] = i;}
    }
    return r; 
}

///////////////////     BASES     /////////////////////

// RESET EEPROM
// 24LC256 >> 32767 addresses
void resetEEPROM(int x, int y){
  for(short int r = x; r <= y ;r++) writeEEPROM(rom,r,255);
}

// ECRIRE/WRITE
void writeEEPROM(int deviceaddress, unsigned int eeaddress, byte data ) 
{
  Wire.beginTransmission(deviceaddress);
  Wire.write((int)(eeaddress >> 8));   // MSB
  Wire.write((int)(eeaddress & 0xFF)); // LSB
  Wire.write(data);
  Wire.endTransmission();
 
  delay(5);
}

// LIRE/READ
byte readEEPROM(int deviceaddress, unsigned int eeaddress ) 
{
  byte rdata = 0xFF;
 
  Wire.beginTransmission(deviceaddress);
  Wire.write((int)(eeaddress >> 8));   // MSB
  Wire.write((int)(eeaddress & 0xFF)); // LSB
  Wire.endTransmission();
 
  Wire.requestFrom(deviceaddress,1);
 
  if (Wire.available()) rdata = Wire.read();
 
  return rdata;
}
////////////////////////////////////////////////////////////