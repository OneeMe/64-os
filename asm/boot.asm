org 0x7c00

mov [BOOT_DRIVE], dl ; BIOS 会把启动磁盘 id 存放在 dl 中，所以这里先把他存起来

mov bp, 0x8000
mov sp, bp ; 设置一下 stack base，设置到 0x8000

mov bx, 0x9000 ; 设置 bx，从而让读取到的内容被放置到 0x9000 上
mov dh, 5 ; 读取 5 个扇区的内容
mov dl, [BOOT_DRIVE] ; 读取当前磁盘上的内容
call disk_load

mov dx, [0x9000] ; 读取 0x9000 后的第一个 word，看是不是 0xdada
call print_string_hex

mov dx, [0x9000 + 512] ; 读取 0x9000 + 512 后的第一个 word，看是不是 0xface
call print_string_hex

jmp $

%include "print_string_hex.asm"
%include "disk_load.asm"

BOOT_DRIVE: db 0

times 510 - ($ - $$) db 0
dw 0xaa55

times 256 dw 0xdada
times 256 dw 0xface
