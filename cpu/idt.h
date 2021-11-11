#include "types.h"

// IDT 的每个元素的声明
typedef struct
{
    u16 base_low;                         // base 一共有 32 位, 但是这 32 位是分开的，这里是低的 16 位
    u16 sel;                              // 中断的对应处理程序的地址（为什么地址还是 16 位的？）
    u8 always0;                           // 非常好理解
    u8 flags;                             // 代表中断的其他属性，具体的 flags 信息见 http://www.jamesmolloy.co.uk/tutorial_html/4.-The%20GDT%20and%20IDT.html
    u16 base_high;                        // 最后的高 16 位
} __attribute((packed)) idt_entry_struct; // 让编译器取消结构体在编译过程中的优化对齐,按照实际占用字节数进行对齐

// 声明 IDT 所在位置的入口指针
typedef struct
{
    u16 limit;
    u32 base;
} __attribute((packed)) idt_pointer_struct;

// 给中断设置对应的处理程序
// n 代表中断号，entry_address 代表 idt 的地址
void set_idt_gate(int n, u32 entry_address);
void set_idt();
