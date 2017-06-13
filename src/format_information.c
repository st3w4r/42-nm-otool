#include "nm-otool.h"

e_file_format	get_file_format(void *ptr)
{
	uint32_t magic;

	magic = *(uint32_t *)ptr;

	if (magic == MH_MAGIC || magic == MH_CIGAM)
		return (MACHO_32);
	else if (magic == MH_MAGIC_64)
		return (MACHO_64 || magic == MH_CIGAM_64);
	else
		return (UNKNOWN);
}

struct load_command *get_first_load_command(struct mach_header_64 *header)
{
	return ((void*)header + sizeof(*header));
}

struct load_command *get_next_load_command(struct load_command *lc)
{
	return ((void*)lc + lc->cmdsize);
}

struct nlist_64 *get_symbol_table(struct symtab_command *sym, void *ptr)
{
	return (ptr + sym->symoff);
}

void *get_string_table(struct symtab_command *sym, void *ptr)
{
	return (ptr + sym->stroff);
}


char	*get_symbol_string(struct nlist_64 *symbol_table, void *string_table, uint32_t num_symbol)
{
	return (string_table + symbol_table[num_symbol].n_un.n_strx);
}
