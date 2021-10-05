BUILD_DIR=output

all: boot.img


${BUILD_DIR}/boot.bin: asm/boot.asm
	nasm -f bin -I asm $^ -o $@

${BUILD_DIR}/kernel_entry.o: asm/kernel_entry.asm
	nasm -f elf -I asm $^ -o $@

${BUILD_DIR}/kernel.o: c/kernel.c
	x86_64-elf-gcc -ffreestanding -m32 -c $^ -o $@

${BUILD_DIR}/kernel.bin: ${BUILD_DIR}/kernel.o ${BUILD_DIR}/kernel_entry.o
	x86_64-elf-ld -o $@ -Ttext 0x1000 $^ --oformat binary -m elf_i386

boot.img: ${BUILD_DIR}/boot.bin ${BUILD_DIR}/kernel.bin
	cat $^ > $@

run: boot.img
	qemu-system-i386 -fda boot.img

clean:
	rm -rf output/*
	rm boot.img
