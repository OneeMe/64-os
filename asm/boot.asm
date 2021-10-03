org 0x7c00

mov bp, 0x9000 ; 设置 stack base 为 0x9000
mov sp, bp ; 把 stack base 和 stack top 初始化

mov bx, MSG_REAL_MODE 
call print_string

call switch_to_pm

jmp $

%include "print_string.asm"
%include "gdt.asm"
%include "switch_to_pm.asm"
%include "print_string_pm.asm"

[bits 32]
BEGIN_PM:
mov ebx, MSG_PORT_MODE
call print_string_pm

jmp $

; Global variables
MSG_REAL_MODE db "Start in 16 bit real mode", 0
MSG_PORT_MODE db "Successfully landed in 32-bit Protected mode", 0

times 510 - ($ - $$) db 0
dw 0xaa55
