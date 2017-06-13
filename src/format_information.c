#include "nm-otool.h"

e_file_format	get_file_format(void *ptr)
{
	uint32_t magic;

	magic = *(uint32_t *)ptr;

	if (magic == MH_MAGIC)
		return (MACHO_32);
	else if (magic == MH_MAGIC_64)
		return (MACHO_64);
	else
		return (UNKNOWN);
}
