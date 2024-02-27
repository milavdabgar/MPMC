/*  Name     : main.c
 *  Purpose  : Main file for ADC0808 code for AT89C51.
 *  Author   : M.Saeed Yasin
 *  Date     : 24-01-13
 *  Website  : saeedsolutions.blogspot.com
 *  Revision : None
 */
#include "Includes.h"

// Main function
void main()
{
	unsigned char ADC_Value = 0;	 	// To capture ADC value
	unsigned char Digit[3] = { 0,0,0 };	// To make digits to display on LCD

	InitADC();							// Initialize ADC
	InitLCD();							// Initialize LCD display
	WriteStringToLCD("Starting...");	// Show Welcome Message
	delay_sec(1);						// 1 Sec delay
	ClearLCDScreen();					// Clear LCD

	while(1)
	{
		ADC_Value = ReadADC(AN1);		// Read ADC value from Channel 1

		Digit[2] = (unsigned char)(	ADC_Value/100);		  			// Find out first digit
		Digit[1] = (unsigned char)( ADC_Value/10) - Digit[2]*10;	// Find out second digit
		Digit[0] = ADC_Value - Digit[2]*100 - Digit[1]*10;			// Find out third digit

		ClearLCDScreen();											// Clear LCD
		WriteStringToLCD("ADC value = ");							// Display string
		WriteDataToLCD(Digit[2]+0x30);								// Display first digit
		WriteDataToLCD(Digit[1]+0x30);								// Display second digit
		WriteDataToLCD(Digit[0]+0x30);								// Display third digit

		delay_sec(1);												 // Delay of one second
	}
}
