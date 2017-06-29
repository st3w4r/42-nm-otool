#include "nm-otool.h"

/*
** Init the structure format and return this one
*/
s_format *init_format(void *ptr)
{
	s_format					*format;

	if ((format = malloc(sizeof(s_format))) == NULL)
		ft_malloc_error();
	format->filename = NULL;
	format->file_format = get_file_format(ptr);
	format->ptr_header = ptr;
	format->symbol_table = NULL;
	format->string_table = NULL;
	format->section_list = NULL;
	format->symbol_list = NULL;
	format->archive_list = NULL;
	return format;
}
