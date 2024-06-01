#include "fb.h"
#include "serial.h"

void kmain(void)
{
	char *message = "hello world";

	fb_write(message, 11);
	for (int i = 0; i <= 100; i++)
	{
		fb_write(" ", 1);
		fb_write_int(i);
	}

	unsigned short com = SERIAL_COM1_BASE;
	serial_configure_baud_rate(com, 1);
	serial_configure_line(com);
	serial_write(com, message, 11);
}
