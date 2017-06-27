#include "nm-otool.h"

void display_file_format(e_file_format file_format)
{
	if (file_format == MACHO_32)
		ft_putstr("File format: MACHO_32\n");
	else if (file_format == MACHO_64)
		ft_putstr("File format: MACHO_64\n");
	else
		ft_putstr("File format: UNKNOWN\n");
}



// void display_lc_list(s_lc_list *lc_list)
// {
// 	s_lc_list *lc_list_current;
//
// 	lc_list_current = lc_list;
// 	while (lc_list_current != NULL)
// 	{
// 		display_load_command_type(lc_list_current->lc->cmd);
// 		lc_list_current = lc_list_current->prev;
// 	}
// }
//

void display_section_text(void *ptr, s_section_list *section_elem, char *segname, char *sectname, bool is_64)
{
	uint64_t size;
	uint64_t addr;

	ft_putstr("Contents of (");
	ft_putstr(segname);
	ft_putstr(",");
	ft_putstr(sectname);
	ft_putstr(") section");
	ft_putstr("\n");
	if (is_64)
	{
		addr = 0;
		addr = section_elem->section_64->addr;
		// ft_puthexa_size(section_elem->section_64->addr, sizeof(addr) * 2);
		// ft_putstr("\t");
		// print_mem((void*)section_elem->section_64->addr + section_elem->section_64->offset, section_elem->section_64->size);
		ft_print_mem(ptr + section_elem->section_64->offset, (void*)addr, section_elem->section_64->size, is_64);
		// printf("%02x ", section_elem->section_64->addr);
	}
	else
	{
		addr = 0;
		addr = section_elem->section_32->addr;
		ft_print_mem(ptr + section_elem->section_32->offset, (void*)addr, section_elem->section_32->size, is_64);

	}
	ft_putstr("\n");
}

/*
void display_section(s_section_list *section_list, bool is_64)
{
	if (is_64 == TRUE)
	{
		ft_putstr("Segment name: ");
		ft_putstr(section_list->section_64->segname);
		ft_putstr(" Section name: ");
		ft_putstr(section_list->section_64->sectname);
		ft_putstr("\n");
	}
	else
	{
		ft_putstr("Segment name: ");
		ft_putstr(section_list->section_32->segname);
		ft_putstr(" Section name: ");
		ft_putstr(section_list->section_32->sectname);
		ft_putstr("\n");
	}
}*/

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

void display_symbol_hexa_64(void *string_table, s_section_list *section_list, s_symbol_list *symbol_elem)
{
	uint8_t n_type;
	uint8_t type;
	uint8_t n_sect;
	// uint8_t type;
	uint16_t n_desc;
	uint64_t n_value;
	uint32_t n_strx;
	// s_section_list *section_elem;
	char *symbol_string;

	n_type = symbol_elem->symbol_64->n_type;
	n_sect = symbol_elem->symbol_64->n_sect;
	n_value = symbol_elem->symbol_64->n_value;
	n_desc = symbol_elem->symbol_64->n_desc;
	n_strx = symbol_elem->symbol_64->n_un.n_strx;
	type = get_symbol_type(n_type);
	symbol_string = get_symbol_string(symbol_elem, string_table, IS_64);

	if (n_type & N_STAB)
		return ;
	// if ((type == N_SECT || type == N_UNDF) && ft_strcmp(symbol_string, ""))
	ft_puthexa_size(n_value, sizeof(n_value) * 2); ft_putstr(" ");
	ft_puthexa_size(n_type, sizeof(n_type) * 2); ft_putstr(" ");
	ft_puthexa_size(n_sect, sizeof(n_sect) * 2); ft_putstr(" ");
	ft_puthexa_size(n_desc, sizeof(n_desc) * 2); ft_putstr(" ");
	ft_puthexa_size(n_strx, sizeof(n_strx) * 2); ft_putstr(" ");
	ft_putstr(symbol_string);
	ft_putstr("\n");
}

void display_symbol_hexa_32(void *string_table, s_section_list *section_list, s_symbol_list *symbol_elem)
{
	uint8_t n_type;
	uint8_t type;
	uint8_t n_sect;
	// uint8_t type;
	uint16_t n_desc;
	uint32_t n_value;
	uint32_t n_strx;
	// s_section_list *section_elem;
	char *symbol_string;

	n_type = symbol_elem->symbol_32->n_type;
	n_sect = symbol_elem->symbol_32->n_sect;
	n_value = symbol_elem->symbol_32->n_value;
	n_desc = symbol_elem->symbol_32->n_desc;
	n_strx = symbol_elem->symbol_32->n_un.n_strx;
	type = get_symbol_type(n_type);
	symbol_string = get_symbol_string(symbol_elem, string_table, IS_32);

	if (n_type & N_STAB)
		return ;
	// if ((type == N_SECT || type == N_UNDF) && ft_strcmp(symbol_string, ""))
	ft_puthexa_size(n_value, sizeof(n_value) * 2); ft_putstr(" ");
	ft_puthexa_size(n_type, sizeof(n_type) * 2); ft_putstr(" ");
	ft_puthexa_size(n_sect, sizeof(n_sect) * 2); ft_putstr(" ");
	ft_puthexa_size(n_desc, sizeof(n_desc) * 2); ft_putstr(" ");
	ft_puthexa_size(n_strx, sizeof(n_strx) * 2); ft_putstr(" ");
	ft_putstr(symbol_string);
	ft_putstr("\n");
}


void display_symbol_short_64(void *string_table, s_section_list *section_list, s_symbol_list *symbol_elem)
{
	uint8_t n_type;
	uint8_t n_sect;
	uint8_t type;
	uint16_t n_desc;
	uint64_t n_value;
	s_section_list *section_elem;
	char *symbol_string;
	char *segname;
	char *sectname;
	bool is_external;

	n_type = symbol_elem->symbol_64->n_type;
	n_sect = symbol_elem->symbol_64->n_sect;
	n_value = symbol_elem->symbol_64->n_value;
	n_desc = symbol_elem->symbol_64->n_desc;
	type = get_symbol_type(n_type);
	symbol_string = get_symbol_string(symbol_elem, string_table, IS_64);
	section_elem = get_section_index(section_list, n_sect);
	segname = section_elem->section_64->segname;
	sectname = section_elem->section_64->sectname;

	// uint32_t secattr = get_section_attributes(section_elem, IS_64);

	if (n_type & N_STAB)
		return ;


	if (n_type & N_EXT)
		is_external = TRUE;
	else
		is_external = FALSE;


	int c;

	c = '?';
	if (n_type & N_STAB)
		c = '-';
	else if (type == N_UNDF)
	{
			c = 'u';
			if (n_value != 0)
				c = 'c';
	}
	else if (type == N_ABS)
		c = 'a';
	else if (type == N_SECT)
	{
		// ft_putstr("");
		if (ft_strcmp(segname, SEG_TEXT) == 0 &&
				ft_strcmp(sectname, SECT_TEXT) == 0)
		{
			c = 't';
		}
		else if (ft_strcmp(segname, SEG_DATA) == 0 &&
						ft_strcmp(sectname, SECT_DATA) == 0)
		{
			c = 'd';
		}
		else if (ft_strcmp(segname, SEG_DATA) == 0 &&
						ft_strcmp(sectname, SECT_BSS) == 0)
		{
			c = 'b';
		}
		else
		{
			c = 's';
		}

	}
	else if (type == N_PBUD)
		c = 'u';
	else if (type == N_INDR)
		c = 'i';
	else if (type == N_UNDF && n_value != 0)
		c = 'c';

	if (is_external)
		c -= 32;

	// __Display__
	// Flag u
	if (g_prog.flags & FLAG_g)
	{
		if (!(n_type & N_EXT))
			return ;
	}

	if (g_prog.flags & FLAG_u)
	{
		if (type != N_UNDF)
			return ;
		else
			ft_putendl(symbol_string);
		return ;
	}

	// Flag U
	if (g_prog.flags & FLAG_U)
	{
		if (type == N_UNDF)
			return ;
	}

	// Flag j
	if (g_prog.flags & FLAG_j)
	{
		ft_putendl(symbol_string);
		return ;
	}
	// Default
	if (type != N_UNDF)
		ft_puthexa_size(n_value, sizeof(n_value) * 2);
	else if (type == N_UNDF && n_value != 0)
		ft_puthexa_size(n_value, sizeof(n_value) * 2);
	else
		ft_putstr("                ");
	ft_putstr(" ");
	ft_putchar(c);
	ft_putstr(" ");
	ft_putstr(symbol_string);
	ft_putstr("\n");
}


void display_symbol_short_32(void *string_table, s_section_list *section_list, s_symbol_list *symbol_elem)
{
	uint8_t n_type;
	uint8_t n_sect;
	uint8_t type;
	uint16_t n_desc;
	uint32_t n_value;
	s_section_list *section_elem;
	char *symbol_string;
	char *segname;
	char *sectname;
	bool is_external;

	n_type = symbol_elem->symbol_32->n_type;
	n_sect = symbol_elem->symbol_32->n_sect;
	n_value = symbol_elem->symbol_32->n_value;
	n_desc = symbol_elem->symbol_32->n_desc;
	type = get_symbol_type(n_type);
	symbol_string = get_symbol_string(symbol_elem, string_table, IS_32);
	section_elem = get_section_index(section_list, n_sect);
	segname = section_elem->section_32->segname;
	sectname = section_elem->section_32->sectname;

	// uint32_t secattr = get_section_attributes(section_elem, IS_32);

	if (n_type & N_STAB)
		return ;

	if ((n_type & N_EXT) == N_EXT)
		is_external = TRUE;
	else
		is_external = FALSE;

	int c;

	c = '?';
	if (n_type & N_STAB)
		c = '-';
	else if (type == N_UNDF)
	{
			c = 'u';
			if (n_value != 0)
				c = 'c';
	}
	else if (type == N_ABS)
		c = 'a';
	else if (type == N_SECT)
	{
		// ft_putstr("");
		if (ft_strcmp(segname, SEG_TEXT) == 0 &&
				ft_strcmp(sectname, SECT_TEXT) == 0)
		{
			c = 't';
		}
		else if (ft_strcmp(segname, SEG_DATA) == 0 &&
						ft_strcmp(sectname, SECT_DATA) == 0)
		{
			c = 'd';
		}
		else if (ft_strcmp(segname, SEG_DATA) == 0 &&
						ft_strcmp(sectname, SECT_BSS) == 0)
		{
			c = 'b';
		}
		else
		{
			c = 's';
		}

	}
	else if (type == N_PBUD)
		c = 'u';
	else if (type == N_INDR)
		c = 'i';
	else if (type == N_UNDF && n_value != 0)
		c = 'c';

	if (is_external)
		c -= 32;

	// __Display__
	// Flag u
	if (g_prog.flags & FLAG_g)
	{
		if (!(n_type & N_EXT))
			return ;
	}

	if (g_prog.flags & FLAG_u)
	{
		if (type != N_UNDF)
			return ;
		else
			ft_putendl(symbol_string);
		return ;
	}

	// Flag U
	if (g_prog.flags & FLAG_U)
	{
		if (type == N_UNDF)
			return ;
	}

	// Flag j
	if (g_prog.flags & FLAG_j)
	{
		ft_putendl(symbol_string);
		return ;
	}
	// Default
	if (type != N_UNDF)
		ft_puthexa_size(n_value, sizeof(n_value) * 2);
	else if (type == N_UNDF && n_value != 0)
		ft_puthexa_size(n_value, sizeof(n_value) * 2);
	else
		ft_putstr("        ");
	ft_putstr(" ");
	ft_putchar(c);
	ft_putstr(" ");
	ft_putstr(symbol_string);
	ft_putstr("\n");
}


void display_symbol_64(void *string_table, s_section_list *section_list, s_symbol_list *symbol_elem)
{
	// display_nlist_64(section_list,
	// 									symbol_elem->symbol_64->n_un.n_strx,
	// 									symbol_elem->symbol_64->n_type,
	// 									symbol_elem->symbol_64->n_sect,
	// 									symbol_elem->symbol_64->n_desc,
	// 									symbol_elem->symbol_64->n_value);

	uint8_t n_type;
	uint8_t n_sect;
	uint8_t type;
	uint16_t n_desc;
	uint64_t n_value;
	s_section_list *section_elem;
	char *symbol_string;

	n_type = symbol_elem->symbol_64->n_type;
	n_sect = symbol_elem->symbol_64->n_sect;
	n_value = symbol_elem->symbol_64->n_value;
	n_desc = symbol_elem->symbol_64->n_desc;
	type = get_symbol_type(n_type);
	symbol_string = get_symbol_string(symbol_elem, string_table, IS_64);
	section_elem = get_section_index(section_list, n_sect);


	// if ((type != N_SECT && type != N_UNDF) || ft_strcmp(symbol_string, "") == 0)
	// 	return ;
	uint32_t secattr = get_section_attributes(section_elem, IS_64);

	// ft_putnbr(section_elem->section_64->flags);
	// printf("\nFlags: %u\n", section_elem->section_64->flags & SECTION_ATTRIBUTES);

	// ft_putstr(" Section attribute: ");
	// ft_putnbr(section_elem->section_64->flags & 0x000000ff);
	// ft_putstr(" ");
	// if ((section_elem->section_64->flags & SECTION_TYPE)== S_ATTR_DEBUG)
	// 	ft_putstr("S_ATTR_DEBUG");
	if (n_type & N_STAB)
		return ;

	if (type != N_UNDF)
		ft_puthexa_size(n_value, sizeof(n_value) * 2);
	else
		ft_putstr("                ");
	ft_putstr(" ");

	if (type == N_UNDF)
		ft_putstr("(undefined) ");
	else if (type == N_ABS)
		ft_putstr("(absolute) ");
	else if (type == N_SECT)
		ft_putstr("");
	else if (type == N_PBUD)
		ft_putstr("N_PBUD ");
	else if (type == N_INDR)
		ft_putstr("(indirect) ");
	else if (type == N_UNDF && n_type == N_EXT && n_value)
		ft_putstr("(common) ");


	if (n_sect == NO_SECT)
	{
		ft_putstr("");
		// ft_putstr("NO_SECT ");
	}
	else if (n_type == MAX_SECT)
		ft_putstr("MAX_SECT ");
	else
	{

		// ft_putstr("Section n: ");
		// ft_putnbr(n_sect);
		ft_putstr("(");
		ft_putstr(section_elem->section_64->segname);
		ft_putstr(",");
		ft_putstr(section_elem->section_64->sectname);
		ft_putstr(") ");
	}




	uint16_t desc_reference;
	desc_reference = n_desc & REFERENCE_TYPE;
	// if (n_desc == REFERENCE_FLAG_UNDEFINED_NON_LAZY)
		// ft_putstr("REFERENCE_FLAG_UNDEFINED_NON_LAZY ");
	if (n_desc == REFERENCE_FLAG_UNDEFINED_LAZY)
		ft_putstr("REFERENCE_FLAG_UNDEFINED_LAZY ");
	else if (n_desc == REFERENCE_FLAG_DEFINED)
		ft_putstr("REFERENCE_FLAG_DEFINED ");
	else if (n_desc == REFERENCE_FLAG_PRIVATE_DEFINED)
		ft_putstr("REFERENCE_FLAG_PRIVATE_DEFINED ");
	else if (n_desc == REFERENCE_FLAG_PRIVATE_UNDEFINED_NON_LAZY)
		ft_putstr("REFERENCE_FLAG_PRIVATE_UNDEFINED_NON_LAZY ");
	else if (n_desc == REFERENCE_FLAG_PRIVATE_UNDEFINED_LAZY)
		ft_putstr("REFERENCE_FLAG_PRIVATE_UNDEFINED_LAZY ");
	else if (n_desc == REFERENCED_DYNAMICALLY)
		ft_putstr("[referenced dynamically] ");

	// if ((n_type & N_TYPE) == N_TYPE)
	// 	ft_putstr("N_TYPE ");
	if (n_type & N_STAB)
		ft_putstr("N_STAB ");

	if (n_type & N_EXT)
		ft_putstr("external ");
	else if (n_type & N_PEXT)
		ft_putstr("non-external (was a private external) ");
	else
		ft_putstr("non-external ");

	// if ((n_type & N_PEXT) == N_PEXT)
	// 	ft_putstr("non-external ");
	// if ((n_type & N_EXT) == N_EXT)
	// 	ft_putstr("external ");

	ft_putstr(symbol_string);

	ft_putstr("\n");

}

void display_symbol_32(void *string_table, s_section_list *section_list, s_symbol_list *symbol_elem)
{
	// display_nlist_64(section_list,
	// 									symbol_elem->symbol_64->n_un.n_strx,
	// 									symbol_elem->symbol_64->n_type,
	// 									symbol_elem->symbol_64->n_sect,
	// 									symbol_elem->symbol_64->n_desc,
	// 									symbol_elem->symbol_64->n_value);

	uint8_t n_type;
	uint8_t n_sect;
	uint8_t type;
	uint16_t n_desc;
	uint32_t n_value;
	s_section_list *section_elem;
	char *symbol_string;

	n_type = symbol_elem->symbol_32->n_type;
	n_sect = symbol_elem->symbol_32->n_sect;
	n_value = symbol_elem->symbol_32->n_value;
	n_desc = symbol_elem->symbol_32->n_desc;
	type = get_symbol_type(n_type);
	symbol_string = get_symbol_string(symbol_elem, string_table, IS_32);
	section_elem = get_section_index(section_list, n_sect);


	// if ((type != N_SECT && type != N_UNDF) || ft_strcmp(symbol_string, "") == 0)
	// 	return ;
	uint32_t secattr = get_section_attributes(section_elem, IS_32);

	// ft_putnbr(section_elem->section_64->flags);
	// printf("\nFlags: %u\n", section_elem->section_64->flags & SECTION_ATTRIBUTES);

	// ft_putstr(" Section attribute: ");
	// ft_putnbr(section_elem->section_64->flags & 0x000000ff);
	// ft_putstr(" ");
	// if ((section_elem->section_64->flags & SECTION_TYPE)== S_ATTR_DEBUG)
	// 	ft_putstr("S_ATTR_DEBUG");

	if (n_type & N_STAB)
		return ;

	if (type != N_UNDF)
		ft_puthexa_size(n_value, sizeof(n_value) * 2);
	else
		ft_putstr("        ");
	ft_putstr(" ");

	if (type == N_UNDF)
		ft_putstr("(undefined) ");
	else if (type == N_ABS)
		ft_putstr("(absolute) ");
	else if (type == N_SECT)
		ft_putstr("");
	else if (type == N_PBUD)
		ft_putstr("N_PBUD ");
	else if (type == N_INDR)
		ft_putstr("(indirect) ");
	else if (type == N_UNDF && n_type == N_EXT && n_value)
		ft_putstr("(common) ");


	if (n_sect == NO_SECT)
	{
		ft_putstr("");
		// ft_putstr("NO_SECT ");
	}
	else if (n_type == MAX_SECT)
		ft_putstr("MAX_SECT ");
	else
	{

		// ft_putstr("Section n: ");
		// ft_putnbr(n_sect);
		ft_putstr("(");
		ft_putstr(section_elem->section_32->segname);
		ft_putstr(",");
		ft_putstr(section_elem->section_32->sectname);
		ft_putstr(") ");
	}




	uint16_t desc_reference;
	desc_reference = n_desc & REFERENCE_TYPE;
	// if (n_desc == REFERENCE_FLAG_UNDEFINED_NON_LAZY)
		// ft_putstr("REFERENCE_FLAG_UNDEFINED_NON_LAZY ");
	if (n_desc == REFERENCE_FLAG_UNDEFINED_LAZY)
		ft_putstr("REFERENCE_FLAG_UNDEFINED_LAZY ");
	else if (n_desc == REFERENCE_FLAG_DEFINED)
		ft_putstr("REFERENCE_FLAG_DEFINED ");
	else if (n_desc == REFERENCE_FLAG_PRIVATE_DEFINED)
		ft_putstr("REFERENCE_FLAG_PRIVATE_DEFINED ");
	else if (n_desc == REFERENCE_FLAG_PRIVATE_UNDEFINED_NON_LAZY)
		ft_putstr("REFERENCE_FLAG_PRIVATE_UNDEFINED_NON_LAZY ");
	else if (n_desc == REFERENCE_FLAG_PRIVATE_UNDEFINED_LAZY)
		ft_putstr("REFERENCE_FLAG_PRIVATE_UNDEFINED_LAZY ");
	else if (n_desc == REFERENCED_DYNAMICALLY)
		ft_putstr("[referenced dynamically] ");

	// if ((n_type & N_TYPE) == N_TYPE)
	// 	ft_putstr("N_TYPE ");
	if (n_type & N_STAB)
		ft_putstr("N_STAB ");

	if (n_type & N_EXT)
		ft_putstr("external ");
	else if (n_type & N_PEXT)
		ft_putstr("non-external (was a private external) ");
	else
		ft_putstr("non-external ");

	ft_putstr(symbol_string);

	ft_putstr("\n");

}

void display_symbol_list(void *string_table, s_section_list *section_list, s_symbol_list *symbol_list, bool is_64)
{
	while (symbol_list)
	{
		if (is_64 == TRUE)
		{
			// display_symbol_64(string_table, section_list, symbol_list);
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

			// display_symbol_32(string_table, section_list, symbol_list);
			// display_symbol_hexa(string_table, section_list, symbol_list);
			// display_section_command(section_list);
		}
		symbol_list = symbol_list->next;
	}
}

void display_format(s_format *format)
{
	if (g_prog.nbfiles > 1)
	{
		ft_putstr("\n");
		ft_putstr(format->filename);
		ft_putstr(":\n");
	}
	display_symbol_list(format->string_table, format->section_list, format->symbol_list, format->is_64);

	// if (format->is_64 == TRUE)
	// {
	// 	// display_lc_list(format.lc_list);
	// 	// display_section(get_section_index(format->section_list, 8));
	// 	// display_mach_header_64(format->ptr_header);
	// 	// display_section_list(format->ptr_header, format->section_list, format->is_64);
	// 	display_symbol_list(format->string_table, format->section_list, format->symbol_list, format->is_64);
	// }
	// else
	// {
	// 	// display_mach_header_32(format->ptr_header);
	//
	// 	// display_section_list(format->ptr_header, format->section_list, format->is_64);
	// 	display_symbol_list(format->string_table, format->section_list, format->symbol_list, format->is_64);
	// }

}

// void	display_symbol(char *str)
// {
// 	ft_putstr(str);
// }

void	display_mach_header_32(struct mach_header *header)
{
	ft_putstr("magic: ");				ft_puthexa(header->magic);			ft_putstr("\n");
	ft_putstr("cputype: ");			ft_puthexa(header->cputype);		ft_putstr("\n");
	ft_putstr("cpusubtype: ");	ft_puthexa(header->cpusubtype);	ft_putstr("\n");
	ft_putstr("filetype: ");		ft_puthexa(header->filetype);		ft_putstr("\n");
	ft_putstr("ncmds: ");				ft_putnbr(header->ncmds);			ft_putstr("\n");
	ft_putstr("sizeofcmds: ");	ft_puthexa(header->sizeofcmds);	ft_putstr("\n");
	ft_putstr("flags: ");				ft_puthexa(header->flags);			ft_putstr("\n");
	ft_putstr("\n");
}

void	display_mach_header_64(struct mach_header_64 *header)
{
	ft_putstr("magic: ");				ft_puthexa(header->magic);			ft_putstr("\n");
	ft_putstr("cputype: ");			ft_puthexa(header->cputype);		ft_putstr("\n");
	ft_putstr("cpusubtype: ");	ft_puthexa(header->cpusubtype);	ft_putstr("\n");
	ft_putstr("filetype: ");		ft_puthexa(header->filetype);		ft_putstr("\n");
	ft_putstr("ncmds: ");				ft_putnbr(header->ncmds);			ft_putstr("\n");
	ft_putstr("sizeofcmds: ");	ft_putnbr(header->sizeofcmds);	ft_putstr("\n");
	ft_putstr("flags: ");				ft_puthexa(header->flags);			ft_putstr("\n");
	ft_putstr("reserved: ");		ft_puthexa(header->reserved);		ft_putstr("\n");

	display_cpu_type(header->cputype, header->cpusubtype);
	ft_putstr("\n");
}

void display_load_command_type(uint32_t cmd)
{
	ft_putstr("Command type: ");
	if (cmd == LC_REQ_DYLD)
		ft_putstr("LC_REQ_DYLD");
	else if (cmd == LC_SEGMENT)
		ft_putstr("LC_SEGMENT");
	else if(cmd == LC_SYMTAB)
		ft_putstr("LC_SYMTAB");
	else if(cmd == LC_SYMSEG)
		ft_putstr("LC_SYMSEG");
	else if(cmd == LC_THREAD)
		ft_putstr("LC_THREAD");
	else if(cmd == LC_UNIXTHREAD)
		ft_putstr("LC_UNIXTHREAD");
	else if(cmd == LC_LOADFVMLIB)
		ft_putstr("LC_LOADFVMLIB");
	else if(cmd == LC_IDFVMLIB)
		ft_putstr("LC_IDFVMLIB");
	else if(cmd == LC_IDENT)
		ft_putstr("LC_IDENT");
	else if(cmd == LC_FVMFILE)
		ft_putstr("LC_FVMFILE");
	else if(cmd == LC_PREPAGE)
		ft_putstr("LC_PREPAGE");
	else if(cmd == LC_DYSYMTAB)
		ft_putstr("LC_DYSYMTAB");
	else if(cmd == LC_LOAD_DYLIB)
		ft_putstr("LC_LOAD_DYLIB");
	else if(cmd == LC_ID_DYLIB)
		ft_putstr("LC_ID_DYLIB");
	else if(cmd == LC_LOAD_DYLINKER)
		ft_putstr("LC_LOAD_DYLINKER");
	else if(cmd == LC_ID_DYLINKER)
		ft_putstr("LC_ID_DYLINKER");
	else if(cmd == LC_PREBOUND_DYLIB)
		ft_putstr("LC_PREBOUND_DYLIB");
	else if(cmd == LC_ROUTINES)
		ft_putstr("LC_ROUTINES");
	else if(cmd == LC_SUB_FRAMEWORK)
		ft_putstr("LC_SUB_FRAMEWORK");
	else if(cmd == LC_SUB_UMBRELLA)
		ft_putstr("LC_SUB_UMBRELLA");
	else if(cmd == LC_SUB_CLIENT)
		ft_putstr("LC_SUB_CLIENT");
	else if(cmd == LC_SUB_LIBRARY)
		ft_putstr("LC_SUB_LIBRARY");
	else if(cmd == LC_TWOLEVEL_HINTS)
		ft_putstr("LC_TWOLEVEL_HINTS");
	else if(cmd == LC_PREBIND_CKSUM)
		ft_putstr("LC_PREBIND_CKSUM");
	else if (cmd == LC_LOAD_WEAK_DYLIB)
		ft_putstr("LC_LOAD_WEAK_DYLIB");
	else if (cmd == LC_SEGMENT_64)
		ft_putstr("LC_SEGMENT_64");
	else if (cmd == LC_ROUTINES_64)
		ft_putstr("LC_ROUTINES_64");
	else if (cmd == LC_UUID)
		ft_putstr("LC_UUID");
	else if (cmd == LC_RPATH)
		ft_putstr("LC_RPATH");
	else if (cmd == LC_CODE_SIGNATURE)
		ft_putstr("LC_CODE_SIGNATURE");
	else if (cmd == LC_SEGMENT_SPLIT_INFO)
		ft_putstr("LC_SEGMENT_SPLIT_INFO");
	else if (cmd == LC_REEXPORT_DYLIB)
		ft_putstr("LC_REEXPORT_DYLIB");
	else if (cmd == LC_LAZY_LOAD_DYLIB)
		ft_putstr("LC_LAZY_LOAD_DYLIB");
	else if (cmd == LC_ENCRYPTION_INFO)
		ft_putstr("LC_ENCRYPTION_INFO");
	else if (cmd == LC_DYLD_INFO)
		ft_putstr("LC_DYLD_INFO");
	else if (cmd == LC_DYLD_INFO_ONLY)
		ft_putstr("LC_DYLD_INFO_ONLY");
	else if (cmd == LC_LOAD_UPWARD_DYLIB)
		ft_putstr("LC_LOAD_UPWARD_DYLIB");
	else if (cmd == LC_VERSION_MIN_MACOSX)
		ft_putstr("LC_VERSION_MIN_MACOSX");
	else if (cmd == LC_VERSION_MIN_IPHONEOS)
		ft_putstr("LC_VERSION_MIN_IPHONEOS");
	else if (cmd == LC_FUNCTION_STARTS)
		ft_putstr("LC_FUNCTION_STARTS");
	else if (cmd == LC_DYLD_ENVIRONMENT)
		ft_putstr("LC_DYLD_ENVIRONMENT");
	else if (cmd == LC_MAIN)
		ft_putstr("LC_MAIN");
	else if (cmd == LC_DATA_IN_CODE)
		ft_putstr("LC_DATA_IN_CODE");
	else if (cmd == LC_SOURCE_VERSION)
		ft_putstr("LC_SOURCE_VERSION");
	else if (cmd == LC_DYLIB_CODE_SIGN_DRS)
		ft_putstr("LC_DYLIB_CODE_SIGN_DRS");
	else if (cmd == LC_ENCRYPTION_INFO_64)
		ft_putstr("LC_ENCRYPTION_INFO_64");
	else if (cmd == LC_LINKER_OPTION)
		ft_putstr("LC_LINKER_OPTION");
	else if (cmd == LC_LINKER_OPTIMIZATION_HINT)
		ft_putstr("LC_LINKER_OPTIMIZATION_HINT");
	else if (cmd == LC_VERSION_MIN_TVOS)
		ft_putstr("LC_VERSION_MIN_TVOS");
	else if (cmd == LC_VERSION_MIN_WATCHOS)
		ft_putstr("LC_VERSION_MIN_WATCHOS");
	else
		ft_putstr("UNKNOWN");
	ft_putstr("\n");
}


void display_section_command(s_section_list *section_elem)
{
	// ft_putstr("Section: Segment name: ");
	// ft_putstr(section_elem->section_64->segname);
	// ft_putstr(" Section name: ");
	// ft_putstr(section_elem->section_64->sectname);

	uint32_t sectype = get_section_type(section_elem, IS_64);

	ft_putstr(" Section type: ");
	if (sectype == S_REGULAR)
		ft_putstr("S_REGULAR");
	 if (sectype == S_ZEROFILL)
		ft_putstr("S_ZEROFILL");
	 if (sectype == S_CSTRING_LITERALS)
		ft_putstr("S_CSTRING_LITERALS");
	 if (sectype == S_4BYTE_LITERALS)
		ft_putstr("S_4BYTE_LITERALS");
	 if (sectype == S_8BYTE_LITERALS)
		ft_putstr("S_8BYTE_LITERALS");
	 if (sectype == S_LITERAL_POINTERS)
		ft_putstr("S_LITERAL_POINTERS");
	 if (sectype == S_NON_LAZY_SYMBOL_POINTERS)
		ft_putstr("S_NON_LAZY_SYMBOL_POINTERS");
	 if (sectype == S_LAZY_SYMBOL_POINTERS)
		ft_putstr("S_LAZY_SYMBOL_POINTERS");
	 if (sectype == S_SYMBOL_STUBS)
		ft_putstr("S_SYMBOL_STUBS");
	 if (sectype == S_MOD_INIT_FUNC_POINTERS)
		ft_putstr("S_MOD_INIT_FUNC_POINTERS");
	 if (sectype == S_MOD_TERM_FUNC_POINTERS)
		ft_putstr("S_MOD_TERM_FUNC_POINTERS");
	 if (sectype == S_COALESCED)
		ft_putstr("S_COALESCED");
	 if (sectype == S_GB_ZEROFILL)
		ft_putstr("S_GB_ZEROFILL");
	 if (sectype == S_INTERPOSING)
		ft_putstr("S_INTERPOSING");
	 if (sectype == S_16BYTE_LITERALS)
		ft_putstr("S_16BYTE_LITERALS");
	 if (sectype == S_DTRACE_DOF)
		ft_putstr("S_DTRACE_DOF");
	 if (sectype == S_LAZY_DYLIB_SYMBOL_POINTERS)
		ft_putstr("S_LAZY_DYLIB_SYMBOL_POINTERS");
	 if (sectype == S_THREAD_LOCAL_REGULAR)
		ft_putstr("S_THREAD_LOCAL_REGULAR");
	 if (sectype == S_THREAD_LOCAL_ZEROFILL)
		ft_putstr("S_THREAD_LOCAL_ZEROFILL");
	 if (sectype == S_THREAD_LOCAL_VARIABLES)
		ft_putstr("S_THREAD_LOCAL_VARIABLES");
	 if (sectype == S_THREAD_LOCAL_VARIABLE_POINTERS)
		ft_putstr("S_THREAD_LOCAL_VARIABLE_POINTERS");
	 if (sectype == S_THREAD_LOCAL_INIT_FUNCTION_POINTERS)
		ft_putstr("S_THREAD_LOCAL_INIT_FUNCTION_POINTERS");
	// else
	// 	ft_putstr("UNKNOWN");


	uint32_t secattr = get_section_attributes(section_elem, IS_64);
	ft_putstr(" Section attribute: ");
	if (secattr == SECTION_ATTRIBUTES_USR)
		ft_putstr("SECTION_ATTRIBUTES_USR");
	if (secattr == S_ATTR_PURE_INSTRUCTIONS)
		ft_putstr("S_ATTR_PURE_INSTRUCTIONS");
	if (secattr == S_ATTR_NO_TOC)
		ft_putstr("S_ATTR_NO_TOC");
	if (secattr == S_ATTR_STRIP_STATIC_SYMS)
		ft_putstr("S_ATTR_STRIP_STATIC_SYMS");
	if (secattr == S_ATTR_NO_DEAD_STRIP)
		ft_putstr("S_ATTR_NO_DEAD_STRIP");
	if (secattr == S_ATTR_LIVE_SUPPORT)
		ft_putstr("S_ATTR_LIVE_SUPPORT");
	if (secattr == S_ATTR_SELF_MODIFYING_CODE)
		ft_putstr("S_ATTR_SELF_MODIFYING_CODE");
	if (secattr == S_ATTR_DEBUG)
		ft_putstr("S_ATTR_DEBUG");
	if (secattr == SECTION_ATTRIBUTES_SYS)
		ft_putstr("SECTION_ATTRIBUTES_SYS");
	if (secattr == S_ATTR_SOME_INSTRUCTIONS)
		ft_putstr("S_ATTR_SOME_INSTRUCTIONS");
	if (secattr == S_ATTR_EXT_RELOC)
		ft_putstr("S_ATTR_EXT_RELOC");
	if (secattr == S_ATTR_LOC_RELOC)
		ft_putstr("S_ATTR_LOC_RELOC");
	// else
	// 	ft_putstr("UNKNOWN");
	ft_putstr("\n");
}


void display_cpu_type(cpu_type_t cputype, cpu_subtype_t cpusubtype)
{
	cpu_type_t type;
	cpu_subtype_t subtype;

	type = cputype;// & CPU_ARCH_MASK;

	ft_putstr("CPU Type: ");
	if (type == CPU_TYPE_ANY)
		ft_putstr("CPU_TYPE_ANY");
	else if (type == CPU_TYPE_VAX)
		ft_putstr("CPU_TYPE_VAX");
	else if (type == CPU_TYPE_MC680x0)
		ft_putstr("CPU_TYPE_MC680x0");
	else if (type == CPU_TYPE_X86)
		ft_putstr("CPU_TYPE_X86");
	else if (type == CPU_TYPE_I386)
		ft_putstr("CPU_TYPE_I386");
	else if (type == CPU_TYPE_X86_64)
		ft_putstr("CPU_TYPE_X86_64");
	else if (type == CPU_TYPE_MC98000)
		ft_putstr("CPU_TYPE_MC98000");
	else if (type == CPU_TYPE_HPPA)
		ft_putstr("CPU_TYPE_HPPA");
	else if (type == CPU_TYPE_ARM)
		ft_putstr("CPU_TYPE_ARM");
	else if (type == CPU_TYPE_ARM64)
		ft_putstr("CPU_TYPE_ARM64");
	else if (type == CPU_TYPE_MC88000)
		ft_putstr("CPU_TYPE_MC88000");
	else if (type == CPU_TYPE_SPARC)
		ft_putstr("CPU_TYPE_SPARC");
	else if (type == CPU_TYPE_I860)
		ft_putstr("CPU_TYPE_I860");
	else if (type == CPU_TYPE_POWERPC)
		ft_putstr("CPU_TYPE_POWERPC");
	else if (type == CPU_TYPE_POWERPC64)
		ft_putstr("CPU_TYPE_POWERPC64");
	else
		ft_putstr("UNKNOWN");
	ft_putstr("\n");

	subtype = cpusubtype;// & CPU_SUBTYPE_MASK;

	ft_putstr("CPU Subtype: ");
	if (subtype == CPU_SUBTYPE_MULTIPLE)
		ft_putstr("CPU_SUBTYPE_MULTIPLE");
	else if (subtype == CPU_SUBTYPE_LITTLE_ENDIAN)
		ft_putstr("CPU_SUBTYPE_LITTLE_ENDIAN");
	else if (subtype == CPU_SUBTYPE_BIG_ENDIAN)
		ft_putstr("CPU_SUBTYPE_BIG_ENDIAN");
	else
		ft_putstr("UNKNOWN");
	ft_putstr("\n");

}


void display_file_type(uint32_t filetype)
{
	ft_putstr("File type: ");
	if (filetype == MH_OBJECT)
		ft_putstr("MH_OBJECT");
	else if (filetype == MH_EXECUTE)
		ft_putstr("MH_EXECUTE");
	else if (filetype == MH_FVMLIB)
		ft_putstr("MH_FVMLIB");
	else if (filetype == MH_CORE)
		ft_putstr("MH_CORE");
	else if (filetype == MH_PRELOAD)
		ft_putstr("MH_PRELOAD");
	else if (filetype == MH_DYLIB)
		ft_putstr("MH_DYLIB");
	else if (filetype == MH_DYLINKER)
		ft_putstr("MH_DYLINKER");
	else if (filetype == MH_BUNDLE)
		ft_putstr("MH_BUNDLE");
	else if (filetype == MH_DYLIB_STUB)
		ft_putstr("MH_DYLIB_STUB");
	else if (filetype == MH_DSYM)
		ft_putstr("MH_DSYM");
	else if (filetype == MH_KEXT_BUNDLE)
		ft_putstr("MH_KEXT_BUNDLE");
	else if (filetype == MH_NOUNDEFS)
		ft_putstr("MH_NOUNDEFS");
	else if (filetype == MH_INCRLINK)
		ft_putstr("MH_INCRLINK");
	else if (filetype == MH_DYLDLINK)
		ft_putstr("MH_DYLDLINK");
	else if (filetype == MH_BINDATLOAD)
		ft_putstr("MH_BINDATLOAD");
	else if (filetype == MH_PREBOUND)
		ft_putstr("MH_PREBOUND");
	else if (filetype == MH_SPLIT_SEGS)
		ft_putstr("MH_SPLIT_SEGS");
	else if (filetype == MH_LAZY_INIT)
		ft_putstr("MH_LAZY_INIT");
	else if (filetype == MH_TWOLEVEL)
		ft_putstr("MH_TWOLEVEL");
	else if (filetype == MH_FORCE_FLAT)
		ft_putstr("MH_FORCE_FLAT");
	else if (filetype == MH_NOMULTIDEFS)
		ft_putstr("MH_NOMULTIDEFS");
	else if (filetype == MH_NOFIXPREBINDING)
		ft_putstr("MH_NOFIXPREBINDING");
	else if (filetype == MH_PREBINDABLE)
		ft_putstr("MH_PREBINDABLE");
	else if (filetype == MH_ALLMODSBOUND)
		ft_putstr("MH_ALLMODSBOUND");
	else if (filetype == MH_SUBSECTIONS_VIA_SYMBOLS)
		ft_putstr("MH_SUBSECTIONS_VIA_SYMBOLS");
	else if (filetype == MH_CANONICAL)
		ft_putstr("MH_CANONICAL");
	else if (filetype == MH_WEAK_DEFINES)
		ft_putstr("MH_WEAK_DEFINES");
	else if (filetype == MH_BINDS_TO_WEAK)
		ft_putstr("MH_BINDS_TO_WEAK");
	else if (filetype == MH_ALLOW_STACK_EXECUTION)
		ft_putstr("MH_ALLOW_STACK_EXECUTION");
	else if (filetype == MH_ROOT_SAFE)
		ft_putstr("MH_ROOT_SAFE");
	else if (filetype == MH_SETUID_SAFE)
		ft_putstr("MH_SETUID_SAFE");
	else if (filetype == MH_NO_REEXPORTED_DYLIBS)
		ft_putstr("MH_NO_REEXPORTED_DYLIBS");
	else if (filetype == MH_PIE)
		ft_putstr("MH_PIE");
	else if (filetype == MH_DEAD_STRIPPABLE_DYLIB)
		ft_putstr("MH_DEAD_STRIPPABLE_DYLIB");
	else if (filetype == MH_HAS_TLV_DESCRIPTORS)
		ft_putstr("MH_HAS_TLV_DESCRIPTORS");
	else if (filetype == MH_NO_HEAP_EXECUTION)
		ft_putstr("MH_NO_HEAP_EXECUTION");
	else if (filetype == MH_APP_EXTENSION_SAFE)
		ft_putstr("MH_APP_EXTENSION_SAFE");
	else
		ft_putstr("UNKNOWN");
	ft_putstr("\n");
}

// void display_nlist_64(s_section_list *section_list,
// 	uint32_t n_strx, uint8_t n_type, uint8_t n_sect,
// 	uint16_t n_desc, uint64_t n_value)
// {
// 	// n_type
// 	if (n_type == N_STAB)
// 		ft_putstr("N_STAB ");
// 	else if (n_type == N_PEXT)
// 		ft_putstr("N_PEXT ");
// 	else if (n_type == N_TYPE)
// 		ft_putstr("N_TYPE ");
// 	else if (n_type == N_EXT)
// 		ft_putstr("N_EXT ");
//
// 	uint8_t type = get_symbol_type(n_type);
//
// 	if (type == N_UNDF)
// 		ft_putstr("N_UNDF ");
// 	else if (type == N_ABS)
// 		ft_putstr("N_ABS ");
// 	else if (type == N_SECT)
// 		ft_putstr("N_SECT ");
// 	else if (type == N_PBUD)
// 		ft_putstr("N_PBUD ");
// 	else if (type == N_INDR)
// 		ft_putstr("N_INDR ");
//
//
//
// 	// n_sect
// 	if (n_sect == NO_SECT)
// 		ft_putstr("NO_SECT ");
// 	else if (n_type == MAX_SECT)
// 		ft_putstr("MAX_SECT ");
// 	else {
// 		s_section_list *section_elem = get_section_index(section_list, n_sect);
//
// 		ft_putstr("Section n: ");
// 		ft_putnbr(n_sect);
// 		ft_putstr(" (");
// 		ft_putstr(section_elem->section_64->segname);
// 		ft_putstr(",");
// 		ft_putstr(section_elem->section_64->sectname);
// 		ft_putstr(") ");
// 	}
//
//
// 	// n_desc
// 	ft_putstr(" ndesc: ");
// 	if (n_desc == N_GSYM)
// 		ft_putstr("N_GSYM");
// 	else if (n_desc == N_FNAME)
// 		ft_putstr("N_FNAME");
// 	else if (n_desc == N_FUN)
// 		ft_putstr("N_FUN");
// 	else if (n_desc == N_STSYM)
// 		ft_putstr("N_STSYM");
// 	else if (n_desc == N_LCSYM)
// 		ft_putstr("N_LCSYM");
// 	else if (n_desc == N_BNSYM)
// 		ft_putstr("N_BNSYM");
// 	else if (n_desc == N_AST)
// 		ft_putstr("N_AST");
// 	else if (n_desc == N_OPT)
// 		ft_putstr("N_OPT");
// 	else if (n_desc == N_RSYM)
// 		ft_putstr("N_RSYM");
// 	else if (n_desc == N_SLINE)
// 		ft_putstr("N_SLINE");
// 	else if (n_desc == N_ENSYM)
// 		ft_putstr("N_ENSYM");
// 	else if (n_desc == N_SSYM)
// 		ft_putstr("N_SSYM");
// 	else if (n_desc == N_SO)
// 		ft_putstr("N_SO");
// 	else if (n_desc == N_OSO)
// 		ft_putstr("N_OSO");
// 	else if (n_desc == N_LSYM)
// 		ft_putstr("N_LSYM");
// 	else if (n_desc == N_BINCL)
// 		ft_putstr("N_BINCL");
// 	else if (n_desc == N_SOL)
// 		ft_putstr("N_SOL");
// 	else if (n_desc == N_PARAMS)
// 		ft_putstr("N_PARAMS");
// 	else if (n_desc == N_VERSION)
// 		ft_putstr("N_VERSION");
// 	else if (n_desc == N_OLEVEL)
// 		ft_putstr("N_OLEVEL");
// 	else if (n_desc == N_PSYM)
// 		ft_putstr("N_PSYM");
// 	else if (n_desc == N_EINCL)
// 		ft_putstr("N_EINCL");
// 	else if (n_desc == N_ENTRY)
// 		ft_putstr("N_ENTRY");
// 	else if (n_desc == N_LBRAC)
// 		ft_putstr("N_LBRAC");
// 	else if (n_desc == N_EXCL)
// 		ft_putstr("N_EXCL");
// 	else if (n_desc == N_RBRAC)
// 		ft_putstr("N_RBRAC");
// 	else if (n_desc == N_BCOMM)
// 		ft_putstr("N_BCOMM");
// 	else if (n_desc == N_ECOMM)
// 		ft_putstr("N_ECOMM");
// 	else if (n_desc == N_ECOML)
// 		ft_putstr("N_ECOML");
// 	else if (n_desc == N_LENG)
// 		ft_putstr("N_LENG");
// 	else if (n_desc == N_PC)
// 		ft_putstr("N_PC");
// 	else
// 		ft_putstr("UNKNOWN");
// 	ft_putstr(" ");
//
// 	// SET_COMM_ALIGN(n_desc,1);
// 	// uint16_t desc_reference;
// 	// desc_reference = n_desc & REFERENCE_TYPE;
// 	// if (n_desc == REFERENCE_FLAG_UNDEFINED_NON_LAZY)
// 	// 	ft_putstr("REFERENCE_FLAG_UNDEFINED_NON_LAZY ");
// 	// else if (n_desc == REFERENCE_FLAG_UNDEFINED_LAZY)
// 	// 	ft_putstr("REFERENCE_FLAG_UNDEFINED_LAZY ");
// 	// else if (n_desc == REFERENCE_FLAG_DEFINED)
// 	// 	ft_putstr("REFERENCE_FLAG_DEFINED ");
// 	// else if (n_desc == REFERENCE_FLAG_PRIVATE_DEFINED)
// 	// 	ft_putstr("REFERENCE_FLAG_PRIVATE_DEFINED ");
// 	// else if (n_desc == REFERENCE_FLAG_PRIVATE_UNDEFINED_NON_LAZY)
// 	// 	ft_putstr("REFERENCE_FLAG_PRIVATE_UNDEFINED_NON_LAZY ");
// 	// else if (n_desc == REFERENCE_FLAG_PRIVATE_UNDEFINED_LAZY)
// 	// 	ft_putstr("REFERENCE_FLAG_PRIVATE_UNDEFINED_LAZY ");
//
//
// 	ft_puthexa_size(n_value);
// 	ft_putstr(" ");
// 	ft_puthexa(n_type);
// 	ft_putstr(" ");
// 	ft_puthexa(n_sect);
// 	ft_putstr(" ");
// 	ft_puthexa(n_desc);
// 	ft_putstr(" ");
// 	ft_puthexa_size(n_strx);
// 	ft_putstr(" ");
// 	ft_putstr("\n");
// }
