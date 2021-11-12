[EXTERN isr_handler]

isr_common_stub:
    pusha ; 先把所有的寄存器信息都放在栈上
    mov ax, ds ; 把 data segment selector 保存在 eax 寄存器上
    push eax

    mov ax, 0x10 ; 这里不太懂
    mov ds, ax  
    mov es, ax  
    mov fs, ax  
    mov gs, ax  

    call isr_handler  
  
    pop eax ; 恢复 eax
    mov ds, ax  
    mov es, ax  
    mov fs, ax  
    mov gs, ax  
    
    popa ; 恢复其他寄存器
    add esp, 8 ; 没太懂
    sti  ; 没太懂
    ire  ; 回到中断执行之前的位置继续执行

; define a macro, taking one parameter  
%macro ISR_NOERRCODE 1 
 [GLOBAL isr%1] ; %1 accesses the first parameter.  
 isr%1:  
 cli  
 push byte 0  
 push byte %1  
 jmp isr_common_stub  
%endmacro  
  
%macro ISR_ERRCODE 1  
 [GLOBAL isr%1]  
 isr%1:  
 cli  
 push byte %1  
 jmp isr_common_stub  
%endmacro

; 0: Divide By Zero Exception
ISR_NOERRCODE 0
; 1: Debug Exception
ISR_NOERRCODE 1
; 2: Non Maskable Interrupt Exception
ISR_NOERRCODE 2
; 3: Int 3 Exception
ISR_NOERRCODE 3
; 4: INTO Exception
ISR_NOERRCODE 4
; 5: Out of Bounds Exception
ISR_NOERRCODE 5
; 6: Invalid Opcode Exception
ISR_NOERRCODE 6
; 7: Coprocessor Not Available Exception
ISR_NOERRCODE 7
; 8: Double Fault Exception (With Error Code!)
ISR_ERRCODE 8
; 9: Coprocessor Segment Overrun Exception
ISR_NOERRCODE 9
; 10: Bad TSS Exception (With Error Code!)
ISR_ERRCODE 10
; 11: Segment Not Present Exception (With Error Code!)
ISR_ERRCODE 11
; 12: Stack Fault Exception (With Error Code!)
ISR_ERRCODE 12
; 13: General Protection Fault Exception (With Error Code!)
ISR_ERRCODE 13
; 14: Page Fault Exception (With Error Code!)
ISR_ERRCODE 14
; 15: Reserved Exception
ISR_NOERRCODE 15
; 16: Floating Point Exception
ISR_NOERRCODE 16
; 17: Alignment Check Exception
ISR_NOERRCODE 17
; 18: Machine Check Exception
ISR_NOERRCODE 18
; 19: Reserved
ISR_NOERRCODE 19
; 20: Reserved
ISR_NOERRCODE 20
; 21: Reserved
ISR_NOERRCODE 21
; 22: Reserved
ISR_NOERRCODE 22
; 23: Reserved
ISR_NOERRCODE 23
; 24: Reserved
ISR_NOERRCODE 24
; 25: Reserved
ISR_NOERRCODE 25
; 26: Reserved
ISR_NOERRCODE 26
; 27: Reserved
ISR_NOERRCODE 27
; 28: Reserved
ISR_NOERRCODE 28
; 29: Reserved
ISR_NOERRCODE 29
; 30: Reserved
ISR_NOERRCODE 30
; 31: Reserved
ISR_NOERRCODE 31
