#include "nm-otool.h"

void	handle_format_macho_64(s_file *file, s_format *format, void *ptr)
{
	if (file->is_displayed == FALSE)
	{
		format->is_64 = TRUE;
		handle_macho(format, ptr, format->is_64);
		display_format(file, format);
		file->is_displayed = TRUE;
	}
}

void handle_format_macho_32(s_file *file, s_format *format, void *ptr)
{
	format->is_64 = FALSE;
	handle_macho(format, ptr, format->is_64);
	if (file->nb_archs == 1)
		display_format(file, format);
}

void handle_format_fat(s_file *file, s_format *format, void *ptr)
{
	format->is_64 = FALSE;
	handle_fat(file, format, ptr, format->is_64);
}

void handle_format_archive(s_file *file, s_format *format, void *ptr)
{
	format->is_64 = FALSE;
	handle_ar(file, format, ptr, format->is_64);
}
/*
** Handle file and redirect to the correct file type
*/
void	handle_format(void *ptr, s_file *file)
{
	s_format *format;

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
