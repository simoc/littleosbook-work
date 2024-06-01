#include "fb.h"

void kmain(void)
{
	fb_write("hello world", 11);
	for (int i = 0; i <= 100; i++)
	{
		fb_write(" ", 1);
		fb_write_int(i);
	}
}
