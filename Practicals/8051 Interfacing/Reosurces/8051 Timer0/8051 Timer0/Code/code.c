/*  Name     : code.c
 *  Purpose  : Main file for using timer0 of 8051.
 *  Author   : M.Saeed Yasin
 *  Date     : 08-06-12
 *  Revision : None
 */
#include<reg51.h>

// Out Pin
sbit Out = P2^0;		   // Pin P2.0 is named as Out

//Function declarations
void cct_init(void);
void InitTimer0(void);


int main(void)
{
   cct_init();   	       // Make all ports zero
   InitTimer0();           // Start Timer0
 
   while(1)                // Rest is done in Timer0 interrupt
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


void InitTimer0(void)
{
	TMOD &= 0xF0;    // Clear 4bit field for timer0
	TMOD |= 0x02;    // Set timer0 in mode 2
	
	TH0 = 0x05;      // 250 usec reloading time
	TL0 = 0x05;      // First time value
	
	ET0 = 1;         // Enable Timer0 interrupts
	EA  = 1;         // Global interrupt enable
	
	TR0 = 1;         // Start Timer 0
}


void Timer0_ISR (void) interrupt 1   // It is called after every 250usec
{
	Out = ~Out;  // Toggle Out pin

	TF0 = 0;     // Clear the interrupt flag
}

