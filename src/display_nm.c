/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_nm.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybarbier <ybarbier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/29 15:07:29 by ybarbier          #+#    #+#             */
/*   Updated: 2017/06/29 16:42:40 by ybarbier         ###   ########.fr       */
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
			if (g_prog.flags & FLAG_x)
				display_symbol_hexa_64(string_table, symbol_list);
			else
				display_symbol_short_64(string_table, section_list,
										symbol_list);
		}
		else
		{
			if (g_prog.flags & FLAG_x)
				display_symbol_hexa_32(string_table, symbol_list);
			else
				display_symbol_short_32(string_table, section_list,
										symbol_list);
		}
		symbol_list = symbol_list->next;
	}
}

void	display_ar_header(char *filename, char *name)
{
	ft_putstr("\n");
	ft_putstr(filename);
	ft_putstr("(");
	ft_putstr(name);
	ft_putstr("):\n");
}

void	display_format(t_s_file *file, t_s_format *format)
{
	if (g_prog.nbfiles > 1 &&
			file->file_format != ARCHIVE &&
			file->file_format != FAT)
	{
		ft_putstr("\n");
		ft_putstr(format->filename);
		ft_putstr(":\n");
	}
	if (file->file_format == ARCHIVE)
	{
		display_ar_header(file->filename, file->sub_filename);
	}
	display_symbol_list(format->string_table,
						format->section_list,
						format->symbol_list,
						format->is_64);
}
