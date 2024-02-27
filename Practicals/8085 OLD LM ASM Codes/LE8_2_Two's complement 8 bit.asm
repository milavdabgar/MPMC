;<2’s complement of a no>
LDA 4150H 
;Get the number
CMA 
;Complement the number
ADI 01H 
;Add one in the number
STA 4151H 
;Store the result
HLT 
;Terminate program execution