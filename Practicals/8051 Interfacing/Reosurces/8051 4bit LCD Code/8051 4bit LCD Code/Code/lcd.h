#ifndef _LCD_H
#define _LCD_H
// ***********************************************************
// Project:   LCD 4bit
// Author:    M.Saeed Yasin
// Module description:  Operate LCD in 4bit mode
// ***********************************************************

#include<reg51.h>

//Function declarations
void cct_init(void);
void lcdinit(void);
void writecmd(int);
void writedata(char);
void ReturnHome(void);

//*******************
//Pin description
/*
P2.4 to P2.7 is data bus
P1.0 is RS
P1.1 is E
*/
//********************

// Defines Pins
sbit RS = P2^2;//P1^0;
sbit E  = P2^3;//P1^1;

#endif