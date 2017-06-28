#include "nm-otool.h"

/*
** Functinos for archive
*/

struct ar_magic *get_ar_magic(void *ptr)
{
	return (ptr);
}

struct ar_header *get_ar_header(void *ptr)
{
	struct ar_header *ar_header;

	ar_header = (ptr + sizeof(struct ar_magic));
	check_memory_out(ar_header);
	return (ar_header);
}
