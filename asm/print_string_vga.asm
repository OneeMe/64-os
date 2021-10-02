; 将 ebx 中存储的地址上的字符串打印到屏幕上
; 在 32 位模式下运行
[bits 32]
; 定义一些常量
VIDEO_MEMORY equ 0xb8000
WHITE_ON_BLACK equ 0x0f
print_string_pm:
    pusha
    mov edx, VIDEO_MEMORY ; 之后我们设置的内存地址会不断增多，现在先将地址存储在 edx 中

print_string_loop:
    mov al, [ebx] ; 先将 ebx 所指向的内存上的字符存储在 al 上
    mov ah, WHITE_ON_BLACK

    cmp al, 0
    je over

    mov [edx], ax ; 把 ax 寄存器上的内容复制到 0xb8000 开始的内存上

    add ebx, 1 ; 继续看 ebx 所指向的下一个地址存储的字符是什么
    add edx, 2 ; 因为 VIDEO_MEMORY 一次用掉两个字节，所以地址 +2

    jmp print_string_loop

over:
    popa
    ret


