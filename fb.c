#include "fb.h"
#include "io.h"

/* The I/O ports */
#define FB_COMMAND_PORT 0x3D4
#define FB_DATA_PORT    0x3D5

/* The I/O port commands */
#define FB_HIGH_BYTE_COMMAND 14
#define FB_LOW_BYTE_COMMAND  15

/** fb_move_cursor:
 * Move the cursor of the framebuffer to the given position
 *
 * @param pos The new position of the cursor
 */
void fb_move_cursor(unsigned short pos)
{
	outb(FB_COMMAND_PORT, FB_HIGH_BYTE_COMMAND);
	outb(FB_DATA_PORT, ((pos >> 8) & 0x00FF));
	outb(FB_COMMAND_PORT, FB_LOW_BYTE_COMMAND);
	outb(FB_DATA_PORT, (pos & 0x00FF));
}

/** fb_write_cell:
 * Writes a character with the given foreground and background to position i
 * in the frame buffer.
 *
 * @param i The location in the framebuffer
 * @param c The character
 * @param fg The foreground color
 * @param bg The background color
 */
void fb_write_cell(unsigned int i, char c, unsigned char fg, unsigned char bg)
{
	char *fb = (char *) 0x000B8000; /* address of frame buffer */
	fb[i] = c;
	fb[i + 1] = ((bg & 0x0F) << 4) | (fg & 0x0F);
}

int fb_write(char *buf, unsigned int len)
{
	static unsigned int current_row = 0;
	static unsigned int current_column = 0;

	unsigned int i = 0;
	while (i < len)
	{
		fb_write_cell((current_row * 80 + current_column) * 2,
			buf[i], FB_GREEN, FB_LIGHT_GREY);
		i++;
		current_column++;
		if (current_column >= 80)
		{
			current_column = 0;
			current_row++;
			if (current_row >= 25)
			{
				current_row = 0;
			}
		}
    }
	return len;
}

int fb_write_int(int n)
{
	char buf[16];
	char *ptr = buf + sizeof(buf) - 1;
	int is_negative = 0;
	int digit;
	unsigned int len = 0;

	if (n < 0)
	{
		n = -n;
		is_negative = 1;
	}

	do
	{
		digit = n % 10;
		*ptr = digit + '0';
		ptr--;
		len++;
		n = n / 10;
	}
    while (n != 0);

	if (is_negative)
	{
		*ptr = '-';
		ptr--;
		len++;
	}

	return fb_write(ptr + 1, len);
}
