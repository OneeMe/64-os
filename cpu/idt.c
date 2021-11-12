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
    // 在 lib/asm/gdt.asm 中，我们定义的 code segment 的偏移是 0x8
    idt[n].sel = 0x8;
}

void set_idt()
{
    idt_pointer.base = (u32)&idt;
    idt_pointer.limit = IDT_ENTRIES * sizeof(idt_entry_struct) - 1;
    // 把 idt_pointer 的地址传给汇编让其加载
    __asm__ __volatile__("lidtl (%0)"
                         :
                         : "r"(&idt_pointer));
}
