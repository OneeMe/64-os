print_string: 
    pusha ; 保存寄存器
print:
    mov ah, 0x0e ; 初始化 mode
    mov cx, [bx] ; [bx] 中的内容放到 cx 中
    cmp cl, 0    ; 然后比较 cl 中的内容，如果发现是 0 ，就结束
    je done
    mov al, cl   ; 否则打印
    int 0x10
    cmp ch, 0    ; 然后比较 ch 中的内容，如果发现是 0 ，就结束
    je done
    mov al, ch
    int 0x10
    add bx, 2    ; 打印结束后增加 bx 的地址，准备下一次打印
    jmp print
done:
    popa ; 恢复寄存器
    ret
