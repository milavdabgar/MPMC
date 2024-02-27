
;<Multiplication of two 8- bit nos. using repeated Addition>

MVI D,00h 
;Initialize D register to 00
MVI A,00h
;Initialize A register to 00
LXI H,4150H
MOV B,M 
;Get the second number in B register
INX H
MOV C,M 
;Get the second number in C register
LOOP: ADD B 
;Add content of A to reg. B
JNC NEXT 
;Jump on no carry to NEXT
INR C 
;Increment the content of reg. C
NEXT: DCR C 
;decrement the content of reg. C
JNZ LOOP 
;Jump on no zero to address
STA 4152H  
;Store the result in memory
MOV A,D
STA 4153H 
;Store the MSB of result in memory
HLT