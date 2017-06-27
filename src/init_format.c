#include "nm-otool.h"

// s_lc_list	*init_lc_list(struct mach_header_64 *header)
// {
// 	s_lc_list *lc_list_previous;
// 	s_lc_list *lc_list_current;
// 	uint32_t ncmds;
// 	uint32_t i;
// 	struct load_command *lc;
//
// 	lc_list_previous = NULL;
//
// 	i = 0;
// 	ncmds = header->ncmds;
// 	lc = get_first_load_command(header);
// 	while (i < ncmds)
// 	{
// 		if ((lc_list_current = malloc(sizeof(s_lc_list))) == NULL)
// 			ft_malloc_error();
// 		lc_list_current->lc = lc;
// 		lc_list_current->prev = lc_list_previous;
// 		lc_list_current->next = NULL;
// 		lc_list_previous = lc_list_current;
// 		lc = get_next_load_command(lc);
// 		i++;
// 	}
// 	return lc_list_current;
// }


/*
** Init the structure format and return this one
*/
 s_format *init_format(void *ptr)
 {
	 s_format					*format;
	 s_section_list		s_section_list;
	 s_symbol_list		s_symbol_list;

	 if ((format = malloc(sizeof(s_format))) == NULL)
		ft_malloc_error();

	format->filename = NULL;
	format->file_format = get_file_format(ptr);
	//  format.is_64 =
	// format.is_big_endian =
	format->ptr_header = ptr;
	// format.string_table = // Not the right place
	// format.symbol_table = // Not the right placed
	// format.lc_list = init_lc_list(ptr);
	format->symbol_table = NULL;
	format->string_table = NULL;
	format->section_list = NULL;
	format->symbol_list = NULL;
	format->archive_list = NULL;
	return format;
 }
