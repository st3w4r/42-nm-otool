#include "nm-otool.h"

/*
** Check is the adress is not out of memory file
*/
void check_memory_out(void *ptr)
{
	if (ptr > g_prog.current_max_addr)
	{
		ft_error_str_exit("malformed file\n");
	}
}
