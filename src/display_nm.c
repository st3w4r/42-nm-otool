#include "nm-otool.h"

void display_symbol_list(void *string_table, s_section_list *section_list,
												s_symbol_list *symbol_list, bool is_64)
{
	while (symbol_list)
	{
		if (is_64 == TRUE)
		{
			if (g_prog.flags & FLAG_x)
				display_symbol_hexa_64(string_table, section_list, symbol_list);
			else
				display_symbol_short_64(string_table, section_list, symbol_list);
		}
		else
		{
			if (g_prog.flags & FLAG_x)
				display_symbol_hexa_32(string_table, section_list, symbol_list);
			else
				display_symbol_short_32(string_table, section_list, symbol_list);
		}
		symbol_list = symbol_list->next;
	}
}

void display_ar_header(char *filename, char *name)
{
	ft_putstr("\n");
	ft_putstr(filename);
	ft_putstr("(");
	ft_putstr(name);
	ft_putstr("):\n");
}

void display_format(s_file *file, s_format *format)
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
	display_symbol_list(format->string_table, format->section_list, format->symbol_list, format->is_64);
}
