#include <REG52.H>

/*=============================================================================
=============================================================================*/
unsigned char ex0_isr_counter = 0;

void ex0_isr (void) interrupt 0
{
ex0_isr_counter++;   // Increment the count
}

/*=============================================================================
=============================================================================*/
void main (void)
{

/*-----------------------------------------------
Configure INT0 (external interrupt 0) to generate
an interrupt on the falling-edge of /INT0 (P3.2).
Enable the EX0 interrupt and then enable the
global interrupt flag.
-----------------------------------------------*/
IT0 = 1;   // Configure interrupt 0 for falling edge on /INT0 (P3.2)
EX0 = 1;   // Enable EX0 Interrupt
EA = 1;    // Enable Global Interrupt Flag

/*-----------------------------------------------
Wait forever.
-----------------------------------------------*/
while (1)
  {
  }
}

/*=============================================================================
=============================================================================*/

