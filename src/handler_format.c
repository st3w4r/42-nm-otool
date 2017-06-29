/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler_format.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybarbier <ybarbier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/29 15:09:21 by ybarbier          #+#    #+#             */
/*   Updated: 2017/06/29 15:09:22 by ybarbier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm_otool.h"

void	handle_format_macho_64(t_s_file *file, t_s_format *format, void *ptr)
{
	if (file->is_displayed == FALSE)
	{
		format->is_64 = TRUE;
		handle_macho(format, ptr, format->is_64);
		display_format(file, format);
		file->is_displayed = TRUE;
	}
}

void handle_format_macho_32(t_s_file *file, t_s_format *format, void *ptr)
{
	format->is_64 = FALSE;
	handle_macho(format, ptr, format->is_64);
	if (file->nb_archs == 1)
		display_format(file, format);
}

void handle_format_fat(t_s_file *file, t_s_format *format, void *ptr)
{
	format->is_64 = FALSE;
	handle_fat(file, ptr, format->is_64);
}

void handle_format_archive(t_s_file *file, t_s_format *format, void *ptr)
{
	format->is_64 = FALSE;
	handle_ar(file, ptr);
}
/*
** Handle file and redirect to the correct file type
*/
void	handle_format(void *ptr, t_s_file *file)
{
	t_s_format *format;

	format = init_format(ptr);
	format->filename = file->filename;
	if (format->file_format == MACHO_64)
		handle_format_macho_64(file, format, ptr);
	else if (format->file_format == MACHO_32)
		handle_format_macho_32(file, format, ptr);
	else if (format->file_format == FAT)
		handle_format_fat(file, format, ptr);
	else if (format->file_format == ARCHIVE)
		handle_format_archive(file, format, ptr);
	else
		ft_error_str("The file is not supported\n");
}
