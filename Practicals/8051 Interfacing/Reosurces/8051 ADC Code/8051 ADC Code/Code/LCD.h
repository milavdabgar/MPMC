#ifndef __LCD_H
#define __LCD_H

//*******************
//Pin description
/*
P1.4 to P1.7 is data bus
P1.1 is RS
P1.0 is E
*/
//********************

// Defines Pins
sbit RS = P1^1;
sbit E  = P1^0;

// Constants
#define E_Delay       250       

// Function Declarations
void delay_sec(unsigned int);
void __delay_us(unsigned int);	
void InitLCD(void);
void WriteCommandToLCD(int);
void WriteDataToLCD(char);
void WriteStringToLCD(const char*);
void ClearLCDScreen(void);

#endif