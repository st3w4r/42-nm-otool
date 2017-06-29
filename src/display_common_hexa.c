/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_common_hexa.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybarbier <ybarbier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/29 15:07:05 by ybarbier          #+#    #+#             */
/*   Updated: 2017/06/29 16:33:44 by ybarbier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm_otool.h"

void	display_symbol_hexa_64(void *string_table, t_s_symbol_list *symbol_elem)
{
	uint8_t			n_type;
	char			*symbol_string;
	struct nlist_64	*symbol;

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

void	display_symbol_hexa_32(void *string_table, t_s_symbol_list *symbol_elem)
{
	uint8_t			n_type;
	char			*symbol_string;
	struct nlist	*symbol;

	symbol = symbol_elem->symbol_32;
	n_type = symbol->n_type;
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
