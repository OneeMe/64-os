; 参数：DX 输入的一个字
; 输出：打印16进制表示
; copy from https://github.com/cfenollosa/os-tutorial/blob/master/05-bootsector-functions-strings/boot_sect_print_hex.asm
print_string_hex:
    pusha
    mov cx, 0 ; 用于存储当前循环次数
hex_loop:
    cmp cx, 4
    je hex_loop_end
    mov ax, dx
    and ax, 0x000f
    add ax, '0' ; 0 is 0x30
    cmp ax, 0x39 
    jle step_2 ; if less than 0x39
    add ax, 7
step_2:
    mov bx, HEX_MESSAGE + 5
    sub bx, cx
    mov [bx], al
    shr dx, 4
    add cx, 1
    jmp hex_loop
hex_loop_end:
    mov bx, HEX_MESSAGE
    call print_string
    popa 
    ret
%include "print_string.asm"
HEX_MESSAGE:
    db '0x0000',0
