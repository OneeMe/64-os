; DH: sectors
; DL: drive id
disk_load:
    push dx ; save dx to stack 
    mov ah, 0x02 ; 让 BIOS 按照 sector 读取磁盘
    mov al, dh ; read dh sector count
    mov ch, 0x00 ; cylinder 0
    mov dh, 0x00 ; head 0
    mov cl, 0x02 ; read from second sector, which is after boot sector

    int 0x13

    jc disk_error

    pop dx
    cmp dh, al
    jne disk_error
    ret

disk_error:
    mov bx, DISK_ERROR_MESSAGE
    call print_string
    jmp $

DISK_ERROR_MESSAGE:
    db "DISK Read Error!", 0
