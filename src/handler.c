#include "nm-otool.h"

void handle_symtab_command(struct symtab_command *sym, void *ptr)
{
	uint32_t				i;
	char						*str;
	void						*string_table;
	struct nlist_64	*symbol_table;

	symbol_table = get_symbol_table(sym, ptr);
	string_table = get_string_table(sym, ptr);

	i = 0;
	while (i < sym->nsyms)
	{
		str = get_symbol_string(symbol_table, string_table, i);
		ft_putendl(str);
		i++;
	}
}

/*
** Handle a load command to extract information
*/
void handle_load_command(struct load_command *lc, void *ptr)
{
	struct symtab_command *sym;


	if (lc->cmd == LC_SYMTAB)
	{
		sym = (struct symtab_command *)lc;
		handle_symtab_command(sym, ptr);
	}
}

/*
** Handle the macho file format
*/
void	handle_macho_64(void *ptr)
{
	struct mach_header_64 *header;
	uint32_t ncmds;
	uint32_t i;
	struct load_command *lc;

	header = (struct mach_header_64*)ptr;
	i = 0;
	ncmds = header->ncmds;
	lc = get_first_load_command(header);
	while (i < ncmds)
	{
		handle_load_command(lc, ptr);
		lc = get_next_load_command(lc);
		i++;
	}
}
