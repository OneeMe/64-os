#include "irq.h"
#include "../kernel/util.h"

#define MASTER_PIC 0x20 /* IO base address for master PIC */
#define SLAVE_PIC 0xA0  /* IO base address for slave PIC */
#define MASTER_PIC_DATA (MASTER_PIC + 1)
#define SLAVE_PIC_DATA (SLAVE_PIC + 1)

#define ICW1 0x11 /* init + need ICW4 */
#define MASTER_OFFSET 0x20
#define SLAVE_OFFSET 0x28
#define ICW3_MASTER 0x04
#define ICW3_SLAVE 0x02
#define ICW4 0x01 /* 8086/88 (MCS-80/85) mode */
#define MASK 0x00 /* 8086/88 (MCS-80/85) mode */

#define IRQ_ENTRIES 224
handler irq_handlers[IRQ_ENTRIES];

void remap_pic()
{
    port_byte_out(MASTER_PIC, ICW1);
    port_byte_out(MASTER_PIC_DATA, MASTER_OFFSET);
    port_byte_out(MASTER_PIC_DATA, ICW3_MASTER);
    port_byte_out(MASTER_PIC_DATA, ICW4);
    port_byte_out(MASTER_PIC_DATA, MASK);

    port_byte_out(SLAVE_PIC, ICW1);
    port_byte_out(SLAVE_PIC_DATA, SLAVE_OFFSET);
    port_byte_out(SLAVE_PIC_DATA, ICW3_SLAVE);
    port_byte_out(SLAVE_PIC_DATA, ICW4);
    port_byte_out(SLAVE_PIC_DATA, MASK);
}

extern void irq0();
extern void irq1();
extern void irq2();
extern void irq3();
extern void irq4();
extern void irq5();
extern void irq6();
extern void irq7();
extern void irq8();
extern void irq9();
extern void irq10();
extern void irq11();
extern void irq12();
extern void irq13();
extern void irq14();
extern void irq15();

void setup_irq()
{
    remap_pic();

    set_idt_gate(32, (u32)irq0);
    set_idt_gate(33, (u32)irq1);
    set_idt_gate(34, (u32)irq2);
    set_idt_gate(35, (u32)irq3);
    set_idt_gate(36, (u32)irq4);
    set_idt_gate(37, (u32)irq5);
    set_idt_gate(38, (u32)irq6);
    set_idt_gate(39, (u32)irq7);
    set_idt_gate(40, (u32)irq8);
    set_idt_gate(41, (u32)irq9);
    set_idt_gate(42, (u32)irq10);
    set_idt_gate(43, (u32)irq11);
    set_idt_gate(44, (u32)irq12);
    set_idt_gate(45, (u32)irq13);
    set_idt_gate(46, (u32)irq14);
    set_idt_gate(47, (u32)irq15);
}

void irq_handler(isr_param_registers registers)
{
    /* After every interrupt we need to send an EOI to the PICs
     * or they will not send another interrupt again */
    if (registers.int_no >= 40)
        port_byte_out(0xA0, 0x20); /* slave */
    port_byte_out(0x20, 0x20);     /* master */

    /* Handle the interrupt in a more modular way */
    u8 irq_index = registers.int_no - 32;

    if (irq_index >= 0 && irq_index < IRQ_ENTRIES && irq_handlers[irq_index] != 0)
    {
        handler handler = irq_handlers[irq_index];
        handler(registers);
    }
}

void register_irq_handler(u8 n, handler handler)
{
    irq_handlers[n] = handler;
    if (n >= 0 && n < IRQ_ENTRIES)
    {
    }
}
