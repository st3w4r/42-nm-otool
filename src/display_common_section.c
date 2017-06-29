/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_common_section.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybarbier <ybarbier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/29 15:07:12 by ybarbier          #+#    #+#             */
/*   Updated: 2017/06/29 15:07:14 by ybarbier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm-otool.h"

void display_section_text(void *ptr, s_section_list *section_elem,
													char *segname, char *sectname, bool is_64)
{
	uint64_t addr;

	ft_putstr("Contents of (");
	ft_putstr(segname);
	ft_putstr(",");
	ft_putstr(sectname);
	ft_putstr(") section");
	ft_putstr("\n");
	addr = 0;
	if (is_64)
	{
		addr = section_elem->section_64->addr;
		ft_print_mem(ptr + section_elem->section_64->offset,
			(void*)addr, section_elem->section_64->size, is_64);
	}
	else
	{
		addr = section_elem->section_32->addr;
		ft_print_mem(ptr + section_elem->section_32->offset,
			(void*)addr, section_elem->section_32->size, is_64);

	}
	ft_putstr("\n");
}

void display_section(void *ptr, s_section_list *section_list, bool is_64)
{
	char *segname;
	char *sectname;

	if (is_64 == TRUE)
	{
		segname = section_list->section_64->segname;
		sectname = section_list->section_64->sectname;
	}
	else
	{
		segname = section_list->section_32->segname;
		sectname = section_list->section_32->sectname;
	}
	if (ft_strcmp(segname, SEG_TEXT) == 0 &&
			ft_strcmp(sectname, SECT_TEXT) == 0)
	{
		display_section_text(ptr, section_list, segname, sectname, is_64);
	}
}

void display_section_list(void *ptr, s_section_list *section_list, bool is_64)
{
	while (section_list)
	{
		display_section(ptr, section_list, is_64);
		section_list = section_list->next;
	}
}
