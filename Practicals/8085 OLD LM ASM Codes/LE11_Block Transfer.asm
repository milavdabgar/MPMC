
;<Transfer Block of data bytes from one memory location to another>

MVI C,05H  
;Initialize counter
LXI H,4150H  
;Initialize source memory pointer
LXI D,5150H  
;Initialize destination memory pointer
BACK: MOV A,M   
;Get byte from source memory block
STAX D 
;Store byte in the destination memory block
INX H  
;Increment source memory pointer
INX D  
;Increment destination memory pointer
DCR C 
;Decrement counter
JNZ BACK  
;If counter 0 repeat
HLT  
;Terminate program execution