# 64-os

这是阅读 "Writing a Simple Operating System — from Scratch" 过程中的代码记录

## 环境准备

```shell
brew install nasm qemu x86_64-elf-gcc x86_64-elf-binutils
```

## 虚拟机启动方法

```shell
bochs
```

或者 

```shell
qemu-system-i386 -fda boot.img
```
