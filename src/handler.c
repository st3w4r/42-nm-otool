#include "nm-otool.h"

void handle_symtab_command(s_format *format, struct symtab_command *sym, void *ptr, bool is_64)
{
	uint32_t	i;
	char			*str;
	void			*string_table;
	void			*symbol_table;

	symbol_table = get_symbol_table(sym, ptr);
	string_table = get_string_table(sym, ptr);
	format->symbol_table = symbol_table;
	format->string_table = string_table;

	i = 0;
	while (i < sym->nsyms)
	{
			if (format->symbol_list == NULL)
				init_symbol_list(format, symbol_table, is_64);
			else
				add_symbol_list(format, symbol_table, is_64);
		if (is_64 == TRUE)
			symbol_table = symbol_table + sizeof(struct nlist_64);
		else
			symbol_table = symbol_table + sizeof(struct nlist);
		i++;
	}
}

void handle_segment_command(s_format *format, void *seg, void *ptr, bool is_64)
{
	uint32_t i;
	uint32_t	nsects;
	// struct section_64 *sec;
	void		*sec;
	char		*segname;
	// struct segment_command_64

	if (is_64 == TRUE)
	{
		nsects = ((struct segment_command_64*)seg)->nsects;
		segname = ((struct segment_command_64*)seg)->segname;
	}
	else
	{
		nsects = ((struct segment_command*)seg)->nsects;
		segname = ((struct segment_command*)seg)->segname;
	}
	ft_putstr("Segment name: ");
	ft_putstr(segname);
	ft_putstr(" number of section: ");
	ft_putnbr(nsects);
	ft_putstr("\n");
	i = 0;
	while (i < nsects)
	{
		sec = get_section_command(seg, i, is_64);
		if (format->section_list == NULL)
			init_section_list(format, sec, is_64);
		else
			add_section_list(format, sec, is_64);
		// display_section_command(sec);
		i++;
	}
}

/*
** Handle a load command to extract information
*/
void handle_load_command(s_format *format, struct load_command *lc, void *ptr, bool is_64)
{
	struct symtab_command *sym;
	void *seg;


	if (lc->cmd == LC_SYMTAB)
	{
		sym = (struct symtab_command *)lc;
		handle_symtab_command(format, sym, ptr, is_64);
	}
	else if (lc->cmd == LC_SEGMENT_64)
	{
		seg = (struct segment_command_64 *)lc;
		handle_segment_command(format, seg, ptr, is_64);
		// handle_section_command((void*)seg + sizeof(struct segment_command_64), ptr);
	}
	else if (lc->cmd == LC_SEGMENT)
	{
		seg = (struct segment_command *)lc;
		handle_segment_command(format, seg, ptr, is_64);
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
** Handle the macho file format for 32 bits and 64 bits
*/
void	handle_macho(s_format *format, void *ptr, bool is_64)
{
	void *header;
	uint32_t ncmds;
	uint32_t i;
	struct load_command *lc;

	header = ptr;
	if (is_64 == TRUE)
		ncmds = ((struct mach_header_64*)header)->ncmds;
	else
	 	ncmds = ((struct mach_header*)header)->ncmds;
	// display_mach_header_64(header);
	// display_file_type(header->filetype);
	// display_cpu_type(header->cputype, header->cpusubtype);
	i = 0;
	// ncmds = header->ncmds;
	lc = get_first_load_command(header, is_64);
	while (i < ncmds)
	{
		// display_load_command_type(lc->cmd);
		handle_load_command(format, lc, ptr, is_64);
		lc = get_next_load_command(lc);
		i++;
	}
}

/*
** Handle the fat file
*/
void	handle_fat(s_format *format, void *ptr, bool is_64)
{
	uint32_t nfat_arch;

	if (is_64 == TRUE)
		nfat_arch = ((struct fat_header*)ptr)->nfat_arch; // Need cast to 64bit struct
	else
		nfat_arch = ((struct fat_header*)ptr)->nfat_arch;
	ft_puthexa_size(nfat_arch, 8);
	ft_putstr("\n");
	printf("%d\n", nfat_arch);
	printf("%lu\n", sizeof (uint32_t));
	nfat_arch = ((nfat_arch << 8) & 0xFF00FF00) | ((nfat_arch >> 8) & 0xFF00FF);
	nfat_arch = nfat_arch << 16 | nfat_arch >> 16;
	// nfat_arch = nfat_arch << 24;
	// 00000000 00000000 00000000 00000010 2
	// 00000000 00000000 00000010 00000000 (nfat_arch << 8)
	// 11111111 00000000 11111111 00000000 0xFF00FF00
	// 00000000 00000000 00000010 00000000 &

	// 00000000 00000000 00000000 00000000 nfat_arch >> 8
	// 11111111 00000000 11111111 00000000 0xFF00FF
	// 00000000 00000000 00000000 00000000 &
	// 00000000 00000000 00000010 00000000 |

	// 00000000 00000000 00000010 00000000
	// 00000010 00000000 00000000 00000000 nfat_arch << 16
	// 00000000 00000000 00000000 00000000 nfat_arch >> 16
	// 00000010 00000000 00000000 00000000 |

	print_mem(&nfat_arch, 4);
	printf("%d\n", nfat_arch);
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
		ft_putstr("File macho 64\n");
		format->is_64 = TRUE;
		handle_macho(format, ptr, format->is_64);
		display_format(format);
	}
	else if (format->file_format == MACHO_32)
	{
		format->is_64 = FALSE;
		ft_putstr("File macho 32\n");
		handle_macho(format, ptr, format->is_64);
		display_format(format);
	}
	else if (format->file_format == FAT)
	{
		format->is_64 = FALSE;
		ft_putstr("File FAT\n");
		handle_fat(format, ptr, format->is_64);
	}
	else if (format->file_format == FAT_64)
	{
		ft_putstr("File FAT 64\n");
	}
	else
	{
		ft_error_str_exit("The file is not supported\n");
	}
}
