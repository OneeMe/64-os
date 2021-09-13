mov ah, 0x0e
; first try
mov al, secreet
int 0x10
; second try
mov al, [secreet]
int 0x10
; third try
mov bx, secreet
add bx, 0x7c00
mov al, [bx]
int 0x10
; fourth try
mov al, [0x7c1d]
int 0x10

jmp $
secreet:
    db 'X'

times 510 - ($ - $$) db 0
dw 0xaa55
