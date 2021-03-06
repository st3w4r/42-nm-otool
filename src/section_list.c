/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   section_list.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybarbier <ybarbier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/29 15:09:52 by ybarbier          #+#    #+#             */
/*   Updated: 2017/06/29 17:09:42 by ybarbier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm_otool.h"

/*
** Return the section at index in the section_list
** If no section at this index return NULL
*/

t_s_section_list	*get_section_index(t_s_section_list *section_list,
										uint8_t index_section)
{
	uint8_t				i;
	t_s_section_list	*current_section;

	current_section = section_list;
	i = 1;
	while (i < index_section && current_section != NULL)
	{
		current_section = current_section->next;
		i++;
	}
	return (current_section);
}

/*
** Add section to the section_list
** Send a struct section and recevice a t_s_section_list
*/

t_s_section_list	*add_section_list(t_s_format *format,
										void *sec,
										bool is_64)
{
	t_s_section_list *section_list;

	section_list = format->section_list;
	while (section_list->next != NULL)
	{
		section_list = section_list->next;
	}
	if ((section_list->next = malloc(sizeof(t_s_section_list))) == NULL)
		ft_malloc_error();
	if (is_64 == TRUE)
	{
		section_list->next->section_64 = sec;
		section_list->next->section_32 = NULL;
	}
	else
	{
		section_list->next->section_32 = sec;
		section_list->next->section_64 = NULL;
	}
	section_list->next->prev = section_list;
	section_list->next->next = NULL;
	return (section_list->next);
}

/*
** Init the first section of the section_list
** Send a struct section and recevice a t_s_section_list
*/

t_s_section_list	*init_section_list(t_s_format *format,
										void *sec,
										bool is_64)
{
	t_s_section_list *section_list;

	if ((section_list = malloc(sizeof(t_s_section_list))) == NULL)
		ft_malloc_error();
	if (is_64 == TRUE)
	{
		section_list->section_64 = sec;
		section_list->section_32 = NULL;
	}
	else
	{
		section_list->section_32 = sec;
		section_list->section_64 = NULL;
	}
	section_list->prev = NULL;
	section_list->next = NULL;
	format->section_list = section_list;
	return (format->section_list);
}
