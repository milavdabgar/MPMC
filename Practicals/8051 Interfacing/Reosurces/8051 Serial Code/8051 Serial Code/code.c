////////////////////////////////////// ////////
// Project: Internet to serial port Control  //
// Author:  M.Saeed Yasin                    //
// Date:    14/11/2010                       //
///////////////////////////////////////////////

#include <reg52.h>

//DEFINE CONSTANT
#define Baud_rate 0xFD  // BAUD RATE 9600                     


//DEFINE PROTOTYPES
void SerialInitialize(void);
void SendByteSerially(unsigned char);	
void cct_init(void);

sbit Appliance1 = P1^0;
sbit Appliance2 = P1^1;
sbit Appliance3 = P1^2;
sbit Appliance4 = P1^3;
sbit Appliance5 = P1^4;
sbit Appliance6 = P1^5;
sbit Appliance7 = P1^6;
sbit Appliance8 = P1^7;


void main()
{
	cct_init();
	SerialInitialize();	

    EA = 1;
	ES = 1;

	while(1) {;}
}


void cct_init(void)   //initialize cct
{
	P0 = 0x00; //not used
	P1 = 0x00; //Used for Appliances
	P2 = 0x00; //not used
	P3 = 0x03; //used for serial

}

void SerialInitialize(void)		           // INITIALIZE SERIAL PORT
{
	TMOD = 0x20;	                       // Timer 1 IN MODE 2 -AUTO RELOAD TO GENERATE BAUD RATE
	SCON = 0x50;			               // SERIAL MODE 1, 8-DATA BIT 1-START BIT, 1-STOP BIT, REN ENABLED
	TH1 = Baud_rate;		               // LOAD BAUDRATE TO TIMER REGISTER
	TR1 = 1;			                   // START TIMER
}

void SendByteSerially(unsigned char serialdata)
{
	SBUF = serialdata;			            // LOAD DATA TO SERIAL BUFFER REGISTER
	while(TI == 0);			            	// WAIT UNTIL TRANSMISSION TO COMPLETE
	TI = 0;				                	// CLEAR TRANSMISSION INTERRUPT FLAG
}

void serial_ISR (void) interrupt 4
{
    //receive character
	char chr;
	if(RI==1)
	{
		chr = SBUF;
		RI = 0;
	}

    P0 = ~P0;    //Show the data has been updated

    switch(chr)
	{
     case '1':  Appliance1 = 1; SendByteSerially('k');  break;
     case '2':  Appliance2 = 1; SendByteSerially('k');  break;
	 case '3':  Appliance3 = 1; SendByteSerially('k');  break;
	 case '4':  Appliance4 = 1; SendByteSerially('k');  break;
	 case '5':  Appliance5 = 1; SendByteSerially('k');  break;
	 case '6':  Appliance6 = 1; SendByteSerially('k');  break;
	 case '7':  Appliance7 = 1; SendByteSerially('k');  break;
	 case '8':  Appliance8 = 1; SendByteSerially('k');  break;


     case 'a':  Appliance1 = 0; SendByteSerially('k');  break;
     case 'b':  Appliance2 = 0; SendByteSerially('k');  break;
     case 'c':  Appliance3 = 0; SendByteSerially('k');  break;
     case 'd':  Appliance4 = 0; SendByteSerially('k');  break;
     case 'e':  Appliance5 = 0; SendByteSerially('k');  break;
     case 'f':  Appliance6 = 0; SendByteSerially('k');  break;
     case 'g':  Appliance7 = 0; SendByteSerially('k');  break;
     case 'h':  Appliance8 = 0; SendByteSerially('k');  break;


     default: ;	break;     //do nothing
	}

	RI = 0;
}   	  
