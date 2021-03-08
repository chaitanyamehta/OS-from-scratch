CODE = $(wildcard *.c)
OBJ = boot.o $(CODE:.c=.o)

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
