/*  Name     : code.c
 *  Purpose  : Main file for generating pwm using 8051.
 *  Author   : M.Saeed Yasin
 *  Date     : 13-06-12
 *  Revision : None
 */
#include<reg52.h>

// PWM_Pin
sbit PWM_Pin = P2^0;		   // Pin P2.0 is named as PWM_Pin

// Function declarations
void cct_init(void);
void InitTimer0(void);
void InitPWM(void);

// Global variables
unsigned char PWM = 0;	  // It can have a value from 0 (0% duty cycle) to 255 (100% duty cycle)
unsigned int temp = 0;    // Used inside Timer0 ISR

// PWM frequency selector
/* PWM_Freq_Num can have values in between 1 to 257	only
 * When PWM_Freq_Num is equal to 1, then it means highest PWM frequency
 * which is approximately 1000000/(1*255) = 3.9kHz
 * When PWM_Freq_Num is equal to 257, then it means lowest PWM frequency
 * which is approximately 1000000/(257*255) = 15Hz
 *
 * So, in general you can calculate PWM frequency by using the formula
 *     PWM Frequency = 1000000/(PWM_Freq_Num*255)
 */
#define PWM_Freq_Num   2	 // Highest possible PWM Frequency


// Main Function
int main(void)
{
   cct_init();   	       // Make all ports zero
   InitPWM();              // Start PWM
 
   PWM = 127;              // Make 50% duty cycle of PWM  -> 127

   while(1)                // Rest is done in Timer0 interrupt
   {}
}

// Init CCT function
void cct_init(void)
{
	P0 = 0x00;   
	P1 = 0x00;   
	P2 = 0x00;   
	P3 = 0x00;  
}

// Timer0 initialize
void InitTimer0(void)
{
	TMOD &= 0xF0;    // Clear 4bit field for timer0
	TMOD |= 0x01;    // Set timer0 in mode 1 = 16bit mode
	
	TH0 = 0x00;      // First time value
	TL0 = 0x00;      // Set arbitrarily zero
	
	ET0 = 1;         // Enable Timer0 interrupts
	EA  = 1;         // Global interrupt enable
	
	TR0 = 1;         // Start Timer 0
}

// PWM initialize
void InitPWM(void)
{
	PWM = 0;         // Initialize with 0% duty cycle
	InitTimer0();    // Initialize timer0 to start generating interrupts
					 // PWM generation code is written inside the Timer0 ISR
}

// Timer0 ISR
void Timer0_ISR (void) interrupt 1   
{
	unsigned int temp = 0;
	TR0 = 0;    // Stop Timer 0

	if(PWM_Pin)	// if PWM_Pin is high
	{
		PWM_Pin = 0;
		temp = (255-PWM)*PWM_Freq_Num;
		TH0  = 0xFF - (temp>>8)&0xFF;
		TL0  = 0xFF - temp&0xFF;	
	}
	else	     // if PWM_Pin is low
	{
		PWM_Pin = 1;
		temp = PWM*PWM_Freq_Num;
		TH0  = 0xFF - (temp>>8)&0xFF;
		TL0  = 0xFF - temp&0xFF;
	}

	TF0 = 0;     // Clear the interrupt flag
	TR0 = 1;     // Start Timer 0
}

