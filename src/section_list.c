#include "nm-otool.h"

/*
** Return the section at index in the section_list
** If no section at this index return NULL
*/
s_section_list *get_section_index(s_section_list *section_list, uint8_t index_section)
{
	uint8_t i;
	s_section_list *current_section;

	current_section = section_list;
	i = 1;
	while (i < index_section && current_section != NULL)
	{
		current_section = current_section->next;
		i++;
	}
	return current_section;
}


/*
** Add section to the section_list
*/
s_section_list *add_section_list(s_format *format, struct section_64 *sec)
{
	s_section_list *section_list;

	section_list = format->section_list;
	while (section_list->next != NULL)
	{
		section_list = section_list->next;
	}
	if ((section_list->next = malloc(sizeof(s_section_list))) == NULL)
		ft_malloc_error();
	section_list->next->section = sec;
	section_list->next->prev = section_list;
	section_list->next->next = NULL;
	return section_list->next;
}

/*
** Init the first section of the section_list
*/
s_section_list *init_section_list(s_format *format, struct section_64 *sec)
{
	s_section_list *section_list;

	if ((section_list = malloc(sizeof(s_section_list))) == NULL)
		ft_malloc_error();
	section_list->section = sec;
	section_list->prev = NULL;
	section_list->next = NULL;
	format->section_list = section_list;
 return format->section_list;
}