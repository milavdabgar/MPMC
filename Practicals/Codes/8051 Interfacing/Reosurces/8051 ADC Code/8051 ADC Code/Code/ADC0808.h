#ifndef __ADC0808_H
#define __ADC0808_H

// Define ADC Channels
#define AN0		0
#define AN1		1
#define AN2		2
#define AN3		3
#define AN4		4
#define AN5		5
#define AN6		6
#define AN7		7

// Define Pins
sbit Add_A = P2^0;     // Address Pin A
sbit Add_B = P2^1;     // Address Pin B
sbit Add_C = P2^2;     // Address Pin C
sbit ALE   = P2^3;     // Address Latch Enable
sbit EOC   = P2^4;     // End Of Conversion
sbit OE    = P2^5;     // Output Enable
sbit START = P2^6;     // Start Conversion
sbit CLK   = P2^7;     // Clock for AD0808

// Define Data Bus
#define Data_Bus 	P0

#define HalfCycleDelay		10		// usecs

// Function Declarations
void InitADC(void);
unsigned char ReadADC(unsigned char);

#endif