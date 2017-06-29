/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format_information_2.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybarbier <ybarbier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/29 15:08:04 by ybarbier          #+#    #+#             */
/*   Updated: 2017/06/29 15:08:05 by ybarbier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm-otool.h"

/*
** Get the next symbol from the symbol_table
** Use with get_symbol_table and iterate on nsyms
*/
void *get_next_symbol(void *symbol_table, bool is_64)
{
	void *next_symbol;

	if (is_64 == TRUE)
		next_symbol = symbol_table + sizeof(struct nlist_64);
	else
		next_symbol = symbol_table + sizeof(struct nlist);
	check_memory_out(next_symbol);
	return (next_symbol);
}

/*
** Get the symbol table from a command and the ptr on the beginning of the
** mapped file. And return the ptr on the symbol tble (strcut nlist_64)
*/
void *get_symbol_table(struct symtab_command *sym, void *ptr)
{
	void *symbol_table;

	symbol_table = (ptr + sym->symoff);
	check_memory_out(symbol_table);
	return (symbol_table);
}

void *get_string_table(struct symtab_command *sym, void *ptr)
{
	void *string_table;

	string_table = (ptr + sym->stroff);
	check_memory_out(string_table);
	return (string_table);
}

char	*get_symbol_string(t_s_symbol_list *symbol_elem, void *string_table, bool is_64)
{
	char *symbol_string;

	if (is_64 == TRUE)
	{
		symbol_string = (string_table + symbol_elem->symbol_64->n_un.n_strx);
	}
	else
	{
		symbol_string = (string_table + symbol_elem->symbol_32->n_un.n_strx);
	}
	check_memory_out(symbol_string);
	return (symbol_string);
}

/*
** Send a struct segment_command witht an index and return a struct section
*/
void *get_section_command(void *seg, uint32_t index_section, bool is_64)
{
	void *section_command;

	if (is_64 == TRUE)
	{
		section_command = (void*)seg +
					sizeof(struct segment_command_64) +
					(index_section * sizeof(struct section_64));
	}
	else
	{
		section_command = (void*)seg +
					sizeof(struct segment_command) +
					(index_section * sizeof(struct section));
	}
	check_memory_out(section_command);
	return (section_command);
}
