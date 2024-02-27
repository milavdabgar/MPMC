#include "Includes.h"


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

void ToggleEpinOfLCD(void)
{
	E = 1;                // Give a pulse on E pin
	__delay_us(E_Delay);  // so that LCD can latch the
	E = 0;                // data from data bus
	__delay_us(E_Delay); 	
}

void WriteDataToLCD(char t)
{
   RS = 1;             // This is data

   P1 &= 0x0F;		   // Make P1.4 to P1.7 zero
   P1 |= (t&0xF0);     // Write Upper nibble of data
   ToggleEpinOfLCD();  // Toggle E pin to send data 

   P1 &= 0x0F;		   // Make P1.4 to P1.7 zero
   P1 |= ((t<<4)&0xF0);// Write Lower nibble of data
   ToggleEpinOfLCD();  // Toggle E pin to send data 
}


void WriteCommandToLCD(int z)
{
   RS = 0;             // This is command

   P1 &= 0x0F;		   // Make P1.4 to P1.7 zero
   P1 |= (z&0xF0);     // Write Upper nibble of data
   ToggleEpinOfLCD();  // Toggle E pin to send data 

   P1 &= 0x0F;		   // Make P1.4 to P1.7 zero
   P1 |= ((z<<4)&0xF0);// Write Lower nibble of data
   ToggleEpinOfLCD();  // Toggle E pin to send data 
}

void InitLCD(void)
{
	RS = 0;		 	// Make pin zero
	E  = 0;			// Make Pin zero					

  ///////////// Reset process from datasheet /////////
     __delay_us(15000);

	 P1 &= 0x0F;		   // Make P1.4 to P1.7 zero
	 P1 |= 0x30;    	   // Write 0x3
     ToggleEpinOfLCD();    // Toggle E pin to send data 

     __delay_us(4500);

	 P1 &= 0x0F;		   // Make P1.4 to P1.7 zero
	 P1 |= 0x30;    	   // Write 0x3
     ToggleEpinOfLCD();    // Toggle E pin to send data 

     __delay_us(300);

	 P1 &= 0x0F;		   // Make P1.4 to P1.7 zero
	 P1 |= 0x30;    	   // Write 0x3
     ToggleEpinOfLCD();    // Toggle E pin to send data 

     __delay_us(650);

	 P1 &= 0x0F;		   // Make P1.4 to P1.7 zero
	 P1 |= 0x20;    	   // Write 0x2
     ToggleEpinOfLCD();    // Toggle E pin to send data 

	 __delay_us(650);

  /////////////////////////////////////////////////////
   WriteCommandToLCD(0x28);    //function set
   WriteCommandToLCD(0x0c);    //display on,cursor off,blink off
   WriteCommandToLCD(0x01);    //clear display
   WriteCommandToLCD(0x06);    //entry mode, set increment
}


void WriteStringToLCD(const char *s)
{
	while(*s)
		WriteDataToLCD(*s++);   // print first character on LCD 
}


void ClearLCDScreen(void)       // Clear the Screen and return cursor to zero position
{
	WriteCommandToLCD(0x01);    // Clear the screen
	__delay_us(2000);           // Delay for cursor to return at zero position
}
