
;<Division of two 8- bit nos. using repeated Subtraction>

LXI H,4150h  
;Get Address of Divisor(4150H) in HL Reg Pair
MOV B,M
;Get Divisor into Reg B.
MVI C,00h  
;Clear C reg. for quotient.
INX H
;Point to next location (Address of Dividend - 4151H)
MOV A,M 
;Get the Dividend into Accumulator
NEXT: CMP B 
;Compare A reg.with reg B and update flags
JC LOOP 
;If A<B it will result in carry,
;It indicates Division is complete
;Go to label LOOP and save result 
SUB B  
;Perform Subtraction (Dividend - Divisor)
INR C  
;increment the content of reg. C used for Quotient
JMP NEXT 
;Perform Repetitive Subtraction (Dividend - Divisor)
;till Dividend<Divisor.
LOOP: STA 4152h 
;Store the Quotient of result in to memory location 4152H
MOV A,C
;Get the remainder of result in Accumulator
STA 4153h  
;Store remainder in to memory location 4153H
HLT