#include "nm-otool.h"

void handle_symtab_command(s_format *format, struct symtab_command *sym, void *ptr)
{
	uint32_t				i;
	char						*str;
	void						*string_table;
	struct nlist_64	*symbol_table;

	symbol_table = get_symbol_table(sym, ptr);
	string_table = get_string_table(sym, ptr);
	format->symbol_table = symbol_table;
	format->string_table = string_table;

	i = 0;
	ft_putstr("NSYMS: ");ft_putnbr(sym->nsyms); ft_putstr(" ");
	while (i < sym->nsyms)
	{
			if (format->symbol_list == NULL)
				init_symbol_list(format, symbol_table);
			else
				add_symbol_list(format, symbol_table);
		// str = get_symbol_string(symbol_table, string_table, i);
		// display_nlist_64(symbol_table[i].n_un.n_strx, symbol_table[i].n_type,
			// symbol_table[i].n_sect, symbol_table[i].n_desc, symbol_table[i].n_value);
		// ft_putstr(str);
		// ft_putstr("\n");
		symbol_table++;
		i++;
	}
}

void handle_segment_command(s_format *format, struct segment_command_64 *seg, void *ptr)
{
	uint32_t i;
	struct section_64 *sec;

	ft_putstr("Segment name: ");
	ft_putstr(seg->segname);
	ft_putstr(" number of section: ");
	ft_putnbr(seg->nsects);
	ft_putstr("\n");
	i = 0;
	while (i < seg->nsects)
	{
		sec = get_section_command(seg, i);
		if (format->section_list == NULL)
			init_section_list(format, sec);
		else
			add_section_list(format, sec);
		// display_section_command(sec, ptr);
		i++;
	}
}

/*
** Handle a load command to extract information
*/
void handle_load_command(s_format *format, struct load_command *lc, void *ptr)
{
	struct symtab_command *sym;
	struct segment_command_64 *seg;


	if (lc->cmd == LC_SYMTAB)
	{
		sym = (struct symtab_command *)lc;
		handle_symtab_command(format, sym, ptr);
	}
	else if (lc->cmd == LC_SEGMENT_64)
	{
		seg = (struct segment_command_64 *)lc;
		handle_segment_command(format, seg, ptr);
		// handle_section_command((void*)seg + sizeof(struct segment_command_64), ptr);
	}
}

/*
** Handle the macho file format
*/
// void	handle_macho_64(void *ptr)
// {
// 	struct mach_header_64 *header;
// 	uint32_t ncmds;
// 	uint32_t i;
// 	struct load_command *lc;
//
// 	header = (struct mach_header_64*)ptr;
// 	display_mach_header_64(header);
// 	display_file_type(header->filetype);
// 	display_cpu_type(header->cputype, header->cpusubtype);
// 	i = 0;
// 	ncmds = header->ncmds;
// 	lc = get_first_load_command(header);
// 	while (i < ncmds)
// 	{
// 		display_load_command_type(lc->cmd);
// 		handle_load_command(lc, ptr);
// 		lc = get_next_load_command(lc);
// 		i++;
// 	}
// }

/*
** Handle the macho file format for 32 bits
*/
void	handle_macho_32(s_format *format, void*ptr)
{
	struct mach_header *header;

}

/*
** Handle the macho file format for 64 bits
*/
void	handle_macho_64(s_format *format, void *ptr)
{
	struct mach_header_64 *header;
	uint32_t ncmds;
	uint32_t i;
	struct load_command *lc;

	header = (struct mach_header_64*)ptr;
	display_mach_header_64(header);
	// display_file_type(header->filetype);
	// display_cpu_type(header->cputype, header->cpusubtype);
	i = 0;
	ncmds = header->ncmds;
	lc = get_first_load_command(header);
	while (i < ncmds)
	{
		// display_load_command_type(lc->cmd);
		handle_load_command(format, lc, ptr);
		lc = get_next_load_command(lc);
		i++;
	}
}

/*
** Handle file and redirect to the correct file type
*/
void	handle_format(void *ptr)
{
	// e_file_format file_format;
	s_format *format;

	format = init_format(ptr);
	// file_format = get_file_format(ptr);
	if (format->file_format == MACHO_64)
	{
		handle_macho_64(format, ptr);
		display_format(format);
	}
	else if (format->file_format == MACHO_32)
	{
		ft_putstr("File macho 32\n");
		handle_macho_32(format, ptr);
		// display_format(format);
	}
	else
	{
		ft_error_str_exit("The file is not supported\n");
	}
}
