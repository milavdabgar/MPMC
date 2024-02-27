#ifndef __DAC0808_H
#define __DAC0808_H

// Define Pins
#define DAC_Data_Bus	P2	  	// Port Name

// Define VREF+ value
#define VREF			5		// Volts


// Function Declarations
void InitDAC(void);
void Generate_DAC_Voltage(unsigned int);

#endif