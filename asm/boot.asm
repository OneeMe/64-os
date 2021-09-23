org 0x7c00

mov bx, HELLO_MSG
call print_string

mov bx, GOODBYE_MSG
call print_string

mov dx, 0x12fe
call print_string_hex

jmp $

%include "print_string_hex.asm"

HELLO_MSG:
    db 'hello, world!', 0
GOODBYE_MSG: 
    db 'Goodby!', 0

times 510 - ($ - $$) db 0
dw 0xaa55
