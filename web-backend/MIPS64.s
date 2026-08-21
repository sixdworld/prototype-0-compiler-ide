; Symbol Table
; Name	Reg	Offset

.data
str0: .asciiz "hiii"

.code
daddiu r4, r0, str0
syscall 5
