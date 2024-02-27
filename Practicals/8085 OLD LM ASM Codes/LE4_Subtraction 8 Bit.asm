
;<Subtraction of two 8-bit numbers>

MVI C,00H 
;Initialize C register to 00
LDA 4150H  
;Load the value to Accumulator.
MOV B,A 
;Move the content of Accumulator to B register.
LDA 4151H
;Load the value to Accumulator.
SUB B  
;Add the value of register B to Accumulator.
JNC LOOP 
;Jump on no carry.
CMA  
;Complement Accumulator Content
INR A 
;Increment value of register C.
INR C  
;Increment value of register C.
LOOP: STA 4152H 
;Store the value of Accumulator.
MOV A,C 
;Move content of Register C to Accumulator
STA 4153H 
;Store the value of Accumulator
HLT