
;<Addition of two 16-bit numbers>

LHLD 4150H
;Get first 16-bit number
XCHG
;Save first 16-bit number in DE
LHLD 4152H  
;Get second 16-bit number in HL
DAD D  
;Add DE and HE
SHLD 4154H 
;Store 16-bit result in memory locations 2004H and 2005H.
HLT 
;Terminate program execution