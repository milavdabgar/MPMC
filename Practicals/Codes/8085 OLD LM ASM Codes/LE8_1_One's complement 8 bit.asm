
;<1’s complement of 8 bit number>
LDA 4150H 
;Get the number
CMA 
;Complement number
STA 4151H  
;Store the result
HLT 
;Terminate program execution

