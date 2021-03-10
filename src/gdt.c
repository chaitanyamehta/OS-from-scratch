#include "gdt.h"

/* GDT, with 3 entries */
struct gdt_entry gdt[3];
struct gdt_ptr gdtp;

/* This exists in 'descriptor_table.s', and is used to load our GDT */
extern void gdt_load();

/* Setup a descriptor in the Global Descriptor Table */
void gdt_set_gate(uint8_t num, uint32_t base, uint32_t limit, uint8_t access, uint8_t granularity)
{
	gdt[num].base_l = base & 0xFFFF;
	gdt[num].base_m = (base >> 16) & 0xFF;
	gdt[num].base_h = (base >> 24) & 0xFF;
	gdt[num].limit_l = (limit & 0xFFFF);
	gdt[num].granularity = (granularity & 0xF0) | ((limit >> 16) & 0x0F);
	gdt[num].access = access;
}

/* Installs the GDT */
void init_gdt()
{
	/* Sets the special GDT pointer up */
	gdtp.limit = (sizeof (struct gdt_entry) * 3) - 1;
	gdtp.base = (uint32_t)&gdt;
	
	/* Null descriptor */
	gdt_set_gate(0, 0, 0, 0, 0);
	
	/* The second entry is our Code Segment. The base address
	   is 0, the limit is 4GBytes, it uses 4KByte granularity,
	   uses 32-bit opcodes, and is a Code Segment descriptor. */
	gdt_set_gate(1, 0, 0xFFFFFFFF, 0x9A, 0xCF);

	/* The third entry is our Data Segment. It's EXACTLY the
	   same as our code segment, but the descriptor type in
	   this entry's access byte says it's a Data Segment */
	gdt_set_gate(2, 0, 0xFFFFFFFF, 0x92, 0xCF);
	
	/* Points the processor's internal register to the new GDT */
	gdt_load();
}
