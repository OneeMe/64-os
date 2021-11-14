#include "../cpu/isr.h"
#include "../cpu/timer.h"

#include "../drivers/ports.h"
#include "../drivers/screen.h"
#include "util.h"

void test_scroll();
void test_interrupt();

void main()
{
    clear_screen();
    setup_idt();

    // test_scroll();
    // test_interrupt();
    init_timer(50);
}

void test_scroll()
{
    /* Fill up the screen */
    int i = 0;
    for (i = 0; i < 24; i++)
    {
        char str[255];
        int_to_ascii(i, str);
        kprint_at(str, 0, i);
    }

    kprint_at("This text forces the kernel to scroll. Row 0 will disappear. ", 60, 24);
    kprint("And with this text, the kernel will scroll again, and row 1 will disappear too!");

    kprint("And now we will begin to enable Interrupt");
}

void test_interrupt()
{
    // 测试一下中断好不好使
    __asm__ __volatile__("int $2");
    __asm__ __volatile__("int $3");
}
