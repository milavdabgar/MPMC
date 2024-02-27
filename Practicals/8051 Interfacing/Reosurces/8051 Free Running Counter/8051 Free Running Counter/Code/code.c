/*  Name     : code.c
 *  Purpose  : Main file for making free running counter using 8051.
 *  Author   : M.Saeed Yasin
 *  Date     : 09-06-12
 *  Revision : None
 */
#include<reg51.h>

// Function declarations
void cct_init(void);
void delay(int);
void DisplayOn7Segment(char);

// Pin description
/* P2 is used for 7 segment
P2.0 is attached with 'A' segment 
P2.1 is attached with 'B' segment 
P2.2 is attached with 'C' segment 
P2.3 is attached with 'D' segment 
P2.4 is attached with 'E' segment 
P2.5 is attached with 'F' segment 
P2.6 is attached with 'G' segment 
*/

// Main function
int main(void)
{
   char ch = '0';	          // Character to be displayed on 7seg

   cct_init();   	          // Make all ports zero	

   while(1)           
   {
	DisplayOn7Segment(ch);	  // Display ch on 7seg
	delay(30000);			  // About 1 sec delay

	switch(ch)				  // Update ch with new value to be displayed
	{
		case '0':	ch = '1';  break;
		case '1':	ch = '2';  break;
		case '2':	ch = '3';  break;
		case '3':	ch = '4';  break;
		case '4':	ch = '5';  break;
		case '5':	ch = '6';  break;
		case '6':	ch = '7';  break;
		case '7':	ch = '8';  break;
		case '8':	ch = '9';  break;
		case '9':	ch = 'A';  break;
		case 'A':	ch = 'B';  break;
		case 'B':	ch = 'C';  break;
		case 'C':	ch = 'D';  break;
		case 'D':	ch = 'E';  break;
		case 'E':	ch = 'F';  break;
		case 'F':	ch = '0';  break;
	
		default: ch = '0';  break;
	}
   }
}

void cct_init(void)
{
	P0 = 0x00;   
	P1 = 0x00;   
	P2 = 0x00;   
	P3 = 0x00;  
}

void delay(int a)
{
   int i;
   for(i=0;i<a;i++);   //null statement
}

void DisplayOn7Segment(char ch)   // ch can have a value from '0' to 'F' only
{
	switch(ch)
	{
		case '0':	P2 = 0x3F;  break;
		case '1':	P2 = 0x06;  break;
		case '2':	P2 = 0x5B;  break;
		case '3':	P2 = 0x4F;  break;
		case '4':	P2 = 0x66;  break;
		case '5':	P2 = 0x6D;  break;
		case '6':	P2 = 0x7D;  break;
		case '7':	P2 = 0x07;  break;
		case '8':	P2 = 0x7F;  break;
		case '9':	P2 = 0x6F;  break;
		case 'A':	P2 = 0x77;  break;
		case 'B':	P2 = 0x7C;  break;
		case 'C':	P2 = 0x39;  break;
		case 'D':	P2 = 0x5E;  break;
		case 'E':	P2 = 0x79;  break;
		case 'F':	P2 = 0x71;  break;

		default: P2 = 0x3F;  break;
	}	
}
