S_FILES = $(wildcard *.s)
C_FILES = $(wildcard *.c)
OBJ = $(S_FILES:.s=.o) $(C_FILES:.c=.o)

CFLAGS = -m32 -nostdlib -nostdinc -fno-builtin -fno-stack-protector
LDFLAGS = -m elf_i386 -Tlink.ld
ASFLAGS = -felf

all: $(OBJ) link

link:
	ld $(LDFLAGS) -o kernel $(OBJ)

.s.o:
	nasm $(ASFLAGS) $<

clean:
	rm -rf *.o kernel
