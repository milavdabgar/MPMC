
;<Add two multibyte binary number>

lxi h,4150h
;starting addrs of source data block 1
  
lxi b,5150h
;starting addrs of source data block 2 

lxi d,6150h
;starting addrs of destination block 

stc
;set carry

cmc
;complement carry, resulting in resetting carry

mvi a,04h
;counter for block length

loop: sta 7150h
;store block legth counter to memory 

ldax b
;load 1st number from block 1 pointed by BC rp into acc

adc m
;add 2nd number to 1st number with carry

stax d
;store result to memory location pointed by DE rp

inx h
;increment HL rp content

inx b
;increment BC rp content

inx d
;increment DE rp content

lda 7150h
;load block legth counter to memory loc 7150H

dcr a
;decrement block length counter

jnz loop
;repeat the loop till counter becomes zero

mvi a,00h
;make acc zero

ral
;rotate acc left through carry

stax d
;store acc data to memory loc pointed by DE rp

hlt
;halt the program