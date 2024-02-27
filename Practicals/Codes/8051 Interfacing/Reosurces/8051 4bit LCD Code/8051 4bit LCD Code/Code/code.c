#include "lcd.h"
#include "delay.h"
// ***********************************************************
// Main program
//
void main(void)
{
   cct_init();                                     //Make all ports zero
   
   lcdinit();                                      //Initilize LCD
	 
   writedata('H');                                 //write
   writedata('e');                                 //write
   writedata('l');                                 //write
   writedata('l');                                 //write
   writedata('o');                                 //write
   writedata(' ');                                 //write
   writedata('W');                                 //write
   writedata('o');                                 //write
   writedata('r');                                 //write
   writedata('l');                                 //write
   writedata('d');                                 //write
   writedata('!');                                 //write

   ReturnHome();                                   //Return to 0 position
			
	while(1)
	{
	}

}


void cct_init(void)
{
P0 = 0x00;   //not used 
P1 = 0x00;   //not used 
P2 = 0x00;   //used as data port
P3 = 0x00;   //used for generating E and RS
}
