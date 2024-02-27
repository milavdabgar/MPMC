;This program adds value 3 to the ACC ten times
MOV A,#0 ;A=0, clear ACC
MOV R2,#10 ;load counter R2=10
AGAIN: ADD A,#03 ;add 03 to ACC
DJNZ R2,AGAIN ;repeat until R2=0,10 times
MOV R5,A ;save A in R5

;Write a program to (a) load the accumulator with the value 55H, and
;(b) complement the ACC 700 times
MOV A,#55H ;A=55H
MOV R3,#10 ;R3=10, outer loop count
NEXT: MOV R2,#70 ;R2=70, inner loop count
AGAIN: CPL A ;complement A register
DJNZ R2,AGAIN ;repeat it 70 times
DJNZ R3,NEXT

;Find the sum of the values 79H, F5H, E2H. Put the sum in registers
;R0 (low byte) and R5 (high byte).
MOV A,#0 ;A=0
MOV R5,A ;clear R5
ADD A,#79H ;A=0+79H=79H
JNC N_1 ;if CY=0, add next number
INC R5 ;if CY=1, increment R5
N_1: ADD A,#0F5H ;A=79+F5=6E and CY=1
JNC N_2 ;jump if CY=0
INC R5 ;if CY=1,increment R5 (R5=1)
N_2: ADD A,#0E2H ;A=6E+E2=50 and CY=1
JNC OVER ;jump if CY=0
INC R5 ;if CY=1, increment 5
OVER: MOV R0,A ;now R0=50H, and R5=02

;LCALL Example
ORG 0
BACK: MOV A,#55H ;load A with 55H
MOV P1,A ;send 55H to port 1
LCALL DELAY ;time delay
MOV A,#0AAH ;load A with AA (in hex)
MOV P1,A ;send AAH to port 1
LCALL DELAY
SJMP BACK ;keep doing this indefinitely

;---------- this is delay subroutine ------------
ORG 300H ;put DELAY at address 300H
DELAY: MOV R5,#0FFH ;R5=255 (FF in hex), counter
AGAIN: DJNZ R5,AGAIN ;stay here until R5 become 0
RET ;return to caller (when R5 =0)
END
	
;Use PUSH/POP in Subroutine
ORG 0
BACK: MOV A,#55H ;load A with 55H
MOV P1,A ;send 55H to p1
MOV R4,#99H
MOV R5,#67H
LCALL DELAY ;time delay
MOV A,#0AAH ;load A with AA
MOV P1,A ;send AAH to p1
LCALL DELAY
SJMP BACK ;keeping doing this

;-------this is the delay subroutine------
ORG 300H
DELAY: PUSH 4 ;push R4
PUSH 5 ;push R5
MOV R4,#0FFH;R4=FFH
NEXT: MOV R5,#0FFH;R5=FFH
AGAIN: DJNZ R5,AGAIN
DJNZ R4,NEXT
POP 5 ;POP into R5
POP 4 ;POP into R4
RET ;return to caller
END


;The following code will continuously send out to port 0 the
;alternating value 55H and AAH
BACK: MOV A,#55H
MOV P0,A
ACALL DELAY
MOV A,#0AAH
MOV P0,A
ACALL DELAY
SJMP BACK

;-------this is the delay subroutine------
DELAY: MOV R5,#0FFH ;R5=255 (FF in hex), counter
AGAIN: DJNZ R5,AGAIN ;stay here until R5 become 0
RET ;return to caller (when R5 =0)


;Port 0 is configured first as an input port by writing 1s to it, and then
;data is received from that port and sent to P1
MOV A,#0FFH ;A=FF hex
MOV P0,A ;make P0 an i/p port
;by writing it all 1s
BACK: MOV A,P0 ;get data from P0
MOV P1,A ;send it to port 1
SJMP BACK ;keep doing it


;The following code will continuously send out to port 0 the
;alternating value 55H and AAH
MOV A,#55H
BACK: MOV P1,A
ACALL DELAY
CPL A
SJMP BACK

;-------this is the delay subroutine------
DELAY: MOV R5,#0FFH ;R5=255 (FF in hex), counter
AGAIN: DJNZ R5,AGAIN ;stay here until R5 become 0
RET ;return to caller (when R5 =0)

;Port 1 is configured first as an input port by writing 1s to it, then data
;is received from that port and saved in R7 and R5
MOV A,#0FFH ;A=FF hex
MOV P1,A ;make P1 an input port
;by writing it all 1s
MOV A,P1 ;get data from P1
MOV R7,A ;save it to in reg R7
ACALL DELAY ;wait
MOV A,P1 ;another data from P1
MOV R5,A ;save it to in reg R5

;-------this is the delay subroutine------
DELAY: MOV R5,#0FFH ;R5=255 (FF in hex), counter
AGAIN: DJNZ R5,AGAIN ;stay here until R5 become 0
RET ;return to caller (when R5 =0)

;Write the following programs.
;Create a square wave of 50% duty cycle on bit 0 of port 1.
HERE: SETB P1.0 ;set to high bit 0 of port 1
LCALL DELAY ;call the delay subroutine
CLR P1.0 ;P1.0=0
LCALL DELAY
SJMP HERE ;keep doing it

;;Another way to write the above program is:
;HERE: CPL P1.0 ;set to high bit 0 of port 1
;LCALL DELAY ;call the delay subroutine
;SJMP HERE ;keep doing it

;-------this is the delay subroutine------
DELAY: MOV R5,#0FFH ;R5=255 (FF in hex), counter
AGAIN: DJNZ R5,AGAIN ;stay here until R5 become 0
RET ;return to caller (when R5 =0)

;Write a program to perform the following:
;(a) Keep monitoring the P1.2 bit until it becomes high
;(b) When P1.2 becomes high, write value 45H to port 0
;(c) Send a high-to-low (H-to-L) pulse to P2.3

SETB P1.2 ;make P1.2 an input
MOV A,#45H ;A=45H
AGAIN: JNB P1.2,AGAIN ; get out when P1.2=1
MOV P0,A ;issue A to P0
SETB P2.3 ;make P2.3 high
CLR P2.3 ;make P2.3 low for H-to-L



;Assume that bit P2.3 is an input and represents the condition of an
;oven. If it goes high, it means that the oven is hot. Monitor the bit
;continuously. Whenever it goes high, send a high-to-low pulse to port
;P1.5 to turn on a buzzer.

HERE: JNB P2.3,HERE ;keep monitoring for high
SETB P1.5 ;set bit P1.5=1
CLR P1.5 ;make high-to-low
SJMP HERE ;keep repeating


;A switch is connected to pin P1.7. Write a program to check the status
;of SW and perform the following:
;(a) If SW=0, send letter �N� to P2
;(b) If SW=1, send letter �Y� to P2

SETB P1.7 ;make P1.7 an input
AGAIN: JB P1.2,OVER ;jump if P1.7=1
MOV P2,'N' ;SW=0, issue �N� to P2
SJMP AGAIN ;keep monitoring
OVER: MOV P2,#'Y' ;SW=1, issue �Y� to P2
SJMP AGAIN ;keep monitoring

;A switch is connected to pin P1.7. Write a program to check the status
;of SW and perform the following:
;(a) If SW=0, send letter �N� to P2
;(b) If SW=1, send letter �Y� to P2
;Use the carry flag to check the switch status.

SETB P1.7 ;make P1.7 an input
AGAIN: MOV C,P1.2 ;read SW status into CF
JC OVER ;jump if SW=1
MOV P2,#'N' ;SW=0, issue �N� to P2
SJMP AGAIN ;keep monitoring
OVER: MOV P2,#'Y' ;SW=1, issue �Y� to P2
SJMP AGAIN ;keep monitoring

;Example 4-7
;A switch is connected to pin P1.0 and an LED to pin P2.7. Write a
;program to get the status of the switch and send it to the LED

SETB P1.7 ;make P1.7 an input
AGAIN: MOV C,P1.0 ;read SW status into CF
MOV P2.7,C ;send SW status to LED
SJMP AGAIN ;keep repeating


;Example 5-1
;Write code to send 55H to ports P1 and P2, using
;(a) their names (b) their addresses
;Solution :

;(a)
MOV A,#55H ;A=55H
MOV P1,A ;P1=55H
MOV P2,A ;P2=55H

;(b) From Table 5-1, P1 address=80H; P2 address=A0H
MOV A,#55H ;A=55H
MOV 80H,A ;P1=55H
MOV 0A0H,A ;P2=55H

;Example 5-2
;Show the code to push R5 and A onto the stack and then pop them
;back them into R2 and B, where B = A and R2 = R5
;Solution:
PUSH 05 ;push R5 onto stack
PUSH 0E0H ;push register A onto stack
POP 0F0H ;pop top of stack into B
;now register B = register A
POP 02 ;pop top of stack into R2
;now R2=R6


;Example 5-3
;Write a program to copy the value 55H into RAM memory locations
;40H to 41H using
;(a) direct addressing mode, (b) register indirect addressing mode
;without a loop, and (c) with a loop
;Solution:
;(a)
MOV A,#55H ;load A with value 55H
MOV 40H,A ;copy A to RAM location 40H
MOV 41H,A ;copy A to RAM location 41H
;(b)
MOV A,#55H ;load A with value 55H
MOV R0,#40H ;load the pointer. R0=40H
MOV @R0,A ;copy A to RAM R0 points to
INC R0 ;increment pointer. Now R0=41h
MOV @R0,A ;copy A to RAM R0 points to
;(c)
MOV A,#55H ;A=55H
MOV R0,#40H ;load pointer.R0=40H,
MOV R2,#02 ;load counter, R2=3
AGAIN: MOV @R0,A ;copy 55 to RAM R0 points to
INC R0 ;increment R0 pointer
DJNZ R2,AGAIN ;loop until counter = zero


;Example 5-4
;Write a program to clear 16 RAM locations starting at RAM address 60H
;Solution:
CLR A ;A=0
MOV R1,#60H ;load pointer. R1=60H
MOV R7,#16 ;load counter, R7=16
AGAIN: MOV @R1,A ;clear RAM R1 points to
INC R1 ;increment R1 pointer
DJNZ R7,AGAIN ;loop until counter=zero


;Example 5-5
;Write a program to copy a block of 10 bytes of data from 35H to 60H
;Solution:
MOV R0,#35H ;source pointer
MOV R1,#60H ;destination pointer
MOV R3,#10 ;counter
BACK: MOV A,@R0 ;get a byte from source
MOV @R1,A ;copy it to destination
INC R0 ;increment source pointer
INC R1 ;increment destination pointer
DJNZ R3,BACK ;keep doing for ten bytes


;Example 5-6
;In this program, assume that the word �USA� is burned into ROM
;locations starting at 200H. And that the program is burned into ROM
;locations starting at 0. Analyze how the program works and state
;where �USA� is stored after this program is run.
;Solution:
ORG 0000H ;burn into ROM starting at 0
MOV DPTR,#200H ;DPTR=200H look-up table addr
CLR A ;clear A(A=0)
MOVC A,@A+DPTR ;get the char from code space
MOV R0,A ;save it in R0
INC DPTR ;DPTR=201 point to next char
CLR A ;clear A(A=0)
MOVC A,@A+DPTR ;get the next char
MOV R1,A ;save it in R1
INC DPTR ;DPTR=202 point to next char
CLR A ;clear A(A=0)
MOVC A,@A+DPTR ;get the next char
MOV R2,A ;save it in R2
Here: SJMP HERE ;stay here

;Data is burned into code space starting at 200H
ORG 200H
MYDATA:DB �USA�
END ;end of program



;Example 5-8
;Write a program to get the x value from P1 and send x2 to P2,
;continuously
;Solution:
ORG 0
MOV DPTR,#300H ;LOAD TABLE ADDRESS
MOV A,#0FFH ;A=FF
MOV P1,A ;CONFIGURE P1 INPUT PORT
BACK: MOV A,P1 ;GET X
MOVC A,@A+DPTR ;GET X SQAURE FROM TABLE
MOV P2,A ;ISSUE IT TO P2
SJMP BACK ;KEEP DOING IT

ORG 300H
XSQR_TABLE: DB 0,1,4,9,16,25,36,49,64,81
END

;Example 5-10
;Write a program to toggle P1 a total of 200 times. Use RAM
;location 32H to hold your counter value instead of registers R0 � R7
;Solution:

MOV P1,#55H ;P1=55H
MOV A, P1
MOV 32H,#200 ;load counter value into RAM loc 32H
LOP1: CPL A ;toggle P1
MOV P1, A
ACALL DELAY
DJNZ 32H,LOP1 ;repeat 200 times

;-------this is the delay subroutine------
DELAY: MOV R5,#0FFH ;R5=255 (FF in hex), counter
AGAIN: DJNZ R5,AGAIN ;stay here until R5 become 0
RET ;return to caller (when R5 =0)

;Example 5-24
;A switch is connected to pin P1.7. Write a program to check the status
;of the switch and make the following decision.
;(a) If SW = 0, send �0� to P2
;(b) If SW = 1, send �1� to P2
;Solution:
SW EQU P1.7
MYDATA EQU P2
HERE: MOV C,SW
JC OVER
MOV MYDATA,#'0'
SJMP HERE
OVER: MOV MYDATA,#'1'
SJMP HERE
END
	
;Example 5-27
;Assume that the on-chip ROM has a message. Write a program to
;copy it from code space into the upper memory space starting at
;address 80H. Also, as you place a byte in upper RAM, give a copy to
;P0.
;Solution:
ORG 0
MOV DPTR,#MYDATA
MOV R1,#80H ;access the upper memory
B1: CLR A
MOVC A,@A+DPTR ;copy from code ROM
MOV @R1,A ;store in upper memory
MOV P0,A ;give a copy to P0
JZ EXIT ;exit if last byte
INC DPTR ;increment DPTR
INC R1 ;increment R1
SJMP B1 ;repeat until last byte
EXIT: SJMP $ ;stay here when finished
	

;---------------
ORG 300H
MYDATA: DB "The Promise of World Peace",0
END
	
	
;Assume that RAM locations 40 � 44H have the following values.
;Write a program to find the sum of the values. At the end of the
;program, register A should contain the low byte and R7 the high byte.
;40 = (7D)
;41 = (EB)
;42 = (C5)
;43 = (5B)
;44 = (30)
;Solution:

MOV R0,#40H ;load pointer
MOV R2,#5 ;load counter
CLR A ;A=0
MOV R7,A ;clear R7
AGAIN: ADD A,@R0 ;add the byte ptr to by R0
JNC NEXT ;if CY=0 don�t add carry
INC R7 ;keep track of carry
NEXT: INC R0 ;increment pointer
DJNZ R2,AGAIN ;repeat until R2 is zero	


;Write a program to add two 16-bit numbers. Place the sum in R7 and
;R6; R6 should have the lower byte.
;Solution:
CLR C ;make CY=0
MOV A, #0E7H ;load the low byte now A=E7H
ADD A, #8DH ;add the low byte
MOV R6, A ;save the low byte sum in R6
MOV A, #3CH ;load the high byte
ADDC A, #3BH ;add with the carry
MOV R7, A ;save the high byte sum


;Assume that 5 BCD data items are stored in RAM locations starting
;at 40H, as shown below. Write a program to find the sum of all the
;numbers. The result must be in BCD.
;40=(71)
;41=(11)
;42=(65)
;43=(59)
;44=(37)
;Solution:

MOV R0,#40H ;Load pointer
MOV R2,#5 ;Load counter
CLR A ;A=0
MOV R7,A ;Clear R7
AGAIN: ADD A,@R0 ;add the byte pointer to by R0
DA A ;adjust for BCD
JNC NEXT ;if CY=0 don�t accumulate carry
INC R7 ;keep track of carries
NEXT: INC R0 ;increment pointer
DJNZ R2,AGAIN ;repeat until R2 is 0	


;Assume that register A has packed BCD, write a program to convert
;packed BCD to two ASCII numbers and place them in R2 and R6.
MOV A,#29H ;A=29H, packed BCD
MOV R2,A ;keep a copy of BCD data
ANL A,#0FH ;mask the upper nibble (A=09)
ORL A,#30H ;make it an ASCII, A=39H(�9�)
MOV R6,A ;save it
MOV A,R2 ;A=29H, get the original data
ANL A,#0F0H ;mask the lower nibble
RR A ;rotate right
RR A ;rotate right
RR A ;rotate right
RR A ;rotate right
ORL A,#30H ;A=32H, ASCII char. �2�
MOV R2,A ;save ASCII char in R2



;Example 9-7
;Find the delay generated by timer 0 in the following code, using both
;of the Methods of Figure 9-4. Do not include the overhead due to
;instruction.
CLR P2.3 ;Clear P2.3
MOV TMOD,#01 ;Timer 0, 16-bitmode
HERE: MOV TL0,#3EH ;TL0=3Eh, the low byte
MOV TH0,#0B8H ;TH0=B8H, the high byte
SETB P2.3 ;SET high timer 0
SETB TR0 ;Start the timer 0
AGAIN: JNB TF0,AGAIN ;Monitor timer flag 0
CLR TR0 ;Stop the timer 0
CLR TF0 ;Clear TF0 for next round
CLR P2.3
;Solution:
;(a) (FFFFH � B83E + 1) = 47C2H = 18370 in decimal and 18370 �
;1.085 us = 19.93145 ms
;(b) Since TH � TL = B83EH = 47166 (in decimal) we have 65536 �
;47166 = 18370. This means that the timer counts from B38EH to
;FFFF. This plus Rolling over to 0 goes through a total of 18370 clock
;cycles, where each clock is 1.085 us in duration. Therefore, we have
;18370 � 1.085 us = 19.93145 ms as the width of the pulse.


;Example 9-8
;Modify TL and TH in Example 9-7 to get the largest time delay
;possible. Find the delay in ms. In your calculation, exclude the
;overhead due to the instructions in the loop.
;Solution:
;To get the largest delay we make TL and TH both 0. This will count
;up from 0000 to FFFFH and then roll over to zero.
CLR P2.3 ;Clear P2.3
MOV TMOD,#01 ;Timer 0, 16-bitmode
HERE: MOV TL0,#0 ;TL0=0, the low byte
MOV TH0,#0 ;TH0=0, the high byte
SETB P2.3 ;SET high P2.3
SETB TR0 ;Start timer 0
AGAIN: JNB TF0,AGAIN ;Monitor timer flag 0
CLR TR0 ;Stop the timer 0
CLR TF0 ;Clear timer 0 flag
CLR P2.3
;Making TH and TL both zero means that the timer will count from
;0000 to FFFF, and then roll over to raise the TF flag. As a result, it
;goes through a total Of 65536 states. Therefore, we have delay =
;(65536 - 0) � 1.085 us = 71.1065ms.


;Example 9-9
;The following program generates a square wave on P1.5 continuously
;using timer 1 for a time delay. Find the frequency of the square
;wave if XTAL = 11.0592 MHz. In your calculation do not
;include the overhead due to Instructions in the loop.
MOV TMOD,#10;Timer 1, mod 1 (16-bitmode)
AGAIN: MOV TL1,#34H ;TL1=34H, low byte of timer
MOV TH1,#76H ;TH1=76H, high byte timer
SETB TR1 ;start the timer 1
BACK: JNB TF1,BACK ;till timer rolls over
CLR TR1 ;stop the timer 1
CPL P1.5 ;comp. p1. to get hi, lo
CLR TF1 ;clear timer flag 1
SJMP AGAIN ;is not auto-reload
;Solution:
;Since FFFFH � 7634H = 89CBH + 1 = 89CCH and 89CCH = 35276
;clock count and 35276 � 1.085 us = 38.274 ms for half of the
;square wave. The frequency = 13.064Hz.
;Also notice that the high portion and low portion of the square wave
;pulse are equal. In the above calculation, the overhead due to all
;the instruction in the loop is not included.


;Example 9-10
;Assume that XTAL = 11.0592 MHz. What value do we need to load
;the timer�s register if we want to have a time delay of 5 ms
;(milliseconds)? Show the program for timer 0 to create a pulse width
;of 5 ms on P2.3.
;Solution:
;Since XTAL = 11.0592 MHz, the counter counts up every 1.085 us.
;This means that out of many 1.085 us intervals we must make a 5 ms
;pulse. To get that, we divide one by the other. We need 5 ms / 1.085
;us = 4608 clocks. To Achieve that we need to load into TL and TH
;the value 65536 � 4608 = EE00H. Therefore, we have TH = EE and TL = 00.
CLR P2.3 ;Clear P2.3
MOV TMOD,#01 ;Timer 0, 16-bitmode
HERE: MOV TL0,#0 ;TL0=0, the low byte
MOV TH0,#0EEH ;TH0=EE, the high byte
SETB P2.3 ;SET high P2.3
SETB TR0 ;Start timer 0
AGAIN: JNB TF0,AGAIN ;Monitor timer flag 0
CLR TR0 ;Stop the timer 0
CLR TF0 ;Clear timer 0 flag


;Example 9-11
;Assume that XTAL = 11.0592 MHz, write a program to generate a
;square wave of 2 kHz frequency on pin P1.5.
;Solution:
;This is similar to Example 9-10, except that we must toggle the bit to
;generate the square wave. Look at the following steps.
;(a) T = 1 / f = 1 / 2 kHz = 500 us the period of square wave.
;(b) 1 / 2 of it for the high and low portion of the pulse is 250 us.
;(c) 250 us / 1.085 us = 230 and 65536 � 230 = 65306 which in hex
;is FF1AH.
;(d) TL = 1A and TH = FF, all in hex. The program is as follow.
MOV TMOD,#01 ;Timer 0, 16-bitmode
AGAIN: MOV TL1,#1AH ;TL1=1A, low byte of timer
MOV TH1,#0FFH ;TH1=FF, the high byte
SETB TR1 ;Start timer 1
BACK: JNB TF1,BACK ;until timer rolls over
CLR TR1 ;Stop the timer 1
CLR P1.5 ;Clear timer flag 1
CLR TF1 ;Clear timer 1 flag
SJMP AGAIN ;Reload timer


;Example 9-12
;Assume XTAL = 11.0592 MHz, write a program to generate a square
;wave of 50 kHz frequency on pin P2.3.
;Solution:
;Look at the following steps.
;(a) T = 1 / 50 = 20 ms, the period of square wave.
;(b) 1 / 2 of it for the high and low portion of the pulse is 10 ms.
;(c) 10 ms / 1.085 us = 9216 and 65536 � 9216 = 56320 in decimal,
;and in hex it is DC00H.
;(d) TL = 00 and TH = DC (hex).
MOV TMOD,#10H ;Timer 1, mod 1
AGAIN: MOV TL1,#00 ;TL1=00,low byte of timer
MOV TH1,#0DCH ;TH1=DC, the high byte
SETB TR1 ;Start timer 1
BACK: JNB TF1,BACK ;until timer rolls over
CLR TR1 ;Stop the timer 1
CLR P2.3 ;Comp. p2.3 to get hi, lo
SJMP AGAIN ;Reload timer, mode 1 isn�t auto-reload

;Example 9-14
;Assume XTAL = 11.0592 MHz, find the frequency of the square
;wave generated on pin P1.0 in the following program
MOV TMOD,#20H ;T1/8-bit/auto reload
MOV TH1,#5 ;TH1 = 5
SETB TR1 ;start the timer 1
BACK: JNB TF1,BACK ;till timer rolls over
CPL P1.0 ;P1.0 to hi, lo
CLR TF1 ;clear Timer 1 flag
SJMP BACK ;mode 2 is auto-reload
;Solution:
;First notice the target address of SJMP. In mode 2 we do not need to
;reload TH since it is auto-reload. Now (256 - 05) � 1.085 us =
;251 � 1.085 us = 272.33 us is the high portion of the pulse. Since
;it is a 50% duty cycle square wave, the period T is twice that; as
;a result T = 2 � 272.33 us = 544.67 us and the frequency =
;1.83597 kHz



;Example 9-15
;Find the frequency of a square wave generated on pin P1.0.
;Solution:
MOV TMOD,#2H ;Timer 0, mod 2 (8-bit, auto reload)
MOV TH0,#0
AGAIN: MOV R5,#250 ;multiple delay count
ACALL DELAY
CPL P1.0
SJMP AGAIN
DELAY: SETB TR0 ;start the timer 0
BACK: JNB TF0,BACK ;stay timer rolls over
CLR TR0 ;stop timer
CLR TF0 ;clear TF for next round
DJNZ R5,DELAY
RET
;T = 2 ( 250 � 256 � 1.085 us ) = 138.88ms, and frequency = 72 Hz


;Example 9-18
;Assuming that clock pulses are fed into pin T1, write a program
;for counter 1 in mode 2 to count the pulses and display the state
;of the TL1 count on P2, which connects to 8 LEDs.
;Solution:
MOV TMOD,#01100000B ;counter 1, mode 2, C/T=1 external pulses
MOV TH1,#0 ;clear TH1
SETB P3.5 ;make T1 input
AGAIN: SETB TR1 ;start the counter
BACK: MOV A,TL1 ;get copy of TL
MOV P2,A ;display it on port 2
JNB TF1,Back ;keep doing, if TF = 0
CLR TR1 ;stop the counter 1
CLR TF1 ;make TF=0
SJMP AGAIN ;keep doing it


;Write a program for the 8051 to transfer letter �A� serially at 4800
;baud, continuously.
;Solution:
MOV TMOD,#20H ;timer 1,mode 2(auto reload)
MOV TH1,#-6 ;4800 baud rate
MOV SCON,#50H ;8-bit, 1 stop, REN enabled
SETB TR1 ;start timer 1
AGAIN: MOV SBUF,#"A" ;letter �A� to transfer
HERE: JNB TI,HERE ;wait for the last bit
CLR TI ;clear TI for next char
SJMP AGAIN ;keep sending A

;Write a program for the 8051 to transfer �YES� serially at 9600
;baud, 8-bit data, 1 stop bit, do this continuously
;Solution:
MOV TMOD,#20H ;timer 1,mode 2(auto reload)
MOV TH1,#-3 ;9600 baud rate
MOV SCON,#50H ;8-bit, 1 stop, REN enabled
SETB TR1 ;start timer 1
AGAIN: MOV A,#"Y" ;transfer �Y�
ACALL TRANS
MOV A,#"E" ;transfer �E�
ACALL TRANS
MOV A,#"S" ;transfer �S�
ACALL TRANS
SJMP AGAIN ;keep doing it
;serial data transfer subroutine
TRANS: MOV SBUF,A ;load SBUF
HERE: JNB TI,HERE ;wait for the last bit
CLR TI ;get ready for next byte
RET


;Write a program for the 8051 to receive bytes of data serially, and
;put them in P1, set the baud rate at 4800, 8-bit data, and 1 stop bit
;Solution:
MOV TMOD,#20H ;timer 1,mode 2(auto reload)
MOV TH1,#-6 ;4800 baud rate
MOV SCON,#50H ;8-bit, 1 stop, REN enabled
SETB TR1 ;start timer 1
HERE: JNB RI,HERE ;wait for char to come in
MOV A,SBUF ;saving incoming byte in A
MOV P1,A ;send to port 1
CLR RI ;get ready to receive next byte
SJMP HERE ;keep getting data

;Example 10-5
;Assume that the 8051 serial port is connected to the COM port of
;IBM PC, and on the PC, we are using the terminal.exe program to
;send and receive data serially. P1 and P2 of the 8051 are connected
;to LEDs and switches, respectively. Write an 8051 program to (a)
;send to PC the message �We Are Ready�, (b) receive any data send
;by PC and put it on LEDs connected to P1, and (c) get data on
;switches connected to P2 and send it to PC serially. The program
;should perform part (a) once, but parts (b) and (c) continuously, use
;4800 baud rate.

;Solution:
ORG 0
MOV P2,#0FFH ;make P2 an input port
MOV TMOD,#20H ;timer 1, mode 2
MOV TH1,#0FAH ;4800 baud rate
MOV SCON,#50H ;8-bit, 1 stop, REN enabled
SETB TR1 ;start timer 1
MOV DPTR,#MYDATA ;load pointer for message
H_1: CLR A
MOVC A,@A+DPTR ;get the character
JZ B_1 ;if last character get out
ACALL SEND ;otherwise call transfer
INC DPTR ;next one
SJMP H_1 ;stay in loop
B_1: MOV a,P2 ;read data on P2
ACALL SEND ;transfer it serially
ACALL RECV ;get the serial data
MOV P1,A ;display it on LEDs
SJMP B_1 ;stay in loop indefinitely

;----serial data transfer. ACC has the data------
SEND: MOV SBUF,A ;load the data
H_2: JNB TI,H_2 ;stay here until last bit gone
CLR TI ;get ready for next char
RET ;return to caller

;----Receive data serially in ACC----------------
RECV: JNB RI,RECV ;wait here for char
MOV A,SBUF ;save it in ACC
CLR RI ;get ready for next char
RET ;return to caller

;-----The message---------------
MYDATA: DB "We Are Ready",0
END

;Example 10-6
;Assume that XTAL = 11.0592 MHz for the following program,
;state (a) what this program does, (b) compute the frequency used
;by timer 1 to set the baud rate, and (c) find the baud rate of the data transfer.
;Solution:
;(a) This program transfers ASCII letter B (01000010
;binary) continuously
;(b) With XTAL = 11.0592 MHz and SMOD = 1 in the
;above program, we have:
;11.0592 / 12 = 921.6 kHz machine cycle frequency.
;921.6 / 16 = 57,600 Hz frequency used by timer 1
;to set the baud rate.
;57600 / 3 = 19,200, the baud rate.

MOV A,PCON ;A=PCON
MOV ACC.7 ;make D7=1
MOV PCON,A ;SMOD=1, double baud rate with same XTAL freq.
MOV TMOD,#20H ;timer 1, mode 2
MOV TH1,-3 ;19200 (57600/3 =19200)
MOV SCON,#50H ;8-bit data, 1 stop bit, RI enabled
SETB TR1 ;start timer 1
MOV A,#�B� ;transfer letter B
A_1: CLR TI ;make sure TI=0
MOV SBUF,A ;transfer it
H_1: JNB TI,H_1 ;stay here until the last bit is gone
SJMP A_1 ;keep sending �B� again




;Example 10-10
;Write a program to send the message �The Earth is but One
;Country� to serial port. Assume a SW is connected to pin P1.2.
;Monitor its status and set the baud rate as follows:
;SW = 0, 4800 baud rate
;SW = 1, 9600 baud rate
;Assume XTAL = 11.0592 MHz, 8-bit data, and 1 stop bit.
;Solution:
SW BIT P1.2
ORG 0H ;starting position
MAIN:
MOV TMOD,#20H
MOV TH1,#-6 ;4800 baud rate (default)
MOV SCON,#50H
SETB TR1
SETB SW ;make SW an input
S1: JNB SW,SLOWSP ;check SW status
MOV A,PCON ;read PCON
SETB ACC.7 ;set SMOD high for 9600
MOV PCON,A ;write PCON
SJMP OVER ;send message

SLOWSP:
MOV A,PCON ;read PCON
SETB ACC.7 ;set SMOD low for 4800
MOV PCON,A ;write PCON
OVER: MOV DPTR,#MESS1 ;load address to message
FN: CLR A
MOVC A,@A+DPTR ;read value
JZ S1 ;check for end of line
ACALL SENDCOM ;send value to serial port
INC DPTR ;move to next value
SJMP FN ;repeat
;------------
SENDCOM:
MOV SBUF,A ;place value in buffer
HERE: JNB TI,HERE ;wait until transmitted
CLR TI ;clear
RET ;return
;------------
MESS1: DB "The Earth is but One Country",0
END
	
	
;Example 11-2
;Write a program that continuously get 8-bit data from P0 and sends it
;to P1 while simultaneously creating a square wave of 200 �s period
;on pin P2.1. Use timer 0 to create the square wave. Assume that
;XTAL = 11.0592 MHz.
;Solution:
;We will use timer 0 in mode 2 (auto reload). TH0 = 100/1.085 us = 92

;--upon wake-up go to main, avoid using
;memory allocated to Interrupt Vector Table
ORG 0000H
LJMP MAIN ;by-pass interrupt vector table
;
;--ISR for timer 0 to generate square wave
ORG 000BH ;Timer 0 interrupt vector table
CPL P2.1 ;toggle P2.1 pin
RETI ;return from ISR	

;--The main program for initialization
ORG 0030H ;after vector table space
MAIN: MOV TMOD,#02H ;Timer 0, mode 2
MOV P0,#0FFH ;make P0 an input port
MOV TH0,#-92 ;TH0=A4H for -92
MOV IE,#82H ;IE=10000010 (bin) enable Timer 0
SETB TR0 ;Start Timer 0
BACK: MOV A,P0 ;get data from P0
MOV P1,A ;issue it to P1
SJMP BACK ;keep doing it loop unless interrupted by TF0
END


;Example 11-3
;Rewrite Example 11-2 to create a square wave that has a high portion
;of 1085 us and a low portion of 15 us. Assume XTAL=11.0592MHz.
;Use timer 1.
;Solution:
;Since 1085 us is 1000 � 1.085 we need to use mode 1 of timer 1.
;--upon wake-up go to main, avoid using
;memory allocated to Interrupt Vector Table
ORG 0000H
LJMP MAIN ;by-pass int. vector table
;--ISR for timer 1 to generate square wave
ORG 001BH ;Timer 1 int. vector table
LJMP ISR_T1 ;jump to ISR

;--The main program for initialization
ORG 0030H ;after vector table space
MAIN: MOV TMOD,#10H ;Timer 1, mode 1
MOV P0,#0FFH ;make P0 an input port
MOV TL1,#018H ;TL1=18 low byte of -1000
MOV TH1,#0FCH ;TH1=FC high byte of -1000
MOV IE,#88H ;10001000 enable Timer 1 int
SETB TR1 ;Start Timer 1
BACK: MOV A,P0 ;get data from P0
MOV P1,A ;issue it to P1
SJMP BACK ;keep doing it
;Timer 1 ISR. Must be reloaded, not auto-reload
ISR_T1: CLR TR1 ;stop Timer 1
MOV R2,#4 ; 2MC
CLR P2.1 ;P2.1=0, start of low portion
HERE: DJNZ R2,HERE ;4x2 machine cycle 8MC
MOV TL1,#18H ;load T1 low byte value 2MC
MOV TH1,#0FCH;load T1 high byte value 2MC
SETB TR1 ;starts timer1 1MC
SETB P2.1 ;P2.1=1,back to high 1MC
RETI ;return to main
END

;Example 11-5
;Assume that the INT1 pin is connected to a switch that is normally
;high. Whenever it goes low, it should turn on an LED. The LED is
;connected to P1.3 and is normally off. When it is turned on it should
;stay on for a fraction of a second. As long as the switch is pressed low,
;the LED should stay on.
;Solution:
ORG 0000H
LJMP MAIN ;by-pass interrupt vector table
;--ISR for INT1 to turn on LED
ORG 0013H ;INT1 ISR
SETB P1.3 ;turn on LED
MOV R3,#255
BACK: DJNZ R3,BACK ;keep LED on for a while
CLR P1.3 ;turn off the LED
RETI ;return from ISR
;--MAIN program for initialization
ORG 30H
MAIN: MOV IE,#10000100B ;enable external INT 1
HERE: SJMP HERE ;stay here until get interrupted
END
	
;Assume that pin 3.3 (INT1) is connected to a pulse generator, write a
;program in which the falling edge of the pulse will send a high to
;P1.3, which is connected to an LED (or buzzer). In other words, the
;LED is turned on and off at the same rate as the pulses are applied to
;the INT1 pin.
;Solution:
ORG 0000H
LJMP MAIN
;--ISR for hardware interrupt INT1 to turn on LED
ORG 0013H ;INT1 ISR
SETB P1.3 ;turn on LED
MOV R3,#255
BACK: DJNZ R3,BACK ;keep the buzzer on for a while
CLR P1.3 ;turn off the buzzer
RETI ;return from ISR
;------MAIN program for initialization
ORG 30H
MAIN: SETB TCON.2 ;make INT1 edge-triggered int.
MOV IE,#10000100B ;enable External INT 1
HERE: SJMP HERE ;stay here until get interrupted
END
	

;Example 11-8
;Write a program in which the 8051 reads data from P1 and writes it to
;P2 continuously while giving a copy of it to the serial COM port to be
;transferred serially. Assume that XTAL=11.0592. Set the baud rate at 9600.
;Solution:
ORG 0000H
LJMP MAIN
ORG 23H
LJMP SERIAL ;jump to serial int ISR
ORG 30H
MAIN: MOV P1,#0FFH ;make P1 an input port
MOV TMOD,#20H ;timer 1, auto reload
MOV TH1,#0FDH ;9600 baud rate
MOV SCON,#50H ;8-bit,1 stop, ren enabled
MOV IE,10010000B ;enable serial int.
SETB TR1 ;start timer 1
BACK: MOV A,P1 ;read data from port 1
MOV SBUF,A ;give a copy to SBUF
MOV P2,A ;send it to P2
SJMP BACK ;stay in loop indefinitely

;-----------------SERIAL PORT ISR
ORG 100H
SERIAL: JB TI,TRANS;jump if TI is high
MOV A,SBUF ;otherwise due to receive
CLR RI ;clear RI since CPU doesn�t
RETI ;return from ISR
TRANS: CLR TI ;clear TI since CPU doesn�t
RETI ;return from ISR
END
	
;Example 11-9
;Write a program in which the 8051 gets data from P1 and sends it to
;P2 continuously while incoming data from the serial port is sent to P0.
;Assume that XTAL=11.0592. Set the baud rata at 9600.
;Solution:
ORG 0000H
LJMP MAIN
ORG 23H
LJMP SERIAL ;jump to serial int ISR
ORG 30H
MAIN: MOV P1,#0FFH ;make P1 an input port
MOV TMOD,#20H ;timer 1, auto reload
MOV TH1,#0FDH ;9600 baud rate
MOV SCON,#50H ;8-bit,1 stop, ren enabled
MOV IE,10010000B ;enable serial int.
SETB TR1 ;start timer 1
BACK: MOV A,P1 ;read data from port 1
MOV P2,A ;send it to P2
SJMP BACK ;stay in loop indefinitely	

;-----------------SERIAL PORT ISR
ORG 100H
SERIAL: JB TI,TRANS;jump if TI is high
MOV A,SBUF ;otherwise due to receive
MOV P0,A ;send incoming data to P0
CLR RI ;clear RI since CPU doesn�t
RETI ;return from ISR
TRANS: CLR TI ;clear TI since CPU doesn�t
RETI ;return from ISR
END

;Example 11-10
;Write a program using interrupts to do the following:
;(a) Receive data serially and sent it to P0,
;(b) Have P1 port read and transmitted serially, and a copy given to
;P2,
;(c) Make timer 0 generate a square wave of 5kHz frequency on P0.1.
;Assume that XTAL-11,0592. Set the baud rate at 4800.
;Solution:
ORG 0
LJMP MAIN
ORG 000BH ;ISR for timer 0
CPL P0.1 ;toggle P0.1
RETI ;return from ISR
ORG 23H ;
LJMP SERIAL ;jump to serial interrupt ISR
ORG 30H
MAIN: MOV P1,#0FFH ;make P1 an input port
MOV TMOD,#22H;timer 1,mode 2(auto reload)
MOV TH1,#0F6H;4800 baud rate
MOV SCON,#50H;8-bit, 1 stop, ren enabled
MOV TH0,#-92 ;for 5kHZ wave
MOV IE,10010010B ;enable serial int.
SETB TR1 ;start timer 1
SETB TR0 ;start timer 0
BACK: MOV A,P1 ;read data from port 1
MOV SBUF,A ;give a copy to SBUF
MOV P2,A ;send it to P2
SJMP BACK ;stay in loop indefinitely
;-----------------SERIAL PORT ISR
ORG 100H
SERIAL:JB TI,TRANS;jump if TI is high
MOV A,SBUF ;otherwise due to receive
MOV P0,A ;send serial data to P0
CLR RI ;clear RI since CPU doesn�t
RETI ;return from ISR
TRANS: CLR TI ;clear TI since CPU doesn�t
RETI ;return from ISR
END


;To send any of the commands to the LCD, make pin RS=0. For data,
;make RS=1. Then send a high-to-low pulse to the E pin to enable the
;internal latch of the LCD. This is shown in the code below.
;calls a time delay before sending next data/command
;P1.0-P1.7 are connected to LCD data pins D0-D7
;P2.0 is connected to RS pin of LCD
;P2.1 is connected to R/W pin of LCD
;P2.2 is connected to E pin of LCD

ORG 0
	
MOV A,#38H ;INIT. LCD 2 LINES, 5X7 MATRIX
ACALL COMNWRT ;call command subroutine
ACALL DELAY ;give LCD some time

MOV A,#0EH ;display on, cursor on
ACALL COMNWRT ;call command subroutine
ACALL DELAY ;give LCD some time

MOV A,#01 ;clear LCD
ACALL COMNWRT ;call command subroutine
ACALL DELAY ;give LCD some time

MOV A,#06H ;shift cursor right
ACALL COMNWRT ;call command subroutine
ACALL DELAY ;give LCD some time

MOV A,#84H ;cursor at line 1, pos. 4
ACALL COMNWRT ;call command subroutine
ACALL DELAY ;give LCD some time

MOV A,#'N' ;display letter N
ACALL DATAWRT ;call display subroutine
ACALL DELAY ;give LCD some time

MOV A,#'O' ;display letter O
ACALL DATAWRT ;call display subroutine
AGAIN: SJMP AGAIN ;stay here

COMNWRT: ;send command to LCD
	MOV P1,A ;copy reg A to port 1
	CLR P2.0 ;RS=0 for command
	CLR P2.1 ;R/W=0 for write
	SETB P2.2 ;E=1 for high pulse
	CLR P2.2 ;E=0 for H-to-L pulse
	RET
DATAWRT: ;write data to LCD
	MOV P1,A ;copy reg A to port 1
	CLR P2.0 ;RS=0 for command
	CLR P2.1 ;R/W=0 for write
	SETB P2.2 ;E=1 for high pulse
	CLR P2.2 ;E=0 for H-to-L pulse
	RET
DELAY: MOV R3,#50 ;50 or higher for fast CPUs
HERE2: MOV R4,#255 ;R4 = 255
HERE: DJNZ R4,HERE ;stay until R4 becomes 0
	DJNZ R3,HERE2
	RET
	END
		

;Check busy flag before sending data, command to LCD
;p1=data pin
;P2.0 connected to RS pin
;P2.1 connected to R/W pin
;P2.2 connected to E pin
ORG 0
MOV A,#38H ;init. LCD 2 lines ,5x7 matrix
ACALL COMMAND ;issue command
MOV A,#0EH ;LCD on, cursor on
ACALL COMMAND ;issue command
MOV A,#01H ;clear LCD command
ACALL COMMAND ;issue command
MOV A,#06H ;shift cursor right
ACALL COMMAND ;issue command
MOV A,#86H ;cursor: line 1, pos. 6
ACALL COMMAND ;command subroutine
MOV A,#'N' ;display letter N
ACALL DATA_DISPLAY
MOV A,#'O' ;display letter O
ACALL DATA_DISPLAY
HERE:SJMP HERE ;STAY HERE

COMMAND:
	ACALL READY ;is LCD ready?
	MOV P1,A ;issue command code
	CLR P2.0 ;RS=0 for command
	CLR P2.1 ;R/W=0 to write to LCD
	SETB P2.2 ;E=1 for H-to-L pulse
	CLR P2.2 ;E=0,latch in
	RET
DATA_DISPLAY:
	ACALL READY ;is LCD ready?
	MOV P1,A ;issue data
	SETB P2.0 ;RS=1 for data
	CLR P2.1 ;R/W =0 to write to LCD
	SETB P2.2 ;E=1 for H-to-L pulse
	CLR P2.2 ;E=0,latch in
	RET
READY:
	SETB P1.7 ;make P1.7 input port
	CLR P2.0 ;RS=0 access command reg
	SETB P2.1 ;R/W=1 read command reg
	
;read command reg and check busy flag
BACK:SETB P2.2 ;E=1 for H-to-L pulse
	CLR P2.2 ;E=0 H-to-L pulse
	JB P1.7,BACK ;stay until busy flag=0
	RET
	END

;To send any of the commands to the LCD, make pin RS=0. For data,
;make RS=1. Then send a high-to-low pulse to the E pin to enable the
;internal latch of the LCD. This is shown in the code below.
;calls a time delay before sending next data/command
;P1.0-P1.7 are connected to LCD data pins D0-D7
;P2.0 is connected to RS pin of LCD
;P2.1 is connected to R/W pin of LCD
;P2.2 is connected to E pin of LCD
ORG 0H

MOV A,#38H ;INIT. LCD 2 LINES, 5X7 MATRIX
ACALL COMNWRT ;call command subroutine
ACALL DELAY ;give LCD some time

MOV A,#0EH ;display on, cursor on
ACALL COMNWRT ;call command subroutine
ACALL DELAY ;give LCD some time

MOV A,#01 ;clear LCD
ACALL COMNWRT ;call command subroutine
ACALL DELAY ;give LCD some time

MOV A,#06H ;shift cursor right
ACALL COMNWRT ;call command subroutine
ACALL DELAY ;give LCD some time

MOV A,#84H ;cursor at line 1, pos. 4
ACALL COMNWRT ;call command subroutine
ACALL DELAY ;give LCD some time

MOV A,#'N' ;display letter N
ACALL DATAWRT ;call display subroutine
ACALL DELAY ;give LCD some time

MOV A,#'O' ;display letter O
ACALL DATAWRT ;call display subroutine
AGAIN: SJMP AGAIN ;stay here

COMNWRT: ;send command to LCD
	MOV P1,A ;copy reg A to port 1
	CLR P2.0 ;RS=0 for command
	CLR P2.1 ;R/W=0 for write
	SETB P2.2 ;E=1 for high pulse
	ACALL DELAY ;give LCD some time
	CLR P2.2 ;E=0 for H-to-L pulse
	RET
DATAWRT: ;write data to LCD
	MOV P1,A ;copy reg A to port 1
	SETB P2.0 ;RS=1 for data
	CLR P2.1 ;R/W=0 for write
	SETB P2.2 ;E=1 for high pulse
	ACALL DELAY ;give LCD some time
	CLR P2.2 ;E=0 for H-to-L pulse
	RET
DELAY: MOV R3,#50 ;50 or higher for fast CPUs
HERE2: MOV R4,#255 ;R4 = 255
HERE: DJNZ R4,HERE ;stay until R4 becomes 0
DJNZ R3,HERE2
RET
END


;Check busy flag before sending data, command to LCD
;p1=data pin
;P2.0 connected to RS pin
;P2.1 connected to R/W pin
;P2.2 connected to E pin
ORG 0H

MOV A,#38H ;init. LCD 2 lines ,5x7 matrix
ACALL COMMAND ;issue command

MOV A,#0EH ;LCD on, cursor on
ACALL COMMAND ;issue command

MOV A,#01H ;clear LCD command
ACALL COMMAND ;issue command

MOV A,#06H ;shift cursor right
ACALL COMMAND ;issue command

MOV A,#86H ;cursor: line 1, pos. 6
ACALL COMMAND ;command subroutine

MOV A,#'N' ;display letter N
ACALL DATA_DISPLAY

MOV A,#'O' ;display letter O
ACALL DATA_DISPLAY
HERE:SJMP HERE ;STAY HERE

COMMAND:
	ACALL READY ;is LCD ready?
	MOV P1,A ;issue command code
	CLR P2.0 ;RS=0 for command
	CLR P2.1 ;R/W=0 to write to LCD
	SETB P2.2 ;E=1 for H-to-L pulse
	CLR P2.2 ;E=0,latch in
	RET
DATA_DISPLAY:
	ACALL READY ;is LCD ready?
	MOV P1,A ;issue data
	SETB P2.0 ;RS=1 for data
	CLR P2.1 ;R/W =0 to write to LCD
	SETB P2.2 ;E=1 for H-to-L pulse
	CLR P2.2 ;E=0,latch in
	RET
READY:
	SETB P1.7 ;make P1.7 input port
	CLR P2.0 ;RS=0 access command reg
	SETB P2.1 ;R/W=1 read command reg
	;read command reg and check busy flag
BACK:SETB P2.2 ;E=1 for H-to-L pulse
CLR P2.2 ;E=0 H-to-L pulse
JB P1.7,BACK ;stay until busy flag=0
RET
END


;Call a time delay before sending next data/command
; P1.0-P1.7=D0-D7, P2.0=RS, P2.1=R/W, P2.2=E
ORG 0
MOV DPTR,#MYCOM
C1: CLR A
	MOVC A,@A+DPTR
	ACALL COMNWRT ;call command subroutine
	ACALL DELAY ;give LCD some time
	INC DPTR
	JZ SEND_DAT
	SJMP C1
SEND_DAT:
MOV DPTR,#MYDATA
D1: CLR A
	MOVC A,@A+DPTR
	ACALL DATAWRT ;call command subroutine
	ACALL DELAY ;give LCD some time
	INC DPTR
	JZ AGAIN
	SJMP D1
AGAIN: SJMP AGAIN ;stay here

COMNWRT: ;send command to LCD
	MOV P1,A ;copy reg A to P1
	CLR P2.0 ;RS=0 for command
	CLR P2.1 ;R/W=0 for write
	SETB P2.2 ;E=1 for high pulse
	ACALL DELAY ;give LCD some time
	CLR P2.2 ;E=0 for H-to-L pulse
	RET
DATAWRT: ;write data to LCD
	MOV P1,A ;copy reg A to port 1
	SETB P2.0 ;RS=1 for data
	CLR P2.1 ;R/W=0 for write
	SETB P2.2 ;E=1 for high pulse
	ACALL DELAY ;give LCD some time
	CLR P2.2 ;E=0 for H-to-L pulse
	RET
DELAY: MOV R3,#250 ;50 or higher for fast CPUs
HERE2: MOV R4,#255 ;R4 = 255
HERE: DJNZ R4,HERE ;stay until R4 becomes 0
DJNZ R3,HERE2
RET

;ORG 300H
;MYCOM: DB 38H,0EH,01,06,84H,0 ; commands and null
;MYDATA: DB "HELLO",0
;END

;Program 12-4: Keyboard Program
;keyboard subroutine. This program sends the ASCII
;code for pressed key to P0.1
;P1.0-P1.3 connected to rows, P2.0-P2.3 to column
MOV P2,#0FFH ;make P2 an input port
K1: MOV P1,#0 ;ground all rows at once
MOV A,P2 ;read all col
;(ensure keys open)
ANL A,00001111B ;masked unused bits
CJNE A,#00001111B,K1 ;till all keys release
K2: ACALL DELAY ;call 20 msec delay
MOV A,P2 ;see if any key is pressed
ANL A,00001111B ;mask unused bits
CJNE A,#00001111B,OVER;key pressed, find row
SJMP K2 ;check till key pressed
OVER: ACALL DELAY ;wait 20 msec debounce time
MOV A,P2 ;check key closure
ANL A,00001111B ;mask unused bits
CJNE A,#00001111B,OVER1;key pressed, find row
SJMP K2 ;if none, keep polling
OVER1: MOV P1, #11111110B ;ground row 0
MOV A,P2 ;read all columns
ANL A,#00001111B ;mask unused bits
CJNE A,#00001111B,ROW_0 ;key row 0, find col.
MOV P1,#11111101B ;ground row 1
MOV A,P2 ;read all columns
ANL A,#00001111B ;mask unused bits
CJNE A,#00001111B,ROW_1 ;key row 1, find col.
MOV P1,#11111011B ;ground row 2
MOV A,P2 ;read all columns
ANL A,#00001111B ;mask unused bits
CJNE A,#00001111B,ROW_2 ;key row 2, find col.
MOV P1,#11110111B ;ground row 3
MOV A,P2 ;read all columns
ANL A,#00001111B ;mask unused bits
CJNE A,#00001111B,ROW_3 ;key row 3, find col.
LJMP K2 ;if none, false input, repeat

ROW_0: MOV DPTR,#KCODE0 ;set DPTR=start of row 0
SJMP FIND ;find col. Key belongs to
ROW_1: MOV DPTR,#KCODE1 ;set DPTR=start of row
SJMP FIND ;find col. Key belongs to
ROW_2: MOV DPTR,#KCODE2 ;set DPTR=start of row 2
SJMP FIND ;find col. Key belongs to
ROW_3: MOV DPTR,#KCODE3 ;set DPTR=start of row 3
FIND: RRC A ;see if any CY bit low
JNC MATCH ;if zero, get ASCII code
INC DPTR ;point to next col. addr
SJMP FIND ;keep searching
MATCH: CLR A ;set A=0 (match is found)
MOVC A,@A+DPTR ;get ASCII from table
MOV P0,A ;display pressed key
LJMP K1

;ASCII LOOK-UP TABLE FOR EACH ROW
ORG 300H
KCODE0: DB '0','1','2','3' ;ROW 0
KCODE1: DB '4','5','6','7' ;ROW 1
KCODE2: DB '8','9','A','B' ;ROW 2
KCODE3: DB 'C','D','E','F' ;ROW 3

;---------- this is delay subroutine ------------
ORG 400H ;put DELAY at address 300H
DELAY: MOV R5,#0FFH ;R5=255 (FF in hex), counter
AGAIN: DJNZ R5,AGAIN ;stay here until R5 become 0
RET ;return to caller (when R5 =0)

END
