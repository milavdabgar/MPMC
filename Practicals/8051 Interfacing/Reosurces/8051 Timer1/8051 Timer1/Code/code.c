/*  Name     : code.c
 *  Purpose  : Main file for using timer1 of 8051.
 *  Author   : M.Saeed Yasin
 *  Date     : 08-06-12
 *  Revision : None
 */
#include<reg51.h>

// Out Pin
sbit Out = P2^0;		   // Pin P2.0 is named as Out

//Function declarations
void cct_init(void);
void InitTimer1(void);


int main(void)
{
   cct_init();   	       // Make all ports zero
   InitTimer1();           // Start Timer1
 
   while(1)                // Rest is done in Timer1 interrupt
   {
   }
}

void cct_init(void)
{
	P0 = 0x00;   
	P1 = 0x00;   
	P2 = 0x00;   
	P3 = 0x00;  
}


void InitTimer1(void)
{
	TMOD &= 0x0F;    // Clear 4bit field for timer1
	TMOD |= 0x20;    // Set timer1 in mode 2
	
	TH1 = 0x05;      // 250 usec reloading time
	TL1 = 0x05;      // First time value
	
	ET1 = 1;         // Enable Timer1 interrupts
	EA  = 1;         // Global interrupt enable
	
	TR1 = 1;         // Start Timer 1
}


void Timer1_ISR (void) interrupt 3   // It is called after every 250usec
{
	Out = ~Out;  // Toggle Out pin

	TF1 = 0;     // Clear the interrupt flag
}

