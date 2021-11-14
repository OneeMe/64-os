#ifndef IRQ_H
#define IRQ_H
#include "idt.h"

void setup_irq();
void register_irq_handler(u8 n, handler handler);
#endif
