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
