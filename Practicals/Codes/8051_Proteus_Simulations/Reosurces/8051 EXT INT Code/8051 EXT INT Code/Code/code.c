/*  Name     : code.c
 *  Purpose  : Main file for external pin (INT0) interrupt code for 8051.
 *  Author   : M.Saeed Yasin
 *  Date     : 15-06-12
 *  Revision : None
 */
#include<reg51.h>

// LED Pin
sbit LED = P1^0;		   // Pin P1.0 is named as LED

//Function declarations
void cct_init(void);
void InitINT0(void);

// Main function
void main(void)
{
   cct_init();   	// Make all ports zero
   InitINT0();      // Intialize INT0 interrupts
 
   while(1)
   {}
}

// Init CCT function
void cct_init(void)
{
	P0 = 0x00;    // Make all pins zero
	P1 = 0x00;    // Make all pins zero
	P2 = 0x00;    // Make all pins zero
	P3 = 0x04;    // Make P3.2 (INT0) pin high only
}

// External INT0 pin interrupt init function
void InitINT0(void)
{
	IT0 = 1;      //Edge triggered interrupt mode (Neg Edge)
	EX0 = 1;      //Enable external interrupt INT0
	EA  = 1;      //Enable global interrupts
}

// INT0 ISR
void external0_isr(void) interrupt 0     
{
	LED = ~LED;   // Toggle LED pin
} 
