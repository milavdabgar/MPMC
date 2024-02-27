#ifndef __LCD_H
#define __LCD_H

//*******************
//Pin description
/*
P2.4 to P2.7 is data bus
P1.0 is RS
P1.1 is E
*/
//********************

// Defines Pins
sbit RS = P1^0;
sbit E  = P1^1;

// Constants
#define E_Delay       250       

// Function Declarations
void InitLCD(void);
void WriteCommandToLCD(int);
void WriteDataToLCD(char);

#endif