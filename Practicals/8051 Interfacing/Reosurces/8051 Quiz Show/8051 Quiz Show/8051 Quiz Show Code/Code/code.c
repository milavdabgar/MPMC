// ***********************************************************
// Project:   Quiz Show
// Author:    M.Saeed Yasin
// Module description:  Use LCD, Keypad, and Computer Hyperterminal for a quiz show
// ***********************************************************
#include <reg51.h>
#include <string.h>

//DEFINE CONSTANT
#define Baud_rate 0xFD  // BAUD RATE 9600 

//Function declarations
void cct_init(void);
void delay(int);
void lcdinit(void);
void writecmd(int);
void writedata(char);
void newline2(void);
void Return(void);
char READ_SWITCHES(void);
char get_key(void);
void Error(int);              
void SerialInitialize(void);
void SendByteSerially(unsigned char);
unsigned char ReceiveByteSerially(void);	
void disp_welcome(void);
void writeline_lcd(char[]);
void writeline_serial(char[]);
void disp_msg_lcd(int);
void Ask_Question(void);
void Get_Answer_n_Give_Marks(void);
void Show_Results(void);
void disp_num_serial(int);
void disp_num_lcd(int);


//***********
//variables
char mode = '0';                     //mode = 0 means single player, mode = 1 means double player
char q1=0,q2=0,q3=0,q4=0,q5=0,q6=0;  //variable q associated with each question stored
int q_no = 13;                       //current question number being asked, 13 is a false intial value
int pc_answer = 0;                   //pc firstly pressed a button? 1 means yes
int keypress = 0;                    //pc key presses count
int userA_marks = 0;                 //userA marks are stored in this variable
int userB_marks = 0;                 //userB marks are stored in this variable

//*******************
//Pin description
/*
P2 is data bus
P3.0 is UART RX
P3.1 is UART TX
P3.6 is E
P3.7 is RS
P1.0 to P1.3 are keypad row outputs
P1.4 to P1.7 are keypad column inputs
*/
//********************
// Define Pins
//********************
sbit RowA = P1^0;     //RowA
sbit RowB = P1^1;     //RowB
sbit RowC = P1^2;     //RowC
sbit RowD = P1^3;     //RowD

sbit C1   = P1^4;     //Column1
sbit C2   = P1^5;     //Column2
sbit C3   = P1^6;     //Column3
sbit C4   = P1^7;     //Column4

sbit E    = P3^6;     //E pin for LCD
sbit RS   = P3^7;     //RS pin for LCD

// ***********************************************************
// Main program
//
int main(void)
{
   cct_init();                                     //Initiate all the cct
   disp_welcome();                                 //display welcome message
   
   while(1)
   {
	   // Initial varible values
	   mode = 'e';
	   q1=0,q2=0,q3=0,q4=0,q5=0,q6=0;
	   q_no = 13;
	   pc_answer = 0;
	   keypress = 0;
	   userA_marks = 0;
	   userB_marks = 0;
	   
	   // Mode selection through key pad
	   while(mode!='1' & mode!='0')
	   { 
	    writecmd(0x01);
		writeline_lcd("Mode 0 or 1?"); 
		mode = get_key();
		if(mode!='1' & mode!='0') { Error(0); newline2(); disp_msg_lcd(0); Return(); delay(30000); writecmd(0x01); }
	   }

	   // Display starting message
	   writecmd(0x01); if(mode=='1') {SendByteSerially(0x0D); SendByteSerially(0x0A);}   //new line and carriage return
	   writeline_lcd("Start"); if(mode=='1') { writeline_serial("Start"); }
	   delay(30000); delay(30000);writecmd(0x01);

	   // Ask question 1
	   writecmd(0x01); if(mode=='1') {SendByteSerially(0x0D); SendByteSerially(0x0A);}   //new line and carriage return
	   writeline_lcd("Q1"); if(mode=='1') { writeline_serial("Q1"); } 
	   delay(30000); delay(30000);writecmd(0x01); if(mode=='1') {SendByteSerially(0x0D); SendByteSerially(0x0A);}   //new line and carriage return
	   Ask_Question(); Get_Answer_n_Give_Marks();

	   // Ask question 2
	   writecmd(0x01); if(mode=='1') {SendByteSerially(0x0D); SendByteSerially(0x0A);}   //new line and carriage return
	   writeline_lcd("Q2"); if(mode=='1') { writeline_serial("Q2"); } 
	   delay(30000); delay(30000); writecmd(0x01); if(mode=='1') {SendByteSerially(0x0D); SendByteSerially(0x0A);}   //new line and carriage return
	   Ask_Question(); Get_Answer_n_Give_Marks();

	   // Ask question 3
	   writecmd(0x01); if(mode=='1') {SendByteSerially(0x0D); SendByteSerially(0x0A);}   //new line and carriage return
	   writeline_lcd("Q3"); if(mode=='1') { writeline_serial("Q3"); } 
	   delay(30000); delay(30000);writecmd(0x01); if(mode=='1') {SendByteSerially(0x0D); SendByteSerially(0x0A);}   //new line and carriage return
	   Ask_Question(); Get_Answer_n_Give_Marks();
	   
	   // Display results
	   Show_Results();   
   }
}


void cct_init(void)
{
	P0 = 0x00;   //not used
	P1 = 0xf0;   //used for generating outputs and taking inputs from Keypad
	P2 = 0x00;   //used as data port for LCD
	P3 = 0x03;   //used for RS and E  and serial comm 

	SerialInitialize();   // Initialize serial port
	lcdinit();            // Initialize LCD display

	EA = 1; ES = 1;      // Enable global and serial interrupts 
}

void delay(int a)
{
   int i;
   for(i=0;i<a;i++);   //null statement
}

void writeline_lcd(char line[])
{
   int i;
   for(i=0;i<strlen(line);i++)
   { writedata(line[i]); } //write to lcd
}

void writeline_serial(char line1[])
{  
   int i;
   EA = 0; ES = 0;
   for(i=0;i<strlen(line1);i++)
   { SendByteSerially(line1[i]); } // SEND DATA TO PC 
   EA = 1; ES = 1;
}

void writedata(char t)
{
   RS = 1;             // This is data
   P2 = t;             //Data transfer
   E  = 1;             // => E = 1
   delay(150);
   E  = 0;             // => E = 0
   delay(150);
}

void writecmd(int z)
{
   RS = 0;             // This is command
   P2 = z;             //Data transfer
   E  = 1;             // => E = 1
   delay(150);
   E  = 0;             // => E = 0
   delay(150);
}

void lcdinit(void)
{
  ///////////// Reset process from datasheet /////////
     delay(15000);
   writecmd(0x30);
     delay(4500);
   writecmd(0x30);
     delay(300);
   writecmd(0x30);
     delay(650);
  /////////////////////////////////////////////////////
   writecmd(0x38);    //function set
   writecmd(0x0c);    //display on,cursor off,blink off
   writecmd(0x01);    //clear display
   writecmd(0x06);    //entry mode, set increment
}

void Return(void)     //Return to 0 location
{
	writecmd(0x02);
	delay(1500);
}

void newline2(void)    //shift to line 2
{
	//set DDRAM address to line 2
	writecmd(0xc0);  //11000000
}

char READ_SWITCHES(void)	
{	
	RowA = 0; RowB = 1; RowC = 1; RowD = 1; 	//Test Row A

	if (C1 == 0) { delay(10000); while (C1==0); return '7'; }
	if (C2 == 0) { delay(10000); while (C2==0); return '8'; }
	if (C3 == 0) { delay(10000); while (C3==0); return '9'; }
	if (C4 == 0) { delay(10000); while (C4==0); return '/'; }

	RowA = 1; RowB = 0; RowC = 1; RowD = 1; 	//Test Row B

	if (C1 == 0) { delay(10000); while (C1==0); return '4'; }
	if (C2 == 0) { delay(10000); while (C2==0); return '5'; }
	if (C3 == 0) { delay(10000); while (C3==0); return '6'; }
	if (C4 == 0) { delay(10000); while (C4==0); return 'x'; }
	
	RowA = 1; RowB = 1; RowC = 0; RowD = 1; 	//Test Row C

	if (C1 == 0) { delay(10000); while (C1==0); return '1'; }
	if (C2 == 0) { delay(10000); while (C2==0); return '2'; }
	if (C3 == 0) { delay(10000); while (C3==0); return '3'; }
	if (C4 == 0) { delay(10000); while (C4==0); return '-'; }
	
	RowA = 1; RowB = 1; RowC = 1; RowD = 0; 	//Test Row D

	if (C1 == 0) { delay(10000); while (C1==0); return 'C'; }
	if (C2 == 0) { delay(10000); while (C2==0); return '0'; }
	if (C3 == 0) { delay(10000); while (C3==0); return '='; }
	if (C4 == 0) { delay(10000); while (C4==0); return '+'; }

	return 'n';           	// Means no key has been pressed
}

char get_key(void)           //get key from user
{
	char key = 'n';              //assume no key pressed

	while(key=='n')              //wait untill a key is pressed
		key = READ_SWITCHES();   //scan the keys again and again

	return key;                  //when key pressed then return its value
}

void Error(int numb)             //displays differet error messages
{
	writecmd(0x01);              //clear display
	
	switch(numb)
	{
	case 0: writeline_lcd("Wrong Input"); break;
	}
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


unsigned char ReceiveByteSerially(void)	
{
	while(RI == 0);			        	// WAIT UNTIL DATA IS RECEIVED 
	RI = 0;				            	// CLEAR FLAG

	//echo back
	SBUF = SBUF;
	while(TI == 0);			            // WAIT UNTIL TRANSMISSION TO COMPLETE
	TI = 0;				              	// CLEAR TRANSMISSION INTERRUPT FLAG
	return SBUF;			        	// RETURN SERIAL DATA
}

void serial_ISR (void) interrupt 4
{
    //receive character
	char chr;
	if(RI==1)
	{
		chr=SBUF;
		RI=0;
	}

	keypress++;

    switch(chr)
	{
	case '0': pc_answer = 1; break;

    default: ;	break;     //do nothing
	}

	RI = 0;
}   	  
	  

void disp_welcome(void)
{
	//Write to PC
	writeline_serial("\tWelcome to Quiz Show");
	SendByteSerially(0x0D); SendByteSerially(0x0A);   //new line and carriage return

	//Write to LCD
	writeline_lcd("Welcome...");
	Return();                                        //Return to 0 position

	delay(30000);
	delay(30000);
	writecmd(0x01);                                  //clear display
}
	
	
void disp_msg_lcd(int numb)
{
	switch(numb)
	{
	case 0: writeline_lcd("Try Again..."); break;
	}
}

void Ask_Question(void)
{
	int q = 13;
	writecmd(0x01);
	
	//randomize question
	while(!(q<7 & q>-1))
	{
		q = (TL1%6);
		if(q1==1 & q==1)  { q = 6; }
		if(q2==1 & q==2)  { q = 4; }
		if(q3==1 & q==3)  { q = 5; }
		if(q4==1 & q==4)  { q = 6; }
		if(q5==1 & q==5)  { q = 2; }
		if(q6==1 & q==6)  { q = 3; }
	}

	switch(q)
	{
	case 1:  q1=1; writeline_lcd("3,8,15,24,35..."); newline2(); writeline_lcd("51  48  46  42"); Return();
			 if(mode=='1') { writeline_serial("3,8,15,24,35...   options are (1)51  (2)48  (3)46  (4)42"); } break;
	case 2:  q2=1; writeline_lcd("6,14,18,28,30..."); newline2(); writeline_lcd("32  46  42  28"); Return();
			 if(mode=='1') { writeline_serial("6,14,18,28,30...   options are (1)32  (2)46  (3)42  (4)28"); } break;
	case 3:  q3=1; writeline_lcd("4, 1, 0, 1, 4..."); newline2(); writeline_lcd("1   3   9   0"); Return();
			 if(mode=='1') { writeline_serial("4, 1, 0, 1, 4...   options are (1)1  (2)3  (3)9  (4)0"); } break;
	case 4:  q4=1; writeline_lcd("-1, 4, 1, 6, 3..."); newline2(); writeline_lcd("8   10   5   7"); Return();
			 if(mode=='1') { writeline_serial("-1, 4, 1, 6, 3...   options are (1)8  (2)10  (3)5  (4)7"); } break;
	case 5:  q5=1; writeline_lcd("10,21,33,46,60..."); newline2(); writeline_lcd("88   73   65   75"); Return();
			 if(mode=='1') { writeline_serial("10,21,33,46,60...   options are (1)88  (2)73  (3)65  (4)75"); } break;
	case 6:  q6=1; writeline_lcd("1-1+1-1+...inf=?"); newline2(); writeline_lcd("0   1   1/2   -1"); Return();
			 if(mode=='1') { writeline_serial("1-1+1-1+...inf=?   options are (1)0  (2)1  (3)1/2  (4)-1"); } break;
	}
	
	q_no = q;
}

void Get_Answer_n_Give_Marks(void)
{
	char answer = 'e';
	char user = 'a';
	pc_answer = 0;

	switch(mode)
	{
	case '0': answer = get_key(); break;
	case '1': while(answer!='0' & pc_answer == 0 )
			  {  answer = READ_SWITCHES(); }
			  if(answer == '0') { user = 'a'; writecmd(0x01); writeline_lcd("Answer: "); answer = get_key(); }
			  else if(pc_answer == 1) { user = 'b'; pc_answer = 0; writeline_serial("Answer: ");ES = 0; answer = ReceiveByteSerially(); ES = 1; }
			  break;
	}
	
	if(user=='b' & mode=='1')
	{
	if(q_no==1 & answer == '2') { userB_marks+=5; }
	else if(q_no==2 & answer == '3') { userB_marks+=5; }
	else if(q_no==3 & answer == '3') { userB_marks+=5; }
	else if(q_no==4 & answer == '1') { userB_marks+=5; }
	else if(q_no==5 & answer == '4') { userB_marks+=5; }
	else if(q_no==6 & answer == '3') { userB_marks+=5; }
	else
	{ userB_marks-=3; writeline_serial("  userA turn");writecmd(0x01); writeline_lcd("Answer: "); answer = get_key(); 
	  if(q_no==1 & answer == '2') { userA_marks+=5; }
	  else if(q_no==2 & answer == '3') { userA_marks+=5; }
	  else if(q_no==3 & answer == '3') { userA_marks+=5; }
	  else if(q_no==4 & answer == '1') { userA_marks+=5; }
	  else if(q_no==5 & answer == '4') { userA_marks+=5; }
	  else if(q_no==6 & answer == '3') { userA_marks+=5; }}
	}
	else if(user=='a' & mode=='1')
	{
	if(q_no==1 & answer == '2') { userA_marks+=5; }
	else if(q_no==2 & answer == '3') { userA_marks+=5; }
	else if(q_no==3 & answer == '3') { userA_marks+=5; }
	else if(q_no==4 & answer == '1') { userA_marks+=5; }
	else if(q_no==5 & answer == '4') { userA_marks+=5; }
	else if(q_no==6 & answer == '3') { userA_marks+=5; }
	else
	{ userA_marks-=3; newline2(); writeline_lcd("  userB turn");writeline_serial("Answer: ");ES = 0; answer = ReceiveByteSerially(); ES = 1;
	   if(q_no==1 & answer == '2') { userB_marks+=5; }
	   else if(q_no==2 & answer == '3') { userB_marks+=5; }
	   else if(q_no==3 & answer == '3') { userB_marks+=5; }
	   else if(q_no==4 & answer == '1') { userB_marks+=5; }
	   else if(q_no==5 & answer == '4') { userB_marks+=5; }
	   else if(q_no==6 & answer == '3') { userB_marks+=5; }}
	}
	else if(mode=='0')
	{
	if(q_no==1 & answer == '2') { userA_marks+=5; }
	else if(q_no==2 & answer == '3') { userA_marks+=5; }
	else if(q_no==3 & answer == '3') { userA_marks+=5; }
	else if(q_no==4 & answer == '1') { userA_marks+=5; }
	else if(q_no==5 & answer == '4') { userA_marks+=5; }
	else if(q_no==6 & answer == '3') { userA_marks+=5; }
	else
	{ userA_marks-=2; }
	}
}


void Show_Results(void)
{
	//UserA Marks
	writecmd(0x01);
	writeline_lcd("Ur Marks...");
	newline2();
	disp_num_lcd(userA_marks);
	writeline_lcd("/15");
	Return();

	SendByteSerially(0x0D); SendByteSerially(0x0A);   //new line and carriage return
	writeline_serial("userA Marks:");
	disp_num_serial(userA_marks);
	writeline_serial("/15");
	SendByteSerially(0x0D); SendByteSerially(0x0A);   //new line and carriage return

	if(mode=='1')
	{
	//UserB Marks

	SendByteSerially(0x0D); SendByteSerially(0x0A);   //new line and carriage return
	writeline_serial("userB Marks:");
	disp_num_serial(userB_marks);
	writeline_serial("/15");
	SendByteSerially(0x0D); SendByteSerially(0x0A);   //new line and carriage return

	delay(30000);
	delay(30000);
	delay(30000);
	delay(30000);
	writecmd(0x01);
	writeline_lcd("PC Marks...");
	newline2();
	disp_num_lcd(userB_marks);
	writeline_lcd("/15");
	Return();
	}

	//wait for user key press
	keypress = 0;
	while(READ_SWITCHES()=='n' & keypress == 0 ) {;}
}

void disp_num_lcd(int numb)            //displays inputted number on LCD
{
	writedata(' ');                    //write a space and then number
	
	switch(numb)
	{
	case -9: writedata('-'); writedata('9'); break;
	case -8: writedata('-'); writedata('8'); break;
	case -7: writedata('-'); writedata('7'); break;
	case -6: writedata('-'); writedata('6'); break;
	case -5: writedata('-'); writedata('5'); break;
	case -4: writedata('-'); writedata('4'); break;
	case -3: writedata('-'); writedata('3'); break;
	case -2: writedata('-'); writedata('2'); break;
	case -1: writedata('-'); writedata('1'); break;
	case 0:  writedata('0'); break;
	case 1:  writedata('1'); break;
	case 2:  writedata('2'); break;
	case 3:  writedata('3'); break;
	case 4:  writedata('4'); break;
	case 5:  writedata('5'); break;
	case 6:  writedata('6'); break;
	case 7:  writedata('7'); break;
	case 8:  writedata('8'); break;
	case 9:  writedata('9'); break;
	case 10: writedata('1'); writedata('0'); break;
	case 11: writedata('1'); writedata('1'); break;
	case 12: writedata('1'); writedata('2'); break;
	case 13: writedata('1'); writedata('3'); break;
	case 14: writedata('1'); writedata('4'); break;
	case 15: writedata('1'); writedata('5'); break;
	}
}


void disp_num_serial(int value)            //displays value on pc
{
	switch(value)
	{
	case -9: SendByteSerially('-');SendByteSerially('9'); break;
	case -8: SendByteSerially('-');SendByteSerially('8'); break;
	case -7: SendByteSerially('-');SendByteSerially('7'); break;
	case -6: SendByteSerially('-');SendByteSerially('6'); break;
	case -5: SendByteSerially('-');SendByteSerially('5'); break;
	case -4: SendByteSerially('-');SendByteSerially('4'); break;
	case -3: SendByteSerially('-');SendByteSerially('3'); break;
	case -2: SendByteSerially('-');SendByteSerially('2'); break;
	case -1: SendByteSerially('-');SendByteSerially('1'); break;
	case 0: SendByteSerially('0'); break;
	case 1: SendByteSerially('1'); break;
	case 2: SendByteSerially('2'); break;
	case 3: SendByteSerially('3'); break;
	case 4: SendByteSerially('4'); break;
	case 5: SendByteSerially('5'); break;
	case 6: SendByteSerially('6'); break;
	case 7: SendByteSerially('7'); break;
	case 8: SendByteSerially('8'); break;
	case 9: SendByteSerially('9'); break;
	case 10: SendByteSerially('1');SendByteSerially('0'); break;
	case 11: SendByteSerially('1');SendByteSerially('1'); break;
	case 12: SendByteSerially('1');SendByteSerially('2'); break;
	case 13: SendByteSerially('1');SendByteSerially('3'); break;
	case 14: SendByteSerially('1');SendByteSerially('4'); break;
	case 15: SendByteSerially('1');SendByteSerially('5'); break;
	}
}