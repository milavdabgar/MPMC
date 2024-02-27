
;<Subtraction of two 16-bit numbers>

LXI H,8765H 
;load HL with 9876H data
LXI B,4321H 
;load BC with 4321H data
MOV A,L 
;move the content of L reg. into Accumulator
SUB C  
;subtract the content of L reg. into Accumulator
STA 4150H 
;Store the LSB into 2000H
MOV A,H 
;move the content of H reg. into Accumulator
SUB B  
;subtract the content of H reg. into Accumulator
STA 4151H 
;Store the LSB into 2000H
HLT 
;Stop