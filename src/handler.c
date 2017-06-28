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
	check_memory_out(ptr + sym->stroff + sym->strsize);
	check_memory_out(ptr + sym->symoff + (sym->nsyms * sym->cmdsize));
	i = 0;
	while (i < sym->nsyms)
	{
		add_symbol_list(format, symbol_table, is_64);
		symbol_table = get_next_symbol(symbol_table, is_64);
		i++;
	}
}

void handle_segment_command(s_format *format, void *seg, void *ptr, bool is_64)
{
	uint32_t i;
	uint32_t	nsects;
	void		*sec;
	char		*segname;

	if (is_64 == TRUE)
	{
		nsects = ((struct segment_command_64*)seg)->nsects;
		segname = ((struct segment_command_64*)seg)->segname;
		check_memory_out(ptr + ((struct segment_command_64*)seg)->fileoff);
		check_memory_out(ptr + ((struct segment_command_64*)seg)->fileoff + ((struct segment_command_64*)seg)->filesize);
	}
	else
	{
		nsects = ((struct segment_command*)seg)->nsects;
		segname = ((struct segment_command*)seg)->segname;
		check_memory_out(ptr + ((struct segment_command*)seg)->fileoff);
		check_memory_out(ptr + ((struct segment_command*)seg)->fileoff + ((struct segment_command*)seg)->filesize);
	}
	i = 0;
	while (i < nsects)
	{
		sec = get_section_command(seg, i, is_64);
		if (format->section_list == NULL)
			init_section_list(format, sec, is_64);
		else
			add_section_list(format, sec, is_64);
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
	}
	else if (lc->cmd == LC_SEGMENT)
	{
		seg = (struct segment_command *)lc;
		handle_segment_command(format, seg, ptr, is_64);
	}
}

/*
** Handle the macho file format for 32 bits and 64 bits
*/
void	handle_macho(s_format *format, void *ptr, bool is_64)
{
	void *header;
	uint32_t sizeofcmds;
	uint32_t ncmds;
	uint32_t i;
	struct load_command *lc;

	header = ptr;
	if (is_64 == TRUE)
	{
		ncmds = ((struct mach_header_64*)header)->ncmds;
		sizeofcmds = ((struct mach_header_64*)header)->sizeofcmds;
		check_memory_out(header + sizeof(struct mach_header_64) + sizeofcmds);
	}
	else
	{
		ncmds = ((struct mach_header*)header)->ncmds;
		sizeofcmds = ((struct mach_header*)header)->sizeofcmds;
		check_memory_out(header + sizeof(struct mach_header) + sizeofcmds);
	}
	i = 0;
	lc = get_first_load_command(header, is_64);
	while (i < ncmds)
	{
		handle_load_command(format, lc, ptr, is_64);
		lc = get_next_load_command(lc);
		i++;
	}
}

/*
** Handle fat architecture
*/
void	handle_fat_arch(s_file *file, s_format *format, void *ptr, void *fat_arch, bool is_64)
{
	cpu_type_t cpu_type;
	cpu_subtype_t cpu_subtype;
	uint32_t offset;
	void *object_file;

	cpu_type = swap_uint32(((struct fat_arch *)fat_arch)->cputype);
	cpu_subtype = swap_uint32(((struct fat_arch *)fat_arch)->cpusubtype);
	offset = swap_uint32(((struct fat_arch *)fat_arch)->offset);
	object_file = get_object_file(ptr, offset);
	handle_format(object_file, file);
}

/*
** Handle the fat file
*/
void	handle_fat(s_file *file, s_format *format, void *ptr, bool is_64)
{
	uint64_t nfat_arch;
	uint64_t i;
	void *fat_arch;

	if (is_64 == TRUE)
		nfat_arch = ((struct fat_header*)ptr)->nfat_arch; // Need cast to 64bit struct
	else
		nfat_arch = ((struct fat_header*)ptr)->nfat_arch;
	nfat_arch = swap_uint32(nfat_arch);
	file->nb_archs = nfat_arch;
	i = 0;
	while (i < nfat_arch)
	{
		fat_arch = get_fat_ach(ptr, i, is_64);
		handle_fat_arch(file, format, ptr, fat_arch, is_64);
		i++;
	}
}

/*
** Handle archive file
*/
void	handle_ar(s_file *file, s_format *format, void *ptr, bool is_64)
{
	struct ar_header *ar_header;
	struct ar_magic *ar_magic;
	size_t size_name;
	void *symdef;
	uint32_t nranlibs;
	void *ranlib_arr;
	size_t i;
	struct ranlib *ranlib_elem;
	void *string_table;
	char *string_elem;
	struct ar_header *ar_header_elem;
	void *ar_object;
	char *name;
	// s_archive_file_list **file_list;


	ar_magic = get_ar_magic(ptr);
	ar_header = get_ar_header(ptr);

	size_name = get_size_from_identifier((char*)ar_header->file_identifier);
	symdef = get_symdef(ar_header, size_name);
	nranlibs = get_nranlibs(symdef);
	ranlib_arr = get_ranlib_array(symdef);
	string_table = get_ar_string_table(ranlib_arr, nranlibs);

	// if ((file_list = malloc(sizeof(s_archive_file_list) * nranlibs)) == NULL)
	// 	ft_malloc_error();

	i = 0;
	while (i < nranlibs)
	{
		ranlib_elem = get_ranlib_element(ranlib_arr, i);
		string_elem = get_ar_string_element(string_table, ranlib_elem);
		ar_header_elem = get_ar_header_element(ptr, ranlib_elem);
		size_name = get_size_from_identifier((char*)ar_header_elem->file_identifier);
		ar_object = get_ar_object(ptr, ranlib_elem, size_name);
		name = get_ar_header_name(ar_header_elem, size_name);

		// ft_putendl(string_elem);
		// ft_putstr(" ");
		// ft_putstr("\n");
		// ft_putstr(file->filename);
		// ft_putstr("(");
		// ft_putstr(name);
		// ft_putstr("):\n");
		// display_ar_header(file->filename, name);
		// ft_putstr(string_elem);
		// add_archive_list(format, ar_object, name);
		file->sub_filename = name;
		file->file_format = ARCHIVE;
		file->is_displayed = FALSE;
		handle_format(ar_object, file);
		i++;
	}
	// s_archive_list * archive_list;
	// archive_list = format->archive_list;
	// while (archive_list != NULL)
	// {
	// 	ft_putstr("\n");
	// 	ft_putstr(file->filename);
	// 	ft_putstr("(");
	// 	ft_putstr(archive_list->name);
	// 	ft_putstr("):\n");
	// 	handle_format(archive_list->ar_object, file);
	// 	archive_list = archive_list->next;
	// }
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
	{
		if (file->is_displayed == FALSE)
		{
			format->is_64 = TRUE;
			handle_macho(format, ptr, format->is_64);
			display_format(file, format);
			file->is_displayed = TRUE;
		}
	}
	else if (format->file_format == MACHO_32)
	{
		format->is_64 = FALSE;
		handle_macho(format, ptr, format->is_64);
		if (file->nb_archs == 1)
			display_format(file, format);
	}
	else if (format->file_format == FAT)
	{
		format->is_64 = FALSE;
		handle_fat(file, format, ptr, format->is_64);
	}
	else if (format->file_format == ARCHIVE)
	{
		format->is_64 = FALSE;
		handle_ar(file, format, ptr, format->is_64);
	}
	else
	{
		ft_error_str("The file is not supported\n");
	}
}
