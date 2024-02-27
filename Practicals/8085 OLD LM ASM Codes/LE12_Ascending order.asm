
;<Arrange data bytes in ascending order>

LXI H,4150H
;Store the address of Block Length in HL Pair
MOV C,M
;Get Block Legth in to Register C and use it as Counter
DCR C
;Decrement Outer Loop Counter by 1
REPEAT: MOV D,C
;Use D as Inner Loop Counter
LXI H,4151H
;Store address of the 1st element of the Block in HL Pair
LOOP: MOV A,M
;Get 1st element of Block in Accumulator for Processing
INX H
;Increment HL Pair content to Point to 2nd element of Block
CMP M
;Compare A (1st Number) with M (2nd Number) and update flags
JC SKIP
;if A<M Got to label SKIP, and skip swapping of data.
MOV B,M
;Move 2nd Number from M to B
MOV M,A
;Move 1st Number from A to M
DCX H
;Set HL Pointer to 1st Slot Address
MOV M,B
;Put 2nd Number (Currently in Reg B) 
;into 1st Slot Address (M Pointed by HL).
INX H
;Set HL Pointer to 2nd Slot Address
SKIP:  DCR D
;Decrement Inner Loop Counter by 1
JNZ LOOP
;Go to lable LOOP till iteration counter becomes 0
DCR C
;Decrement Outer Loop Counter by 1
JNZ REPEAT
;Go to label REPEAT till Outer Loop Counter Becomes 0
HLT