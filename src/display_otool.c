/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_otool.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybarbier <ybarbier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/29 15:07:35 by ybarbier          #+#    #+#             */
/*   Updated: 2017/06/29 16:44:01 by ybarbier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm_otool.h"

void	display_symbol_list(void *string_table,
							t_s_section_list *section_list,
							t_s_symbol_list *symbol_list,
							bool is_64)
{
	while (symbol_list)
	{
		if (is_64 == TRUE)
		{
			display_symbol_short_64(string_table, section_list, symbol_list);
		}
		else
		{
			display_symbol_short_32(string_table, section_list, symbol_list);
		}
		symbol_list = symbol_list->next;
	}
}

void	display_ar_header(char *filename, char *name)
{
	ft_putstr(filename);
	ft_putstr("(");
	ft_putstr(name);
	ft_putstr("):\n");
}

void	display_format(t_s_file *file, t_s_format *format)
{
	if (file->file_format == ARCHIVE && file->is_displayed == FALSE)
	{
		ft_putstr("Archive : ");
		ft_putstr(file->filename);
		ft_putstr("\n");
		file->is_displayed = TRUE;
	}
	if (file->file_format == ARCHIVE)
	{
		display_ar_header(file->filename, file->sub_filename);
	}
	if (file->file_format != ARCHIVE)
	{
		ft_putstr(format->filename);
		ft_putstr(":\n");
	}
	display_section_list(format->ptr_header,
						format->section_list,
						format->is_64);
}
