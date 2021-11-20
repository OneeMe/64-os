#ifndef PAGING_H
#define PAGING_H

#include <stdint.h>

typedef struct page
{
    uint32_t present : 1;  // Page 是否存在于内存中
    uint32_t rw : 1;       // 可读可写
    uint32_t user : 1;     // 是否用户态
    uint32_t accessed : 1; // 是否访问过
    uint32_t dirty : 1;    // 是否写过内容
    uint32_t unused : 7;   // 保留位
    uint32_t frame : 20;   // 地址
} page_t;

typedef struct page_table
{
    page_t pages[1024];
} page_table_t;

typedef struct page_directory
{
    /**
      这里存储所有的 table 的指针
   **/
    page_table_t *tables[1024];
    /**
      这里存储所有 table 的物理地址
   **/
    uint32_t tablesPhysical[1024];
    /**
      tablesPhysical 这个数组的物理地址
   **/
    uint32_t physicalAddr;
} page_directory_t;

#endif
