#ifndef MEM_H
#define MEM_H

// 将 source 中的 bytes 复制到 dest 中
void memory_copy(char *source, char *dest, int no_bytes);

// 获取一个地址中的低、高16位地址
#define low_16(address) (u16)((address)&0xFFFF)
#define high_16(address) (u16)(((address) >> 16) & 0xFFFF)

#endif