#include "Includes.h"


void InitDAC(void)
{	
	DAC_Data_Bus = 0x00;  // Make Outputs	
}


void Generate_DAC_Voltage(unsigned int mV)			 // Input should be in mV
{
	 unsigned long V = ((unsigned long)mV * 25)/VREF;// Scale the input value
	 V = V/98;						  				 // Conversion factor

	DAC_Data_Bus = (unsigned char)V;  				 // Assign proper value to DAC inputs
}