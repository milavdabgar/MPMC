// ***********************************************************
// Project:   Digital Clock
// Author:    M.Saeed Yasin
// Module description:  Make a digital clock display using LCD
// ***********************************************************

#include<reg51.h>

//Function declarations
void cct_init(void);
void delay(int);
void lcdinit(void);
void WriteCommandToLCD(int);
void WriteDataToLCD(char);
void ClearLCDScreen(void);
void InitTimer0(void);
void UpdateTimeCounters(void);
void DisplayTimeToLCD(unsigned int,unsigned int,unsigned int);

//*******************
//Pin description
/*
P2.4 to P2.7 is data bus
P1.0 is RS
P1.1 is E
*/
//********************

// Defines Pins
sbit RS = P2^2;//P1^0;
sbit E  = P2^3;//P1^1;

// Define Clock variables
unsigned int usecCounter = 0;
unsigned int msCounter   = 0;
unsigned int secCounter  = 0;
unsigned int minCounter  = 0;
unsigned int hrCounter   = 0;



// ***********************************************************
// Main program
//
void main(void)
{
   cct_init();             // Make all ports zero
   lcdinit();              // Initilize LCD
   InitTimer0();           // Start Timer0
			
	while(1)
	{
		if( msCounter == 0 )                                       // msCounter becomes zero after exact one sec
		{
			DisplayTimeToLCD(hrCounter, minCounter, secCounter);   // Displays time in HH:MM:SS format
		}

		UpdateTimeCounters();                                      // Update sec, min, hours counters
  	}
}


void cct_init(void)
{
	P0 = 0x00;   //not used 
	P1 = 0x00;   //not used 
	P2 = 0x00;   //used as data port
	P3 = 0x00;   //used for generating E and RS
}


void InitTimer0(void)
{
	TMOD &= 0xF0;    // Clear 4bit field for timer0
	TMOD |= 0x02;    // Set timer0 in mode 2
	
	TH0 = 0x05;      // 250 usec reloading time//0x05
	TL0 = 0x05;      // First time value//0x05
	
	ET0 = 1;         // Enable Timer0 interrupts
	EA  = 1;         // Global interrupt enable
	
	TR0 = 1;         // Start Timer 0
}


void Timer0_ISR (void) interrupt 1     // It is called after every 250usec
{
	usecCounter = usecCounter + 250;   // Count 250 usec
	
	if(usecCounter==1000)              // 1000 usec means 1msec 
	{
		msCounter++;
		usecCounter = 0;
	}

	TF0 = 0;     // Clear the interrupt flag
}


void UpdateTimeCounters(void)
{
	if (msCounter==1000)
	{
		secCounter++;
		msCounter=0;
	}

	if(secCounter==60)
	{
		minCounter++;
		secCounter=0;
	}

	if(minCounter==60)
	{
		hrCounter++;
		minCounter=0;
	}

	if(hrCounter==24)
	{
		hrCounter = 0;
	}
}


void DisplayTimeToLCD( unsigned int h, unsigned int m, unsigned int s )   // Displays time in HH:MM:SS format
{
	ClearLCDScreen();      // Move cursor to zero location and clear screen

	// Display Hour
	WriteDataToLCD( (h/10)+0x30 );
	WriteDataToLCD( (h%10)+0x30 );

	//Display ':'
	WriteDataToLCD(':');

	//Display Minutes
	WriteDataToLCD( (m/10)+0x30 );
	WriteDataToLCD( (m%10)+0x30 );

	//Display ':'
	WriteDataToLCD(':');

	//Display Seconds
	WriteDataToLCD( (s/10)+0x30 );
	WriteDataToLCD( (s%10)+0x30 );
}


void delay(int a)
{
   int i;
   for(i=0;i<a;i++);   //null statement
}

void WriteDataToLCD(char t)
{
   RS = 1;             // This is data

   P2 &= 0x0F;		   // Make P2.4 to P2.7 zero
   P2 |= (t&0xF0);     // Write Upper nibble of data

   E  = 1;             // => E = 1
   delay(150);
   E  = 0;             // => E = 0
   delay(150);

   P2 &= 0x0F;		   // Make P2.4 to P2.7 zero
   P2 |= ((t<<4)&0xF0);// Write Lower nibble of data

   E  = 1;             // => E = 1
   delay(150);
   E  = 0;             // => E = 0
   delay(150);
}


void WriteCommandToLCD(int z)
{
   RS = 0;             // This is command

   P2 &= 0x0F;		   // Make P2.4 to P2.7 zero
   P2 |= (z&0xF0);     // Write Upper nibble of data

   E  = 1;             // => E = 1
   delay(150);
   E  = 0;             // => E = 0
   delay(150);

   P2 &= 0x0F;		   // Make P2.4 to P2.7 zero
   P2 |= ((z<<4)&0xF0);// Write Lower nibble of data

   E  = 1;             // => E = 1
   delay(150);
   E  = 0;             // => E = 0
   delay(150);
}

void lcdinit(void)
{
  ///////////// Reset process from datasheet /////////
     delay(15000);

	 P2 &= 0x0F;		   // Make P2.4 to P2.7 zero
	 P2 |= (0x30&0xF0);    // Write 0x3
	
	 E  = 1;               // => E = 1
	 delay(150);
	 E  = 0;               // => E = 0
	 delay(150);

     delay(4500);

	 P2 &= 0x0F;		   // Make P2.4 to P2.7 zero
	 P2 |= (0x30&0xF0);    // Write 0x3
	
	 E  = 1;               // => E = 1
	 delay(150);
	 E  = 0;               // => E = 0
	 delay(150);

     delay(300);

	 P2 &= 0x0F;		   // Make P2.4 to P2.7 zero
	 P2 |= (0x30&0xF0);    // Write 0x3
	
	 E  = 1;               // => E = 1
	 delay(150);
	 E  = 0;               // => E = 0
	 delay(150);

     delay(650);

	 P2 &= 0x0F;		   // Make P2.4 to P2.7 zero
	 P2 |= (0x20&0xF0);    // Write 0x2
	
	 E  = 1;               // => E = 1
	 delay(150);
	 E  = 0;               // => E = 0
	 delay(150);

	 delay(650);

  /////////////////////////////////////////////////////
   WriteCommandToLCD(0x28);    //function set
   WriteCommandToLCD(0x0c);    //display on,cursor off,blink off
   WriteCommandToLCD(0x01);    //clear display
   WriteCommandToLCD(0x06);    //entry mode, set increment
}

void ClearLCDScreen(void)
{
	WriteCommandToLCD(0x01);   // Clear screen command
	delay(1000);
}