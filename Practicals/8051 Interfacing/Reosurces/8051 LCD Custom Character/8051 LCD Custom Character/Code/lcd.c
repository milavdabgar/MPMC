/*-----------------------------------------------------------------------*/
/* Project Name: LCD 8bit Custom Character Generation                    */
/* Author: Saeed Yasin 24/08/2010
/* --------------------------------------------------------------------- */

#include <reg51.h>
#include <string.h>

/* Function declarations */
void cct_init(void);
void delay(int);
void lcdinit(void);
void writecmd(int);
void writedata(char);
void writeline(char[]);
void ReturnHome(void);
void LCDBuildChar(unsigned char, unsigned char*);

/*-----------------------
Pin description
-------------------------
P2 is data bus
P3.0 is RS
P3.1 is E
-----------------------*/

// -----------------------   Define Custom Characters ----------------------- //
unsigned char Character1[8] = { 0x1c,0x16,0x1d,0x01,0x1d,0x16,0x1c,0x00 };   // Phone Up 1
unsigned char Character2[8] = { 0x07,0x0d,0x17,0x10,0x17,0x0d,0x07,0x00 };   // Phone Up 2
unsigned char Character3[8] = { 0x1f,0x1f,0x12,0x04,0x09,0x10,0x1f,0x00 };   // Phone Down 1
unsigned char Character4[8] = { 0x1f,0x1f,0x09,0x04,0x12,0x01,0x1f,0x00 };   // Phone Down 2
unsigned char Character5[8] = { 0x04,0x04,0x04,0x04,0x15,0x0e,0x04,0x00 };   // Downward Arrow
unsigned char Character6[8] = { 0x04,0x0e,0x15,0x04,0x04,0x04,0x04,0x00 };   // Upward Arrow
unsigned char Character7[8] = { 0x01,0x02,0x04,0x08,0x10,0x11,0x1f,0x00 };   // Curvy Object
unsigned char Character8[8] = { 0x00,0x1f,0x11,0x11,0x11,0x1f,0x00,0x00 };   // Square Box
/*---------------------------------------------------*/


/* Main program */
int main(void)
{
   cct_init();                                     /* Make all ports zero */
   lcdinit();                                      /* Initilize LCD */

   writedata(0x00);                                /* Write Custom Character 1 */
   writedata(0x01);                                /* Write Custom Character 2 */
      writedata(' ');                              // Space
   writedata(0x02);                                /* Write Custom Character 3 */
   writedata(0x03);                                /* Write Custom Character 4 */
      writedata(' ');                              // Space
   writedata(0x04);                                /* Write Custom Character 5 */
   writedata(0x05);                                /* Write Custom Character 6 */
      writedata(' ');                              // Space
   writedata(0x06);                                /* Write Custom Character 7 */
   writedata(0x07);                                /* Write Custom Character 8 */

   while(1)
   {;}
}


/*---------------------------------------------------*/

/* Function definitons */

void cct_init(void)
{
   P0 = 0x00;   /* not used */
   P1 = 0x00;   /* not used */
   P2 = 0x00;   /* used as data port */
   P3 = 0x00;   /* used for generating E and RS */
}

void delay(int a)
{
   int i;
   for(i=0;i<a;i++);   /* null statement */
}

void writedata(char t)
{
   P3 |= 0x01;         /*   => RS = 1     */
   P2 = t;             /*   Data transfer */
   P3 |= 0x02;         /*   => E = 1      */
   delay(150);
   P3 &= 0xfd;         /*   => E = 0      */
   delay(150);
}


void writecmd(int z)
{
   P3 &= 0xfe;         /*   => RS = 1     */
   P2 = z;             /*   Data transfer */
   P3 |= 0x02;         /*   => E = 1      */
   delay(150);
   P3 &= 0xfd;         /*   => E = 0      */
   delay(150);
}

void lcdinit(void)
{
  /* ------------ Reset process from datasheet ----------- */
     delay(15000);
   writecmd(0x30);
     delay(4500);
   writecmd(0x30);
     delay(300);
   writecmd(0x30);
     delay(650);
  /* ----------------------------------------------------- */
   writecmd(0x38);    /* function set */
   writecmd(0x0c);    /* display on,cursor off,blink off */
   writecmd(0x01);    /* clear display */
   writecmd(0x06);    /* entry mode, set increment */
   
   /* ---------- Build Custom Characters -----------------*/
   
   LCDBuildChar(0, Character1);                    /* Build Character1 at position 0 */ 
   LCDBuildChar(1, Character2);                    /* Build Character2 at position 1 */ 
   LCDBuildChar(2, Character3);                    /* Build Character3 at position 2 */ 
   LCDBuildChar(3, Character4);                    /* Build Character4 at position 3 */ 
   LCDBuildChar(4, Character5);                    /* Build Character5 at position 4 */ 
   LCDBuildChar(5, Character6);                    /* Build Character6 at position 5 */ 
   LCDBuildChar(6, Character7);                    /* Build Character6 at position 6 */ 
   LCDBuildChar(7, Character8);                    /* Build Character6 at position 7 */ 
}

void ReturnHome(void)     /* Return to 0 cursor location */
{
   writecmd(0x02);
   delay(1500);
}

void writeline(char Line[])
{
   int i;
   for(i=0;i<strlen(Line);i++)
   {
      writedata(Line[i]);     /* Write Character */
   }
   
   ReturnHome();          /* Return to 0 cursor position */
}

/********************************************************** 
Function Name: LCDBuildChar
Input:
     loc: location where you want to store  0,1,2,....7          
     p: Pointer to pattern data
Usage:
     LCDBuildChar(1,pattern);
 ********************************************************* */

void LCDBuildChar(unsigned char loc, unsigned char *p)
{
     unsigned char i;
	 
     if(loc<8)                                 //If valid address
	 {
         writecmd(0x40+(loc*8));               //Write to CGRAM
         for(i=0;i<8;i++)
            writedata(p[i]);                   //Write the character pattern to CGRAM
     }
	 writecmd(0x80);                           //shift back to DDRAM location 0
}
