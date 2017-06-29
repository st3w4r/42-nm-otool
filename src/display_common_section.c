/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_common_section.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybarbier <ybarbier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/29 15:07:12 by ybarbier          #+#    #+#             */
/*   Updated: 2017/06/29 17:17:21 by ybarbier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm_otool.h"

void	display_section_text(void *ptr,
							t_s_section_list *section_elem,
							char **arr_seg_sec_name,
							bool is_64)
{
	uint64_t addr;

	ft_putstr("Contents of (");
	ft_putstr(arr_seg_sec_name[0]);
	ft_putstr(",");
	ft_putstr(arr_seg_sec_name[1]);
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

void	display_section(void *ptr, t_s_section_list *section_list, bool is_64)
{
	char	*arr_seg_sec_name[2];

	if (is_64 == TRUE)
	{
		arr_seg_sec_name[0] = section_list->section_64->segname;
		arr_seg_sec_name[1] = section_list->section_64->sectname;
	}
	else
	{
		arr_seg_sec_name[0] = section_list->section_32->segname;
		arr_seg_sec_name[1] = section_list->section_32->sectname;
	}
	if (ft_strcmp(arr_seg_sec_name[0], SEG_TEXT) == 0 &&
			ft_strcmp(arr_seg_sec_name[1], SECT_TEXT) == 0)
	{
		display_section_text(ptr, section_list, arr_seg_sec_name, is_64);
	}
}

void	display_section_list(void *ptr,
							t_s_section_list *section_list,
							bool is_64)
{
	while (section_list)
	{
		display_section(ptr, section_list, is_64);
		section_list = section_list->next;
	}
}
