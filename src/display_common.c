#include "nm-otool.h"

void display_section_text(void *ptr, s_section_list *section_elem,
													char *segname, char *sectname, bool is_64)
{
	uint64_t size;
	uint64_t addr;

	ft_putstr("Contents of (");
	ft_putstr(segname);
	ft_putstr(",");
	ft_putstr(sectname);
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

void display_symbol_hexa_64(void *string_table, s_section_list *section_list,
														s_symbol_list *symbol_elem)
{
	uint8_t n_type;
	char *symbol_string;
	struct nlist_64 *symbol;

	symbol = symbol_elem->symbol_64;
	n_type = symbol->n_type;
	symbol_string = get_symbol_string(symbol_elem, string_table, IS_64);
	if (n_type & N_STAB)
		return ;
	ft_puthexa_size(symbol->n_value, sizeof(symbol->n_value) * 2);
	ft_putstr(" ");
	ft_puthexa_size(symbol->n_type, sizeof(symbol->n_type) * 2);
	ft_putstr(" ");
	ft_puthexa_size(symbol->n_sect, sizeof(symbol->n_sect) * 2);
	ft_putstr(" ");
	ft_puthexa_size(symbol->n_desc, sizeof(symbol->n_desc) * 2);
	ft_putstr(" ");
	ft_puthexa_size(symbol->n_un.n_strx, sizeof(symbol->n_un.n_strx) * 2);
	ft_putstr(" ");
	ft_putstr(symbol_string);
	ft_putstr("\n");
}

void display_symbol_hexa_32(void *string_table, s_section_list *section_list, s_symbol_list *symbol_elem)
{
	uint8_t n_type;
	char *symbol_string;
	struct nlist *symbol;

	symbol = symbol_elem->symbol_32;
	n_type = symbol_elem->symbol_32->n_type;
	symbol_string = get_symbol_string(symbol_elem, string_table, IS_32);
	if (n_type & N_STAB)
		return ;
	ft_puthexa_size(symbol->n_value, sizeof(symbol->n_value) * 2);
	ft_putstr(" ");
	ft_puthexa_size(symbol->n_type, sizeof(symbol->n_type) * 2);
	ft_putstr(" ");
	ft_puthexa_size(symbol->n_sect, sizeof(symbol->n_sect) * 2);
	ft_putstr(" ");
	ft_puthexa_size(symbol->n_desc, sizeof(symbol->n_desc) * 2);
	ft_putstr(" ");
	ft_puthexa_size(symbol->n_un.n_strx, sizeof(symbol->n_un.n_strx) * 2);
	ft_putstr(" ");
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
