#include "nm-otool.h"


/*
** Check if the size in the header isn't out of the mapped memory
*/
bool is_out_of_size(size_t file_size, void *ptr_header)
{
	struct mach_header_64 *header;
	uint32_t size;

	header = (struct mach_header_64*)header;
	size = header->sizeofcmds;
	if (size > file_size)
		return true;
	return false;
}

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
