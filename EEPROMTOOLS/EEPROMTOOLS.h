#pragma once

#define rom 0x50

// ARRAY
int arrVal(int a, int b);
#define SIZE_ARR(arr) (sizeof((arr))/sizeof(((arr)[0])))
int mini(int *t,int n);
int maxi(int *t,int n);
int sortAsc(int t[], int s);
int sortDesc(int t[], int s);
void rev(int t[], int x);

// MATRIX
int matrix2D(int a, int b, int c);

// SEARCH
int addSmVal(int a, int b, int c);
int occ(int a, int b, int c);
int AddVal(int a, int b, int c);
int *seqMmVal(int a, int b, int c);

// EEPROM SET
void resetEEPROM(int x, int y);
void writeEEPROM(int deviceaddress, unsigned int eeaddress, byte data );
byte readEEPROM(int deviceaddress, unsigned int eeaddress );
