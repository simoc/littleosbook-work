#ifndef INCLUDE_LGDT_H
#define INCLUDE_LGDT_H

/*
 * An entry in a Global Descriptor Table (GDT).
 */
struct gdt_entry
{
	unsigned short limit_lower;
	unsigned short base_lower;
	unsigned char base_middle;
	unsigned char access_rights;
	unsigned char flags_limit_higher;
	unsigned char base_higher;
} __attribute__((packed));

struct gdt
{
	unsigned short size;
	unsigned int address;
} __attribute((packed));

/** lgdt:
 * Load Global Descriptor Table (GDT).
 *
 * @param address address of GDT
 */
void lgdt(struct gdt *address);

#endif /* INCLUDE_LGDT_H */
