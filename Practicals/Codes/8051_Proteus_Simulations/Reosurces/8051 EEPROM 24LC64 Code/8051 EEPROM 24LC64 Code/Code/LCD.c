#include "Includes.h"

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

   P2 &= 0x0F;		   // Make P2.4 to P2.7 zero
   P2 |= (t&0xF0);     // Write Upper nibble of data
   ToggleEpinOfLCD();  // Toggle E pin to send data 

   P2 &= 0x0F;		   // Make P2.4 to P2.7 zero
   P2 |= ((t<<4)&0xF0);// Write Lower nibble of data
   ToggleEpinOfLCD();  // Toggle E pin to send data 
}


void WriteCommandToLCD(int z)
{
   RS = 0;             // This is command

   P2 &= 0x0F;		   // Make P2.4 to P2.7 zero
   P2 |= (z&0xF0);     // Write Upper nibble of data
   ToggleEpinOfLCD();  // Toggle E pin to send data 

   P2 &= 0x0F;		   // Make P2.4 to P2.7 zero
   P2 |= ((z<<4)&0xF0);// Write Lower nibble of data
   ToggleEpinOfLCD();  // Toggle E pin to send data 
}

void InitLCD(void)
{
	RS = 0;		 	// Make pin zero
	E  = 0;			// Make Pin zero					

  ///////////// Reset process from datasheet /////////
     __delay_us(15000);

	 P2 &= 0x0F;		   // Make P2.4 to P2.7 zero
	 P2 |= 0x30;    	   // Write 0x3
     ToggleEpinOfLCD();    // Toggle E pin to send data 

     __delay_us(4500);

	 P2 &= 0x0F;		   // Make P2.4 to P2.7 zero
	 P2 |= 0x30;    	   // Write 0x3
     ToggleEpinOfLCD();    // Toggle E pin to send data 

     __delay_us(300);

	 P2 &= 0x0F;		   // Make P2.4 to P2.7 zero
	 P2 |= 0x30;    	   // Write 0x3
     ToggleEpinOfLCD();    // Toggle E pin to send data 

     __delay_us(650);

	 P2 &= 0x0F;		   // Make P2.4 to P2.7 zero
	 P2 |= 0x20;    	   // Write 0x2
     ToggleEpinOfLCD();    // Toggle E pin to send data 

	 __delay_us(650);

  /////////////////////////////////////////////////////
   WriteCommandToLCD(0x28);    //function set
   WriteCommandToLCD(0x0c);    //display on,cursor off,blink off
   WriteCommandToLCD(0x01);    //clear display
   WriteCommandToLCD(0x06);    //entry mode, set increment
}
