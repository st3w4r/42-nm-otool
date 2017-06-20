#include "nm-otool.h"

e_file_format	get_file_format(void *ptr)
{
	uint32_t magic;

	magic = *(uint32_t *)ptr;

	if (magic == MH_MAGIC || magic == MH_CIGAM)
		return (MACHO_32);
	else if (magic == MH_MAGIC_64 || magic == MH_CIGAM_64)
		return (MACHO_64);
	else
		return (UNKNOWN);
}

// struct load_command *get_first_load_command(struct mach_header_64 *header)
// {
// 	return ((void*)header + sizeof(*header));
// }

struct load_command *get_first_load_command(void *header, bool is_64)
{
	if (is_64 == TRUE)
		return ((void*)header + sizeof(struct mach_header_64));
	else
		return ((void*)header + sizeof(struct mach_header));
}

struct load_command *get_next_load_command(struct load_command *lc)
{
	return ((void*)lc + lc->cmdsize);
}

/*
** Get the symbol table from a command and the ptr on the beginning of the
** mapped file. And return the ptr on the symbol tble (strcut nlist_64)
*/
void *get_symbol_table(struct symtab_command *sym, void *ptr)
{
	return (ptr + sym->symoff);
}

void *get_string_table(struct symtab_command *sym, void *ptr)
{
	return (ptr + sym->stroff);
}


// char	*get_symbol_string(struct nlist_64 *symbol_table, void *string_table, uint32_t num_symbol)
// {
// 	return (string_table + symbol_table[num_symbol].n_un.n_strx);
// }

char	*get_symbol_string_64(s_symbol_list *symbol_elem, void *string_table)
{
	return (string_table + symbol_elem->symbol_64->n_un.n_strx);
}

char	*get_symbol_string_32(s_symbol_list *symbol_elem, void *string_table)
{
	return (string_table + symbol_elem->symbol_32->n_un.n_strx);
}

struct section_64 *get_section_command_64(struct segment_command_64 *seg, uint32_t index_section)
{
	return (void*)seg +
					sizeof(struct segment_command_64) +
					(index_section * sizeof(struct section_64));
}

struct section *get_section_command_32(struct segment_command *seg, uint32_t index_section)
{
	return (void*)seg +
					sizeof(struct segment_command) +
					(index_section * sizeof(struct section));
}

uint32_t get_section_type_64(s_section_list *section_elem)
{
	return section_elem->section_64->flags & SECTION_TYPE;
}

uint32_t get_section_attributes_64(s_section_list *section_elem)
{
	return section_elem->section_64->flags & SECTION_ATTRIBUTES;
}

uint32_t get_section_type_32(s_section_list *section_elem)
{
	return section_elem->section_32->flags & SECTION_TYPE;
}

uint32_t get_section_attributes_32(s_section_list *section_elem)
{
	return section_elem->section_32->flags & SECTION_ATTRIBUTES;
}

uint8_t get_symbol_type(uint8_t n_type)
{
	return  n_type & N_TYPE;
}
