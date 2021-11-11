#include "idt.h"
#include "../kernel/util.h"

// 有 256 个中断
#define IDT_ENTRIES 256
// 声明 IDT 数组
idt_entry_struct idt[IDT_ENTRIES];
idt_pointer_struct idt_pointer;

void set_idt_gate(int n, u32 entry_address)
{
    idt[n].base_low = low_16(entry_address);
    idt[n].base_high = high_16(entry_address);
    idt[n].always0 = 0;
    // 0x8E = 10001110，代表 present / 32bit interript gate
    idt[n].flags = 0x8E;
    idt[n].sel = 0;
}
