/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler_macho.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybarbier <ybarbier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/29 15:09:25 by ybarbier          #+#    #+#             */
/*   Updated: 2017/06/29 17:04:45 by ybarbier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm_otool.h"

void	handle_symtab_command(t_s_format *format,
							struct symtab_command *sym,
							void *ptr,
							bool is_64)
{
	uint32_t	i;
	void		*string_table;
	void		*symbol_table;

	symbol_table = get_symbol_table(sym, ptr);
	string_table = get_string_table(sym, ptr);
	format->symbol_table = symbol_table;
	format->string_table = string_table;
	i = 0;
	while (i < sym->nsyms)
	{
		add_symbol_list(format, symbol_table, is_64);
		symbol_table = get_next_symbol(symbol_table, is_64);
		i++;
	}
}

void	handle_segment_command(t_s_format *format, void *seg, bool is_64)
{
	uint32_t	i;
	uint32_t	nsects;
	void		*sec;
	char		*segname;

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

void	handle_load_command(t_s_format *format,
							struct load_command *lc,
							void *ptr,
							bool is_64)
{
	struct symtab_command	*sym;
	void					*seg;

	if (lc->cmd == LC_SYMTAB)
	{
		sym = (struct symtab_command *)lc;
		handle_symtab_command(format, sym, ptr, is_64);
	}
	else if (lc->cmd == LC_SEGMENT_64)
	{
		seg = (struct segment_command_64 *)lc;
		handle_segment_command(format, seg, is_64);
	}
	else if (lc->cmd == LC_SEGMENT)
	{
		seg = (struct segment_command *)lc;
		handle_segment_command(format, seg, is_64);
	}
}

/*
** Handle the macho file format for 32 bits and 64 bits
*/

void	handle_macho(t_s_format *format, void *ptr, bool is_64)
{
	void				*header;
	uint32_t			sizeofcmds;
	uint32_t			ncmds;
	uint32_t			i;
	struct load_command	*lc;

	header = ptr;
	if (is_64 == TRUE)
	{
		ncmds = ((struct mach_header_64*)header)->ncmds;
		sizeofcmds = ((struct mach_header_64*)header)->sizeofcmds;
	}
	else
	{
		ncmds = ((struct mach_header*)header)->ncmds;
		sizeofcmds = ((struct mach_header*)header)->sizeofcmds;
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
