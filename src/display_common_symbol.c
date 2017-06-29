/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_common_symbol.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybarbier <ybarbier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/29 15:07:21 by ybarbier          #+#    #+#             */
/*   Updated: 2017/06/29 16:41:10 by ybarbier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm_otool.h"

void	display_symbol_64(uint8_t type, uint64_t n_value,
									char *symbol_string, int type_char)
{
	if ((g_prog.flags & FLAG_u) || g_prog.flags & FLAG_j)
	{
		ft_putstr(symbol_string);
		ft_putstr("\n");
		return ;
	}
	if (type != N_UNDF)
		ft_puthexa_size(n_value, sizeof(n_value) * 2);
	else if (type == N_UNDF && n_value != 0)
		ft_puthexa_size(n_value, sizeof(n_value) * 2);
	else
		ft_putstr("                ");
	ft_putstr(" ");
	ft_putchar(type_char);
	ft_putstr(" ");
	ft_putstr(symbol_string);
	ft_putstr("\n");
}

void	display_symbol_short_64(void *string_table,
								t_s_section_list *section_list,
								t_s_symbol_list *symbol_elem)
{
	uint8_t				n_sect;
	uint8_t				n_type;
	uint64_t			n_value;
	t_s_section_list	*section_elem;
	char				*symbol_string;

	n_sect = symbol_elem->symbol_64->n_sect;
	n_value = symbol_elem->symbol_64->n_value;
	n_type = symbol_elem->symbol_64->n_type;
	symbol_string = get_symbol_string(symbol_elem, string_table, IS_64);
	section_elem = get_section_index(section_list, n_sect);
	if (n_type & N_STAB)
		return ;
	if (select_diplay_symbol(n_type) == FALSE)
		return ;
	display_symbol_64(
		get_symbol_type(n_type),
		n_value,
		get_symbol_string(symbol_elem, string_table, IS_64),
		get_symbol_type_char(get_symbol_type(n_type), n_value,
			section_elem->section_64->segname,
			section_elem->section_64->sectname,
			(n_type & N_EXT) ? TRUE : FALSE));
}

void	display_symbol_32(uint8_t type, uint32_t n_value,
							char *symbol_string, int type_char)
{
	if ((g_prog.flags & FLAG_u) || g_prog.flags & FLAG_j)
	{
		ft_putstr(symbol_string);
		ft_putstr("\n");
		return ;
	}
	if (type != N_UNDF)
		ft_puthexa_size(n_value, sizeof(n_value) * 2);
	else if (type == N_UNDF && n_value != 0)
		ft_puthexa_size(n_value, sizeof(n_value) * 2);
	else
		ft_putstr("        ");
	ft_putstr(" ");
	ft_putchar(type_char);
	ft_putstr(" ");
	ft_putstr(symbol_string);
	ft_putstr("\n");
}

void	display_symbol_short_32(void *string_table,
								t_s_section_list *section_list,
								t_s_symbol_list *symbol_elem)
{
	uint8_t				n_sect;
	uint8_t				n_type;
	uint32_t			n_value;
	t_s_section_list	*section_elem;
	char				*symbol_string;

	n_sect = symbol_elem->symbol_32->n_sect;
	n_value = symbol_elem->symbol_32->n_value;
	n_type = symbol_elem->symbol_32->n_type;
	symbol_string = get_symbol_string(symbol_elem, string_table, IS_32);
	section_elem = get_section_index(section_list, n_sect);
	if (n_type & N_STAB)
		return ;
	if (select_diplay_symbol(n_type) == FALSE)
		return ;
	display_symbol_32(
		get_symbol_type(n_type),
		n_value,
		get_symbol_string(symbol_elem, string_table, IS_32),
		get_symbol_type_char(get_symbol_type(n_type), n_value,
			section_elem->section_32->segname,
			section_elem->section_32->sectname,
			(n_type & N_EXT) ? TRUE : FALSE));
}
