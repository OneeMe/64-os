# 64-os

这是阅读 "Writing a Simple Operating System — from Scratch" 过程中的代码记录

## 编译方式

```shell
cd asm
nasm boot.asm -o ../boot.img -f bin
```

## 虚拟机启动方法

```shell
bochs
```

或者 

```shell
qemu-system-i386  ../boot.img
```
