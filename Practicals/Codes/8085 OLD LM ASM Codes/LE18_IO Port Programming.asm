;<IO Port programming>

jmp start;jump to code skipping data

;data starts here

port1: equ  9h
data:  equ  7fh
var1:  db   data, 0    ;like - 7fh, 0

;code starts here

start: lxi  h, var1    
;load var1 address in HL pair for addressing

mov  a, m       
;load contents of var1 in reg A (i.e. 7fh in A)

out  port1      
;send contents of reg A to port 9h

in   port1      
;read from port1 and store value in reg A

sta  var1+1     
;store contents of reg A in memory location var+1 (next to 7fh!)

hlt             
;halt execution