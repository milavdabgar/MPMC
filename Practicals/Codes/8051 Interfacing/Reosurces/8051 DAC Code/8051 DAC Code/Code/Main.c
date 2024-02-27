/*  Name     : main.c
 *  Purpose  : Main file for DAC0808 code for AT89C51.
 *  Author   : M.Saeed Yasin
 *  Date     : 10-07-13
 *  Website  : saeedsolutions.blogspot.com
 *  Revision : None
 */
#include "Includes.h"

// Define Function Prototypes
void delay_sec(unsigned int);
void __delay_us(unsigned int);

// Main function
void main()
{
	P0 = 0x00;		 		// Initialize all ports with a value of zero
	P1 = 0x00;
	P2 = 0x00;
	P3 = 0x00;

	InitDAC();				// Initialize DAC0808 data bus

	while(1)
	{  
		Generate_DAC_Voltage(1000);		// Generate 1000mV = 1v at output
		delay_sec(2);					// Two second delay
		Generate_DAC_Voltage(2000);		// Generate 2000mV = 2v at output
		delay_sec(2);					// Two second delay
		Generate_DAC_Voltage(3000);		// Generate 3000mV = 3v at output
		delay_sec(2);					// Two second delay
	}
}



// Function Purpose: Produce approximate delay in Secs.
void delay_sec(unsigned int d)
{
   unsigned int i;

   for(i=0;i<(d*20);i++)
   		__delay_us(50000);
}



// Function Purpose: Produce approximate delay in given uSecs.
void __delay_us(unsigned int d)
{
   unsigned int i, limit;
   limit = d/15;

   for(i=0;i<limit;i++);
}

