#include "./memory.h"

void memory_copy(u8 *source, u8 *dest, int no_bytes)
{
    int i;
    for (i = 0; i < no_bytes; i++)
    {
        *(dest + i) = *(source + i);
    }
}

void memory_set(u8 *dest, u8 val, u32 len)
{
    u8 *temp = (u8 *)dest;
    for (; len != 0; len--)
        *temp++ = val;
}
// 64KB，应该是因为目前 kernel 占用的大小还没有那么大，所以就把 64KB 这里当做一个 heap 来用了
u32 base_address = 0x10000;

void make_sure_base()
{
    if (!base_address)
    {
        // 非常奇怪的是编译器没有将 base_address 初始化，而是给了默认值 0，这里手动给一个正确的初始值
        base_address = 0x10000;
    }
}
u32 kmalloc_ap(u32 size, int align, u32 *phys_addr)
{
    make_sure_base();
    if (align == 1 && base_address & 0xFFFFF000)
    {
        // 4KB 对齐一下
        base_address &= 0xFFFFF000;
        base_address += 0x1000;
    }
    if (phys_addr)
    {
        *phys_addr = base_address;
    }
    // 保存一下当前的地址
    u32 return_address = base_address;
    // 把传入的 size 分配到传入的地址中
    base_address += size;
    return return_address;
}

u32 kmalloc(u32 size)
{
    make_sure_base();
    // 保存一下当前的地址
    u32 return_address = base_address;
    // 把传入的 size 分配到传入的地址中
    base_address += size;
    return return_address;
}

u32 kmalloc_a(u32 size, int align)
{
    make_sure_base();
    if (align == 1 && base_address & 0xFFFFF000)
    {
        // 4KB 对齐一下
        base_address &= 0xFFFFF000;
        base_address += 0x1000;
    }
    // 保存一下当前的地址
    u32 return_address = base_address;
    // 把传入的 size 分配到传入的地址中
    base_address += size;
    return return_address;
}

u32 kmalloc_p(u32 size, u32 *phys_addr)
{
    if (phys_addr)
    {
        *phys_addr = base_address;
    }
    // 保存一下当前的地址
    u32 return_address = base_address;
    // 把传入的 size 分配到传入的地址中
    base_address += size;
    return return_address;
}
