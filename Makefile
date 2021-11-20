ASM_LIB=lib/asm

C_SOURCES = $(wildcard kernel/*.c drivers/*.c cpu/*.c lib/c/*.c)
HEADERS = $(wildcard kernel/*.h drivers/*.h cpu/*.h lib/c/*.h)
C_OBJS = $(patsubst %.c, %.o,$(C_SOURCES))

CFLAGS = -g

all: os-image

# build os-image
os-image: boot/boot.bin kernel/kernel.bin
	cat $^ > $@

# build kernel
kernel/kernel.bin: kernel/kernel_entry.o cpu/interrupt_list.o ${C_OBJS}
	x86_64-elf-ld -o $@ -Ttext 0x1000 $^ --oformat binary -m elf_i386

# generic .c -> .o rule
%.o : %.c ${HEADERS}
	x86_64-elf-gcc ${CFLAGS} -m32 -ffreestanding -c $< -o $@

# generic .asm -> .o rule
%.o : %.asm
	nasm $< -f elf -o $@

# generic .asm -> .bin rule
%.bin : %.asm
	nasm $< -f bin -I ${ASM_LIB} -o $@

run: os-image
	qemu-system-i386 -fda $^

# Used for debugging purposes
kernel/kernel.elf: kernel/kernel_entry.o ${C_OBJS}
	x86_64-elf-ld -o $@ -Ttext 0x1000 $^ -m elf_i386

debug: os-image kernel/kernel.elf
	qemu-system-i386 -s -fda $^ & gdb -ex "target remote localhost:1234" -ex "symbol-file kernel/kernel.elf"

clean:
	rm -rf **/*.o **/*.bin **/*.elf os-image
