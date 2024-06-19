#include "lgdt.h"

extern void kmain(void);

struct gdt_entry segment_descriptors[3];

static void gdt_set_entry(unsigned int position,
	unsigned int base,
	unsigned int limit,
	unsigned char access_rights,
	unsigned char flags)
{
	segment_descriptors[position].base_lower = base & 0xffff;
	segment_descriptors[position].base_middle = (base >> 16) & 0xff;
	segment_descriptors[position].base_higher = (base >> 24) & 0xffff;

	segment_descriptors[position].limit_lower = limit & 0xffff;
	/*
	 * From https://wiki.osdev.org/Global_Descriptor_Table
	 * Flags
	 * 3   2   1   0
	 * G   DB  L   Reserved
	 * G: granularity (0 for bytes, 1 for 4KB pages)
	 * DB: default size (0 for 16 bit, 1 for 32 bit)
	 * L: Long mode (1 for 64 bit)
	 */
	segment_descriptors[position].flags_limit_higher = ((flags << 4) & 0xf0) | ((limit >> 16) & 0x0f);
	/*
	 * From https://wiki.osdev.org/Global_Descriptor_Table
	 * Access Byte
	 * 7 	6 	5 	4 	3 	2 	1 	0
	 * P 	DPL 	S 	E 	DC 	RW 	A
	 * P: present bit (must be 1 for any valid segment)
	 * DPL: descriptor privilege level (0 is highest for kernel)
	 * S: 0 for system segment, 1 for code or data segment
	 * E: 1 for code segment that is executable
	 * DC: grow direction, conforming bit
	 * RW: read and write bits
	 * A: access bit (leave it as 1)
	 */
	segment_descriptors[position].access_rights = access_rights;
}

static void gdt_setup()
{
	/* null descriptor */
	gdt_set_entry(0, 0, 0, 0, 0);
	/* kernel code segment */
	gdt_set_entry(1, 0, 0xfffff, 0x9a, 0x0c);
	/* kernel data segment */
	gdt_set_entry(2, 0, 0xfffff, 0x92, 0x0c);
}

void kmain0(void)
{
	/*
	 * Setup Global Descriptor Table (GDT).
	 */
	gdt_setup();
	struct gdt global_descriptor_table;

	/*
	 * From https://wiki.osdev.org/Global_Descriptor_Table
	 * "Size: The size of the table in bytes subtracted by 1.
	 * This subtraction occurs because ...".
	 */
	global_descriptor_table.size = sizeof(segment_descriptors) - 1;
	global_descriptor_table.address = (unsigned int)segment_descriptors;
	lgdt(&global_descriptor_table);

	kmain();
}
