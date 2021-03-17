#ifndef GDT_H
#define GDT_H

#include "stdint.h"

// A struct describing segment descriptor.
struct gdt_entry
{
	uint16_t limit_l;	// Lower 16 bits of the segment limit
	uint16_t base_l;	// Lower 8 bits of the base address
	uint8_t base_m;		// Middle 16 bits of the base address
	uint8_t access;		// present:1, descriptor privilege level:2, 
						// decriptor type:1, segment type:5
	uint8_t granularity;// G, D/B, L, AVL, Seg Limit:4
	uint8_t base_h;		// Upper 8 bits of the base address
	
} __attribute__((packed));

// A struct describing a pointer to an array of global descriptors.
struct gdt_ptr
{
	uint16_t limit;
	uint32_t base;
} __attribute__((packed));

void init_gdt();

#endif

