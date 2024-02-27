#include "lcd.h"
#include "delay.h"

void writedata(char t)
{
   RS = 1;             // This is data

   P2 &= 0x0F;		   // Make P2.4 to P2.7 zero
   P2 |= (t&0xF0);     // Write Upper nibble of data

   E  = 1;             // => E = 1
   delay_us(150);
   E  = 0;             // => E = 0
   delay_us(150);

   P2 &= 0x0F;		   // Make P2.4 to P2.7 zero
   P2 |= ((t<<4)&0xF0);// Write Lower nibble of data

   E  = 1;             // => E = 1
   delay_us(150);
   E  = 0;             // => E = 0
   delay_us(150);
}


void writecmd(int z)
{
   RS = 0;             // This is command

   P2 &= 0x0F;		   // Make P2.4 to P2.7 zero
   P2 |= (z&0xF0);     // Write Upper nibble of data

   E  = 1;             // => E = 1
   delay_us(150);
   E  = 0;             // => E = 0
   delay_us(150);

   P2 &= 0x0F;		   // Make P2.4 to P2.7 zero
   P2 |= ((z<<4)&0xF0);// Write Lower nibble of data

   E  = 1;             // => E = 1
   delay_us(150);
   E  = 0;             // => E = 0
   delay_us(150);
}

void lcdinit(void)
{
  ///////////// Reset process from datasheet /////////
     delay_us(15000);

	 P2 &= 0x0F;		   // Make P2.4 to P2.7 zero
	 P2 |= (0x30&0xF0);    // Write 0x3
	
	 E  = 1;               // => E = 1
	 delay_us(150);
	 E  = 0;               // => E = 0
	 delay_us(150);

     delay_us(4500);

	 P2 &= 0x0F;		   // Make P2.4 to P2.7 zero
	 P2 |= (0x30&0xF0);    // Write 0x3
	
	 E  = 1;               // => E = 1
	 delay_us(150);
	 E  = 0;               // => E = 0
	 delay_us(150);

     delay_us(300);

	 P2 &= 0x0F;		   // Make P2.4 to P2.7 zero
	 P2 |= (0x30&0xF0);    // Write 0x3
	
	 E  = 1;               // => E = 1
	 delay_us(150);
	 E  = 0;               // => E = 0
	 delay_us(150);

     delay_us(650);

	 P2 &= 0x0F;		   // Make P2.4 to P2.7 zero
	 P2 |= (0x20&0xF0);    // Write 0x2
	
	 E  = 1;               // => E = 1
	 delay_us(150);
	 E  = 0;               // => E = 0
	 delay_us(150);

	 delay_us(650);

  /////////////////////////////////////////////////////
   writecmd(0x28);    //function set
   writecmd(0x0c);    //display on,cursor off,blink off
   writecmd(0x01);    //clear display
   writecmd(0x06);    //entry mode, set increment
}

void ReturnHome(void)     //Return to 0 location
{
  writecmd(0x02);
    delay_us(1500);
}