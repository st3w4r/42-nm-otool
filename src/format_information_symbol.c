/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format_information_symbol.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybarbier <ybarbier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/29 15:08:39 by ybarbier          #+#    #+#             */
/*   Updated: 2017/06/29 16:54:59 by ybarbier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm_otool.h"

char	get_symbol_type_char_section(char *segname, char *sectname)
{
	int c;

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
	return (c);
}

char	get_symbol_type_char(uint8_t n_type,
							uint64_t n_value,
							char *segname,
							char *sectname)
{
	int		c;
	uint8_t	type;

	type = get_symbol_type(n_type);
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
		c = get_symbol_type_char_section(segname, sectname);
	else if (type == N_PBUD)
		c = 'u';
	else if (type == N_INDR)
		c = 'i';
	else if (type == N_UNDF && n_value != 0)
		c = 'c';
	(n_type & N_EXT) ? (c -= 32) : (c);
	return (c);
}

bool	select_diplay_symbol(uint8_t n_type)
{
	bool	display;
	uint8_t	type;

	type = get_symbol_type(n_type);
	display = TRUE;
	if (g_prog.flags & FLAG_g)
	{
		if (!(n_type & N_EXT))
			display = FALSE;
	}
	if (g_prog.flags & FLAG_u)
	{
		if (type != N_UNDF)
			display = FALSE;
	}
	if (g_prog.flags & FLAG_U)
	{
		if (type == N_UNDF)
			display = FALSE;
	}
	return (display);
}
