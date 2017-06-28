#include "nm-otool.h"

/*
** Init the structure file and return this one
*/
s_file *init_file(void *ptr)
{
	s_file *file;

	if ((file = malloc(sizeof(s_file))) == NULL)
		ft_malloc_error();
	file->nb_archs = 1;
	file->is_displayed = FALSE;
	file->file_format = get_file_format(ptr);
	return (file);
 }
