#include "types.h"

void setup_idt();

// ISR 的通用处理函数的入参
typedef struct
{
    u32 ds;                                     /* Data segment selector */
    u32 edi, esi, ebp, esp, ebx, edx, ecx, eax; /* Pushed by pusha. */
    u32 int_no, err_code;                       /* Interrupt number and error code (if applicable) */
    u32 eip, cs, eflags, useresp, ss;           /* Pushed by the processor automatically */
} isr_param_registers;
