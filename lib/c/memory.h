#ifndef MEM_H
#define MEM_H

#include "../../cpu/types.h"

// 将 source 中的 bytes 复制到 dest 中
void memory_copy(u8 *source, u8 *dest, int no_bytes);
void memory_set(u8 *dest, u8 val, u32 len);

/* 实现一个简单的 malloc 函数 */
u32 kmalloc(u32 size);
u32 kmalloc_ap(u32 size, int align, u32 *phys_addr);
u32 kmalloc_a(u32 size, int align);
u32 kmalloc_p(u32 size, u32 *phys_addr);

// 获取一个地址中的低、高16位地址
#define low_16(address) (u16)((address)&0xFFFF)
#define high_16(address) (u16)(((address) >> 16) & 0xFFFF)

#endif
