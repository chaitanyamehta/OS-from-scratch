SHELL	= /bin/bash

.SUFFIXES:
.SUFFIXES: .c .s .h .o

INCLDIR	= include/
BOOTDIR	= boot/
BINDIR	= bin/
OBJDIR	= obj/
SRCDIR	= src/

# final executable name
BIN			= $(BINDIR)image.bin
BOOT_BIN	= $(BINDIR)boot.bin
KERN_BIN	= $(BINDIR)kernel.bin

C_SRC	= $(wildcard $(SRCDIR)*.c)
S_SRC	= $(SRCDIR)start.s $(filter-out $(SRCDIR)start.s, $(wildcard $(SRCDIR)*.s))
_OBJS	= $(patsubst $(SRCDIR)%.s, %.o, $(S_SRC)) $(patsubst $(SRCDIR)%.c, %.o, $(C_SRC))
OBJS	= $(addprefix $(OBJDIR), $(_OBJS))

CFLAGS = -m32 -fno-pie -ffreestanding
LDFLAGS = -m elf_i386 -Tlink.ld --oformat binary
ASFLAGS = -f elf

all: $(BIN)
	
$(BIN): $(BOOT_BIN) $(KERN_BIN)
	cat $^ > $(BIN)

$(KERN_BIN): $(OBJS)
	ld $(LDFLAGS) -o $(KERN_BIN) $(OBJS)

$(OBJDIR)%.o: $(SRCDIR)%.c
	gcc $(CFLAGS) -c $< -I $(INCLDIR) -o $@

$(OBJDIR)%.o: $(SRCDIR)%.s
	nasm $(ASFLAGS) $< -o $@

$(BOOT_BIN): $(BOOTDIR)boot.s
	nasm -f bin $< -I $(BOOTDIR) -o $@

clean:
	rm -rf $(OBJDIR)*.o $(BINDIR)*.bin
	
$(shell mkdir -p $(BINDIR))
$(shell mkdir -p $(OBJDIR))

