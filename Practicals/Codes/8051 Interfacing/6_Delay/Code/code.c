/*  Name     : code.c
 *  Purpose  : Main file for using timer0 to generate delay in 8051.
 *  Author   : M.Saeed Yasin
 *  Date     : 14-06-12
 *  Revision : None
 */
#include<reg51.h>

// Out Pin
sbit Out = P2^0;		   // Pin P2.0 is named as Out

//Function declarations
void cct_init(void);
void delay_usec(unsigned int);

// Global Variables
unsigned char TimeUp = 0;  // variable used to generate delay

// Main function
int main(void)
{
   cct_init();   	       // Make all ports zero
 
   while(1)                // Rest is done in Timer0 interrupt
   {
   		Out = 1;		   // Make out pin high
		delay_usec(1000);  // Generate a delay of 1000 usec
		Out = 0;		   // Make out pin low
		delay_usec(1000);  // Generate a delay of 1000 usec
   }
}

// Circuit Initialize function
void cct_init(void)
{
	P0 = 0x00;   
	P1 = 0x00;   
	P2 = 0x00;   
	P3 = 0x00;  
}

// Delay function, it generates delay in micro seconds
void delay_usec(unsigned int d)   // d can have a value from 0 to 65535 only.
{
	TMOD &= 0xF0;    // Clear 4bit field for timer0
	TMOD |= 0x01;    // Set timer0 in mode 1 = 16bit mode
	
	TH0  = (0xFF - (d>>8)&0xFF);	// Load timer0 registers with 
	TL0  = (0xFF - d&0xFF) + 0x26;		// delay value							   
	
	ET0 = 1;         // Enable Timer0 interrupts
	EA  = 1;         // Global interrupt enable
	
	TimeUp = 0;      // When timer expires then this variable will become 1

	TR0 = 1;         // Start Timer 0

	while(!TimeUp);  // Wait for timeup

	TR0 = 0;         // Done
}

// Timer0 ISR function
void Timer0_ISR (void) interrupt 1   // It is called after every 250usec
{
	TimeUp = 1;  // Make TimeUp variable 1 to indicate timer0 overflow
	TF0 = 0;     // Clear the interrupt flag
}

