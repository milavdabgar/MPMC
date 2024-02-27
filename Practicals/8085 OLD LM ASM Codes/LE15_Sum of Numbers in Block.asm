;<Sum of Numbers>

;This program reads the numbers from the memory location 50 till it 
;finds 00 (end of input) and then sums up and stores the result in 
;0080H(LOB),0081H(HOB) respectively.
; this program demonstrates 1)  comparision and 2) addition
;jmp start

;code

;start:  LXI H,4150H ;set up HL as memory pointer
	LXI H,4150H ;set up HL as memory pointer	
	MVI C,00H  ;clear C to save sum
	MOV B,C    ;Clear B to save carry

NXTBYTE: MOV A,M   ; Transfer current reading to (A)
	CPI 00h    ;Is it last reading
	JZ OUTPUT  ;If yes go to output section
	ADD C      ;Add previous sun to accumulator
	JNC SAVE  ; Skip CY register if there is no carry
	
	INR B      ;Update carry register

SAVE:   MOV C,A    ;Save sum
	INX H      ; point to next reading
	JMP NXTBYTE ;Go back to get next reading

OUTPUT:	LXI H,5150H    ;Point to 080H memory location
	MOV M,C    ;Store low-order byte of sum in 080h
	INX H   ;  ;Point to 081H memory location
	MOV M,B

HLT
