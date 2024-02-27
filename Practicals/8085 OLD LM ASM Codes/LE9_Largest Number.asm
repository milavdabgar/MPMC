;<Find largest Number From an array>

LXI H,4150H 
;Load H-L pair with address 4150H

MOV C,M 
;Move counter from memory to reg. C.

INX H
;Increment H-L pair.

MOV A,M 
;Move the 1 st number from memory to reg. A

DCR C 
;Decrement counter.

LOOP: INX H
;Increment H-L pair.

MOV B,M
;Move the next number from memory to reg. B

CMP B  
;Compare B with A.

JNC AHEAD
;Jump to AHEAD if there is not a carry.

MOV A,B 
;Move largest from reg. B to reg. A.

AHEAD: DCR C
;Decrement counter.

JNZ LOOP
;Jump to LOOP if counter is not zero. 

INX H
;Increment H-L pair.

MOV M,A
;Move the result from reg. A to memory.

HLT