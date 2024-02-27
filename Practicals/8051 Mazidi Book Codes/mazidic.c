// Write an 8051 C program to send values 00 – FF to port P1.
// Solution:
#include <reg51.h>
void main(void)
{
    unsigned char z;
    for (z = 0; z <= 255; z++)
        P1 = z;
}
// Write an 8051 C program to send hex values for ASCII characters of
// 0, 1, 2, 3, 4, 5, A, B, C, and D to port P1.
// Solution:
#include <reg51.h>
void main(void)
{
    unsigned char mynum[] = "012345ABCD";
    unsigned char z;
    for (z = 0; z <= 10; z++)
        P1 = mynum[z];
}
// Write an 8051 C program to toggle all the bits of P1 continuously.
// Solution:
// Toggle P1 forever
#include <reg51.h>
void main(void)
{
    for (;;)
    {
        P1 = 0x55;
        P1 = 0xAA;
    }
}
// Write an 8051 C program to send values of –4 to +4 to port P1.
// Solution:
////Singed numbers
#include <reg51.h>
void main(void)
{
    char mynum[] = {+1, -1, +2, -2, +3, -3, +4, -4};
    unsigned char z;
    for (z = 0; z <= 8; z++)
        P1 = mynum[z];
}
// Write an 8051 C program to toggle bit D0 of the port P1 (P1.0)
// 50,000 times.
// Solution:
#include <reg51.h>
sbit MYBIT = P1 ^ 0;
void main(void)
{
    unsigned int z;
    for (z = 0; z <= 50000; z++)
    {
        MYBIT = 0;
        MYBIT = 1;
    }
}
// Write an 8051 C program to toggle bits of P1 continuously forever
// with some delay.
// Solution:
////Toggle P1 forever with some delay in between
////“on” and “off”
#include <reg51.h>
void main(void)
{
    unsigned int x;
    for (;;) // repeat forever
    {
        P1 = 0x55;
        for (x = 0; x < 40000; x++)
            ; // delay size
        // unknown
        P1 = 0xAA;
        for (x = 0; x < 40000; x++)
            ;
    }
}
// Write an 8051 C program to toggle bits of P1 ports continuously with a 250 ms.
// Solution:
#include <reg51.h>
void MSDelay(unsigned int);
void main(void)
{
    while (1) // repeat forever
    {
        P1 = 0x55;
        MSDelay(250);
        P1 = 0xAA;
        MSDelay(250);
    }
}

void MSDelay(unsigned int itime)
{
    unsigned int i, j;
    for (i = 0; i < itime; i++)
        for (j = 0; j < 1275; j++)
            ;
}
// LEDs are connected to bits P1 and P2. Write an 8051 C program that
// shows the count from 0 to FFH (0000 0000 to 1111 1111 in binary)
// on the LEDs.
// Solution:
#include <reg51.h>
#define LED P2
void main(void)
{
    P1 = 00; // clear P1
    LED = 0; // clear P2
    for (;;) // repeat forever
    {
        P1++;  // increment P1
        LED++; // increment P2
    }
}
// Write an 8051 C program to get a byte of data form P1, wait 1/2
// second, and then send it to P2.
// Solution:
#include <reg51.h>
void MSDelay(unsigned int);

void main(void)
{
    unsigned char mybyte;
    P1 = 0xFF; // make P1 input port
    while (1)
    {
        mybyte = P1; // get a byte from P1
        MSDelay(500);
        P2 = mybyte; // send it to P2
    }
}

void MSDelay(unsigned int itime)
{
    unsigned int i, j;
    for (i = 0; i < itime; i++)
        for (j = 0; j < 1275; j++)
            ;
}
// Write an 8051 C program to get a byte of data form P0. If it is less
// than 100, send it to P1; otherwise, send it to P2.
// Solution:
#include <reg51.h>
void main(void)
{
    unsigned char mybyte;
    P0 = 0xFF; // make P0 input port
    while (1)
    {
        mybyte = P0; // get a byte from P0
        if (mybyte < 100)
            P1 = mybyte; // send it to P1
        else
            P2 = mybyte; // send it to P2
    }
}
// Write an 8051 C program to toggle only bit P2.4 continuously without
// disturbing the rest of the bits of P2.
// Solution:
////Toggling an individual bit
#include <reg51.h>
sbit mybit = P2 ^ 4;
void main(void)
{
    while (1)
    {
        mybit = 1; // turn on P2.4
        mybit = 0; // turn off P2.4
    }
}
// Write an 8051 C program to monitor bit P1.5. If it is high, send 55H
// to P0; otherwise, send AAH to P2.
// Solution:
#include <reg51.h>
sbit mybit = P1 ^ 5;
void main(void)
{
    mybit = 1; // make mybit an input
    while (1)
    {
        if (mybit == 1)
            P0 = 0x55;
        else
            P2 = 0xAA;
    }
}
// A door sensor is connected to the P1.1 pin, and a buzzer is connected
// to P1.7. Write an 8051 C program to monitor the door sensor, and
// when it opens, sound the buzzer. You can sound the buzzer by
// sending a square wave of a few hundred Hz.
// Solution:
#include <reg51.h>
void MSDelay(unsigned int);
sbit Dsensor = P1 ^ 1;
sbit Buzzer = P1 ^ 7;

void main(void)
{
    Dsensor = 1; // make P1.1 an input
    while (1)
    {
        while (Dsensor == 1) // while it opens
        {
            Buzzer = 0;
            MSDelay(200);
            Buzzer = 1;
            MSDelay(200);
        }
    }
}
void MSDelay(unsigned int itime)
{
    unsigned int i, j;
    for (i = 0; i < itime; i++)
        for (j = 0; j < 1275; j++)
            ;
}
// The data pins of an LCD are connected to P1. The information is
// latched into the LCD whenever its Enable pin goes from high to low.
// Write an 8051 C program to send “The Earth is but One Country” to
// this LCD.
// Solution:
#include <reg51.h>
#define LCDData P1 // LCDData declaration
sbit En = P2 ^ 0;  // the enable pin

void main(void)
{
    unsigned char message[] = "The Earth is but One Country";
    unsigned char z;
    for (z = 0; z < 28; z++) // send 28 characters
    {
        LCDData = message[z];
        En = 1; // a highEn=0; //-to-low pulse to latch data
    }
}
// Write an 8051 C program to toggle all the bits of P0, P1, and P2
// continuously with a 250 ms delay. Use the sfr keyword to declare the
// port addresses.
// Solution:
// Accessing Ports as SFRs using sfr data type
sfr P0 = 0x80;
sfr P1 = 0x90;
sfr P2 = 0xA0;
void MSDelay(unsigned int);

void main(void)
{
    while (1)
    {
        P0 = 0x55;
        P1 = 0x55;
        P2 = 0x55;
        MSDelay(250);
        P0 = 0xAA;
        P1 = 0xAA;
        P2 = 0xAA;
        MSDelay(250);
    }
}

void MSDelay(unsigned int itime)
{
    unsigned int i, j;
    for (i = 0; i < itime; i++)
        for (j = 0; j < 1275; j++)
            ;
}
// Write an 8051 C program to turn bit P1.5 on and off 50,000 times.
// Solution:
sbit MYBIT = 0x95;
void main(void)
{
    unsigned int z;
    for (z = 0; z < 50000; z++)
    {
        MYBIT = 1;
        MYBIT = 0;
    }
}
// Write an 8051 C program to get the status of bit P1.0, save it, and
// send it to P2.7 continuously.
// Solution:
#include <reg51.h>
sbit inbit = P1 ^ 0;
sbit outbit = P2 ^ 7;
bit membit; // use bit to declare bit- addressable memory

void main(void)
{
    while (1)
    {
        membit = inbit;  // get a bit from P1.0
        outbit = membit; // send it to P2.7
    }
}
// Run the following program on your simulator and examine the results.
// Solution:
#include <reg51.h>
void main(void)
{
    P0 = 0x35 & 0x0F; // ANDing
    P1 = 0x04 | 0x68; // ORing
    P2 = 0x54 ^ 0x78; // XORing
    P0 = ~0x55;       // inversing
    P1 = 0x9A >> 3;   // shifting right 3
    P2 = 0x77 >> 4;   // shifting right 4
    P0 = 0x6 << 4;    // shifting left 4
}
// Write an 8051 C program to toggle all the bits of P0 and P2
// continuously with a 250 ms delay. Using the inverting and Ex-OR
// operators, respectively.
// Solution:
#include <reg51.h>
void MSDelay(unsigned int);
void main(void)
{
    P0 = 0x55;
    P2 = 0x55;
    while (1)
    {
        P0 = ~P0;
        P2 = P2 ^ 0xFF;
        MSDelay(250);
    }
}

void MSDelay(unsigned int itime)
{
    unsigned int i, j;
    for (i = 0; i < itime; i++)
        for (j = 0; j < 1275; j++)
            ;
}
// Write an 8051 C program to get bit P1.0 and send it to P2.7 after
// inverting it.
// Solution:
#include <reg51.h>
sbit inbit = P1 ^ 0;
sbit outbit = P2 ^ 7;
bit membit;

void main(void)
{
    while (1)
    {
        membit = inbit;   // get a bit from P1.0
        outbit = ~membit; // invert it and send it to P2.7
    }
}
// Write an 8051 C program to read the P1.0 and P1.1 bits and issue an
// ASCII character to P0 according to the following table.
// P1.1 P1.0
// 0 0 send ‘0’ to P0
// 0 1 send ‘1’ to P0
// 1 0 send ‘2’ to P0
// 1 1 send ‘3’ to P0
// Solution:
#include <reg51.h>
void main(void)
{
    unsignbed char z;
    z = P1;
    z = z & 0x3;
    switch (z)
    {
    case (0):
    {
        P0 = '0';
        break;
    }
    case (1):
    {
        P0 = '1';
        break;
    }
    case (2):
    {
        P0 = '2';
        break;
    }
    case (3):
    {
        P0 = '3';
        break;
    }
    }
}
// Write an 8051 C program to convert packed BCD 0x29 to ASCII and
// display the bytes on P1 and P2.
// Solution:
#include <reg51.h>
void main(void)
{
    unsigned char x, y, z;
    unsigned char mybyte = 0x29;
    x = mybyte & 0x0F;
    P1 = x | 0x30;
    y = mybyte & 0xF0;
    y = y >> 4;
    P2 = y | 0x30;
}
// Write an 8051 C program to convert ASCII digits of ‘4’ and ‘7’ to
// packed BCD and display them on P1.
// Solution:
#include <reg51.h>
void main(void)
{
    unsigned char bcdbyte;
    unsigned char w = '4';
    unsigned char z = '7';
    w = w & 0x0F;
    w = w << 4;
    z = z & 0x0F;
    bcdbyte = w | z;
    P1 = bcdbyte;
}
// Write an 8051 C program to calculate the checksum byte for the data
// 25H, 62H, 3FH, and 52H.
// Solution:
#include <reg51.h>
void main(void)
{
    unsigned char mydata[] = {0x25, 0x62, 0x3F, 0x52};
    unsigned char sum = 0;
    unsigned char x;
    unsigned char chksumbyte;
    for (x = 0; x < 4; x++)
    {
        P2 = mydata[x];
        sum = sum + mydata[x];
        P1 = sum;
    }
    chksumbyte = ~sum + 1;
    P1 = chksumbyte;
}
// Write an 8051 C program to perform the checksum operation to
// ensure data integrity. If data is good, send ASCII character ‘G’ to P0.
// Otherwise send ‘B’ to P0.
// Solution:
#include <reg51.h>
void main(void)
{
    unsigned char mydata[] = {0x25, 0x62, 0x3F, 0x52, 0xE8};
    unsigned char chksum = 0;
    unsigned char x;
    for (x = 0; x < 5; x++)
        chksum = chksum + mydata[x];
    if (chksum == 0)
        P0 = 'G';
    else
        P0 = 'B';
}
// Write an 8051 C program to convert 11111101 (FD hex) to decimal
// and display the digits on P0, P1 and P2.
// Solution:
#include <reg51.h>
void main(void)
{
    unsigned char x, binbyte, d1, d2, d3;
    binbyte = 0xFD;
    x = binbyte / 10;
    d1 = binbyte % 10;
    d2 = x % 10;
    d3 = x / 10;
    P0 = d1;
    P1 = d2;
    P2 = d3;
}
// Compile and single-step the following program on your 8051
// simulator. Examine the contents of the 128-byte RAM space to locate
// the ASCII values.
// Solution:
#include <reg51.h>
void main(void)
{
    unsigned char mynum[] = "ABCDEF"; // RAM space
    unsigned char z;
    for (z = 0; z <= 6; z++)
        P1 = mynum[z];
}
// Write, compile and single-step the following program on your 8051
// simulator. Examine the contents of the code space to locate the values.
// Solution:
#include <reg51.h>
void main(void)
{
    unsigned char mydata[100]; // RAM space
    unsigned char x, z = 0;
    for (x = 0; x < 100; x++)
    {
        z--;
        mydata[x] = z;
        P1 = z;
    }
}
// Compile and single-step the following program on your 8051
// simulator. Examine the contents of the code space to locate the ASCII
// values.
// Solution:
#include <reg51.h>
void main(void)
{
    code unsigned char mynum[] = "ABCDEF";
    unsigned char z;
    for (z = 0; z <= 6; z++)
        P1 = mynum[z];
}
// Write, compile and single-step the following program on your 8051
// simulator. Examine the contents of the code space to locate the values.
// Solution:
#include <reg51.h>
void main(void)
{
    unsigned char mydata[100]; // RAM space
    unsigned char x, z = 0;
    for (x = 0; x < 100; x++)
    {
        z--;
        mydata[x] = z;
        P1 = z;
    }
}
// Compile and single-step the following program on your 8051
// simulator. Examine the contents of the code space to locate the ASCII
// values.
// Solution:
#include <reg51.h>
void main(void)
{
    code unsigned char mynum[] = "ABCDEF";
    unsigned char z;
    for (z = 0; z <= 6; z++)
        P1 = mynum[z];
}
// Write a C program to send out the value 44H serially one bit at a time
// via P1.0. The LSB should go out first.
// Solution:
#include <reg51.h>
sbit P1b0 = P1 ^ 0;
sbit regALSB = ACC ^ 0;
void main(void)
{
    unsigned char conbyte = 0x44;
    unsigned char x;
    ACC = conbyte;
    for (x = 0; x < 8; x++)
    {
        P1b0 = regALSB;
        ACC = ACC >> 1;
    }
}
// Write a C program to send out the value 44H serially one bit at a time
// via P1.0. The MSB should go out first.
// Solution:
#include <reg51.h>
sbit P1b0 = P1 ^ 0;
sbit regAMSB = ACC ^ 7;
void main(void)
{
    unsigned char conbyte = 0x44;
    unsigned char x;
    ACC = conbyte;
    for (x = 0; x < 8; x++)
    {
        P1b0 = regAMSB;
        ACC = ACC << 1;
    }
}
// Write a C program to bring in a byte of data serially one bit at a time
// via P1.0. The LSB should come in first.
// Solution:
#include <reg51.h>
sbit P1b0 = P1 ^ 0;
sbit ACCMSB = ACC ^ 7;
bit membit;
void main(void)
{
    unsigned char x;
    for (x = 0; x < 8; x++)
    {
        membit = P1b0;
        ACC = ACC >> 1;
        ACCMSB = membit;
    }
    P2 = ACC;
}
// Write a C program to bring in a byte of data serially one bit at a time
// via P1.0. The MSB should come in first.
// Solution:
#include <reg51.h>
sbit P1b0 = P1 ^ 0;
sbit regALSB = ACC ^ 0;
bit membit;

void main(void)
{
    unsigned char x;
    for (x = 0; x < 8; x++)
    {
        membit = P1b0;
        ACC = ACC << 1;
        regALSB = membit;
    }
    P2 = ACC;
}
// Example 9-20
// Write an 8051 C program to toggle all the bits of port P1 continuously
// with some delay in between. Use Timer 0, 16-bit mode to
// generate the delay.
// Solution:
#include <reg51.h>
void T0Delay(void);
void main(void)
{
    while (1)
    {
        P1 = 0x55;
        T0Delay();
        P1 = 0xAA;
        T0Delay();
    }
}

void T0Delay()
{
    TMOD = 0x01;
    TL0 = 0x00;
    TH0 = 0x35;
    TR0 = 1;
    while (TF0 == 0)
        ;
    TR0 = 0;
    TF0 = 0;
}
// Example 9-21
// Write an 8051 C program to toggle only bit P1.5 continuously every
// 50 ms. Use Timer 0, mode 1 (16-bit) to create the delay. Test the
// program on the (a) AT89C51 and (b) DS89C420.
// Solution:
#include <reg51.h>
void T0M1Delay(void);
sbit mybit = P1 ^ 5;

void main(void)
{
    while (1)
    {
        mybit = ~mybit;
        T0M1Delay();
    }
}

void T0M1Delay(void)
{
    TMOD = 0x01;
    TL0 = 0xFD;
    TH0 = 0x4B;
    TR0 = 1;
    while (TF0 == 0)
        ;
    TR0 = 0;
    TF0 = 0;
}
// Example 9-22
// Write an 8051 C program to toggle all bits of P2 continuously every
// 500 ms. Use Timer 1, mode 1 to create the delay.
// Solution:
#include <reg51.h>
void T1M1Delay(void);
void main(void)
{
    unsigned char x;
    P2 = 0x55;
    while (1)
    {
        P2 = ~P2;
        for (x = 0; x < 20; x++)
            T1M1Delay();
    }
}

void T1M1Delay(void)
{
    TMOD = 0x10;
    TL1 = 0xFE;
    TH1 = 0xA5;
    TR1 = 1;
    while (TF1 == 0)
        ;
    TR1 = 0;
    TF1 = 0;
}
// Example 9-25
// A switch is connected to pin P1.2. Write an 8051 C program to
// monitor SW and create the following frequencies on pin P1.7:
// SW=0: 500Hz
// SW=1: 750Hz, use Timer 0, mode 1 for both of them.
// Solution:
#include <reg51.h>
sbit mybit = P1 ^ 5;
sbit SW = P1 ^ 7;
void T0M1Delay(unsigned char);

void main(void)
{
    SW = 1;
    while (1)
    {
        mybit = ~mybit;
        if (SW == 0)
            T0M1Delay(0);
        else
            T0M1Delay(1);
    }
}

void T0M1Delay(unsigned char c)
{
    TMOD = 0x01;
    if (c == 0)
    {
        TL0 = 0x67;
        TH0 = 0xFC;
    }
    else
    {
        TL0 = 0x9A;
        TH0 = 0xFD;
    }
    TR0 = 1;
    while (TF0 == 0)
        ;
    TR0 = 0;
    TF0 = 0;
}
// Example 9-23
// Write an 8051 C program to toggle only pin P1.5 continuously every
// 250 ms. Use Timer 0, mode 2 (8-bit auto-reload) to create the
// delay.
// Solution:
#include <reg51.h>
void T0M2Delay(void);
sbit mybit = P1 ^ 5;

void main(void)
{
    unsigned char x, y;
    while (1)
    {
        mybit = ~mybit;
        for (x = 0; x < 250; x++)
            for (y = 0; y < 36; y++) // we put 36, not 40
                T0M2Delay();
    }
}

void T0M2Delay(void)
{
    TMOD = 0x02;
    TH0 = -23;
    TR0 = 1;
    while (TF0 == 0)
        ;
    TR0 = 0;
    TF0 = 0;
}
// Example 9-24
// Write an 8051 C program to create a frequency of 2500 Hz on pin
// P2.7. Use Timer 1, mode 2 to create delay.
// Solution:
#include <reg51.h>
void T1M2Delay(void);
sbit mybit = P2 ^ 7;

void main(void)
{
    unsigned char x;
    while (1)
    {
        mybit = ~mybit;
        T1M2Delay();
    }
}
void T1M2Delay(void)
{
    TMOD = 0x20;
    TH1 = -184;
    TR1 = 1;
    while (TF1 == 0)
        ;
    TR1 = 0;
    TF1 = 0;
}
// Example 9-26
// Assume that a 1-Hz external clock is being fed into pin T1 (P3.5).
// Write a C program for counter 1 in mode 2 (8-bit auto reload) to count
// up and display the state of the TL1 count on P1. Start the count at 0H.
// Solution:
#include <reg51.h>
void main(void)
{
    T1 = 1;
    TMOD = 0x60;
    TH1 = 0;
    while (1)
    {
        do
        {
            TR1 = 1;
            P1 = TL1;
        } while (TF1 == 0);
        TR1 = 0;
        TF1 = 0;
    }
}
// Example 9-27
// Assume that a 1-Hz external clock is being fed into pin T0 (P3.4).
// Write a C program for counter 0 in mode 1 (16-bit) to count the pulses
// and display the state of the TH0 and TL0 registers on P2 and P1,
// respectively.
// Solution:
#include <reg51.h>
void main(void)
{
    T0 = 1;
    TMOD = 0x05;
    TL0 = 0;
    TH0 = 0;
    while (1)
    {
        do
        {
            TR0 = 1;
            P1 = TL0;
            P2 = TH0;
        } while (TF0 == 0);
        TR0 = 0;
        TF0 = 0;
    }
}
// Example 10-15
// Write a C program for 8051 to transfer the letter “A” serially at 4800
// baud continuously. Use 8-bit data and 1 stop bit.
// Solution:
#include <reg51.h>
void main(void)
{
    TMOD = 0x20; // use Timer 1, mode 2
    TH1 = 0xFA;  // 4800 baud rate
    SCON = 0x50;
    TR1 = 1;
    while (1)
    {
        SBUF = 'A'; // place value in buffer
        while (TI == 0)
            ;
        TI = 0;
    }
}
// Example 10-16
// Write an 8051 C program to transfer the message “YES” serially at
// 9600 baud, 8-bit data, 1 stop bit. Do this continuously.
// Solution:
#include <reg51.h>
void SerTx(unsigned char);
void main(void)
{
    TMOD = 0x20; // use Timer 1, mode 2
    TH1 = 0xFD;  // 9600 baud rate
    SCON = 0x50;
    TR1 = 1; // start timer
    while (1)
    {
        SerTx('Y');
        SerTx('E');
        SerTx('S');
    }
}

void SerTx(unsigned char x)
{
    SBUF = x; // place value in buffer
    while (TI == 0)
        ; // wait until transmitted
    TI = 0;
}
// Example 10-17
// Program the 8051 in C to receive bytes of data serially and put them
// in P1. Set the baud rate at 4800, 8-bit data, and 1 stop bit.
// Solution:
#include <reg51.h>
void main(void)
{
    unsigned char mybyte;
    TMOD = 0x20; // use Timer 1, mode 2
    TH1 = 0xFA;  // 4800 baud rate
    SCON = 0x50;
    TR1 = 1; // start timer
    while (1)
    { // repeat forever
        while (RI == 0)
            ;          // wait to receive
        mybyte = SBUF; // save value
        P1 = mybyte;   // write value to port
        RI = 0;
    }
}
// Example 10-19
// Write an 8051 C Program to send the two messages “Normal Speed”
// and “High Speed” to the serial port. Assuming that SW is connected
// to pin P2.0, monitor its status and set the baud rate as follows:
// SW = 0, 28,800 baud rate
// SW = 1, 56K baud rate
// Assume that XTAL = 11.0592 MHz for both cases.
// Solution:
#include <reg51.h>
sbit MYSW = P2 ^ 0; // input switch
void main(void)
{
    unsigned char z;
    unsigned char Mess1[] = "Normal Speed";
    unsigned char Mess2[] = "High Speed";
    TMOD = 0x20; // use Timer 1, mode 2
    TH1 = 0xFF;     // 28800 for normal
    SCON = 0x50;
    TR1 = 1; // start timer
    if (MYSW == 0)
    {
        for (z = 0; z < 12; z++)
        {
            SBUF = Mess1[z]; // place value in buffer
            while (TI == 0)
                ; // wait for transmit
            TI = 0;
        }
    }
    else
    {
        PCON = PCON | 0x80; // for high speed of 56K
        for (z = 0; z < 10; z++)
        {
            SBUF = Mess2[z]; // place value in buffer
            while (TI == 0)
                ; // wait for transmit
            TI = 0;
        }
    }
}
// Example 10-20
// Write a C program for the DS89C4x0 to transfer the letter “A” serially
// at 4800 baud continuously. Use the second serial port with 8-bit data
// and 1 stop bit. We can only use Timer 1 to set the baud rate.
// Solution:
#include <reg51.h>
sfr SBUF1 = 0xC1;
sfr SCON1 = 0xC0;
sbit TI1 = 0xC1;

void main(void)
{
    TMOD = 0x20; // use Timer 1, mode 2
    TH1 = 0xFA;  // 4800 baud rate
    SCON = 0x50; // use 2nd serial port SCON1
    TR1 = 1;     // start timer
    while (1)
    {
        SBUF1 = 'A'; // use 2nd serial port SBUF1
        while (TI1 == 0)
            ; // wait for transmit
        TI1 = 0;
    }
}
// Example 10-21
// Program the DS89C4x0 in C to receive bytes of data serially via the
// second serial port and put them in P1. Set the baud rate at 9600, 8-bit
// data and 1 stop bit. Use Timer 1 for baud rate generation.
// Solution:
#include <reg51.h>
sfr SBUF1 = 0xC1;
sfr SCON1 = 0xC0;
sbit RI1 = 0xC0;
void main(void)
{
    unsigned char mybyte;
    TMOD = 0x20;  // use Timer 1, mode 2
    TH1 = 0xFD;   // 9600 baud rate
    SCON1 = 0x50; // use 2nd serial port SCON1
    TR1 = 1;      // start timer
    while (1)
    {
        while (RI1 == 0)
            ;           // monitor RI1
        mybyte = SBUF1; // use SBUF1
        P2 = mybyte;    // place value on port
        RI1 = 0;
    }
}
// Example 11-14
// Write a C program that continuously gets a single bit of data from P1.7
// and sends it to P1.0, while simultaneously creating a square wave of
// 200 μs period on pin P2.5. Use Timer 0 to create the square wave.
// Assume that XTAL = 11.0592 MHz.
// Solution:
// We will use timer 0 mode 2 (auto-reload). One half of the period is
// 100 μs. 100/1.085 μs = 92, and TH0 = 256 - 92 = 164 or A4H
#include <reg51.h>
sbit SW = P1 ^ 7;
sbit IND = P1 ^ 0;
sbit WAVE = P2 ^ 5;

void timer0(void) interrupt 1
{
    WAVE = ~WAVE; // toggle pin
}

void main()
{
    SW = 1; // make switch input
    TMOD = 0x02;
    TH0 = 0xA4; // TH0=-92
    IE = 0x82;    // enable interrupt for timer 0
    while (1)
    {
        IND = SW; // send switch to LED
    }
}
// Example 11-16
// Write a C program using interrupts to do the following:
//(a) Receive data serially and send it to P0
//(b) Read port P1, transmit data serially, and give a copy to P2
//(c) Make timer 0 generate a square wave of 5 kHz frequency on P0.1
// Assume that XTAL = 11.0592 MHz. Set the baud rate at 4800.
// Solution:
#include <reg51.h>
sbit WAVE = P0 ^ 1;

void timer0() interrupt 1
{
    WAVE = ~WAVE; // toggle pin
}

void serial0() interrupt 4
{
    if (TI == 1)
    {
        TI = 0; // clear interrupt
    }
    else
    {
        P0 = SBUF; // put value on pins
        RI = 0;    // clear interrupt
    }
}

void main()
{
    unsigned char x;
    P1 = 0xFF; // make P1 an input
    TMOD = 0x22;
    TH1 = 0xF6; // 4800 baud rate
    SCON = 0x50;
    TH0 = 0xA4; // 5 kHz has T=200us
    IE = 0x92;  // enable interrupts
    TR1 = 1;    // start timer 1
    TR0 = 1;    // start timer 0
    while (1)
    {
        x = P1;   // read value from pins
        SBUF = x; // put value in buffer
        P2 = x;   // write value to pins
    }
}
// Example 11-17
// Write a C program using interrupts to do the following:
//(a) Generate a 10 KHz frequency on P2.1 using T0 8-bit auto-reload
//(b) Use timer 1 as an event counter to count up a 1-Hz pulse and
// display it on P0. The pulse is connected to EX1.
// Assume that XTAL = 11.0592 MHz. Set the baud rate at 9600.
// Solution:
#include <reg51.h>
sbit WAVE = P2 ^ 1;
unsigned char cnt;
void timer0() interrupt 1
{
    WAVE = ~WAVE; // toggle pin
}
void timer1() interrupt 3
{
    cnt++;    // increment counter
    P0 = cnt; // display value on pins
}

void main()
{
    cnt = 0; // set counter to 0
    TMOD = 0x42;
    TH0 = 0x46; // 10 KHz
    IE = 0x86;  // enable interrupts
    TR0 = 1;    // start timer 0
    while (1)
        ; // wait until interrupted
}
// Example 12-2
// Write an 8051 C program to send letters ‘M’, ‘D’, and ‘E’ to the LCD
// using the busy flag method.
// Solution:
#include <reg51.h>
sfr ldata = 0x90; // P1=LCD data pins
sbit rs = P2 ^ 0;
sbit rw = P2 ^ 1;
sbit en = P2 ^ 2;
sbit busy = P1 ^ 7;

void MSDelay(unsigned int itime)
{
    unsigned int i, j;
    for (i = 0; i < itime; i++)
        for (j = 0; j < 1275; j++)
            ;
}

void lcdready()
{
    busy = 1; // make the busy pin at input
    rs = 0;
    rw = 1;
    while (busy == 1)
    {           // wait here for busy flag
        en = 0; // strobe the enable pin
        MSDelay(1);
        en = 1;
    }
}

void lcdcmd(unsigned char value)
{
    lcdready();    // check the LCD busy flag
    ldata = value; // put the value on the pins
    rs = 0;
    rw = 0;
    en = 1; // strobe the enable pin
    MSDelay(1);
    en = 0;
    return;
}

void lcddata(unsigned char value)
{
    lcdready();    // check the LCD busy flag
    ldata = value; // put the value on the pins
    rs = 1;
    rw = 0;
    en = 1; // strobe the enable pin
    MSDelay(1);
    en = 0;
    return;
}

void main()
{
    lcdcmd(0x38);
    lcdcmd(0x0E);
    lcdcmd(0x01);
    lcdcmd(0x06);
    lcdcmd(0x86); // line 1, position 6
    lcddata('M');
    lcddata('D');
    lcddata('E');
}