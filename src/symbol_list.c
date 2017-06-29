/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   symbol_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybarbier <ybarbier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/29 15:10:01 by ybarbier          #+#    #+#             */
/*   Updated: 2017/06/29 17:11:46 by ybarbier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm_otool.h"

/*
** Sort by insertion
*/

void			insert_before(t_s_symbol_list *s1, t_s_symbol_list *s2)
{
	s2->next = s1;
	s2->prev = s1->prev;
	s1->prev = s2;
	if (s2->prev)
	{
		s2->prev->next = s2;
	}
}

void			insert_after(t_s_symbol_list *s1, t_s_symbol_list *s2)
{
	s2->next = s1->next;
	s2->prev = s1;
	s1->next = s2;
	if (s2->next)
	{
		s2->next->prev = s2;
	}
}

void			set_format_symbol_list(t_s_format *format,
									t_s_symbol_list *symbol)
{
	while (symbol->prev != NULL)
	{
		symbol = symbol->prev;
	}
	format->symbol_list = symbol;
}

t_s_symbol_list	*add_symbol(t_s_format *format,
							t_s_symbol_list *symbol_elem,
							bool is_64)
{
	t_s_symbol_list	*symbol_list;
	t_s_symbol_list	*symbol_prev;
	void			*string_table;
	char			*string_symbol_list;
	char			*string_symbol_elem;

	symbol_list = format->symbol_list;
	string_table = format->string_table;
	string_symbol_elem = get_symbol_string(symbol_elem, string_table, is_64);
	while (symbol_list != NULL)
	{
		string_symbol_list = get_symbol_string(symbol_list,
												string_table, is_64);
		if (ft_strcmp(string_symbol_elem, string_symbol_list) < 0)
		{
			insert_before(symbol_list, symbol_elem);
			set_format_symbol_list(format, symbol_elem);
			return (symbol_elem);
		}
		symbol_prev = symbol_list;
		symbol_list = symbol_list->next;
	}
	insert_after(symbol_prev, symbol_elem);
	set_format_symbol_list(format, symbol_elem);
	return (symbol_elem);
}

/*
** Add symbol to the symbol_list
** Send a struct nlist and receive a struct symbol_list
** Init if the format symbol_list is null
*/

t_s_symbol_list	*add_symbol_list(t_s_format *format, void *symbol, bool is_64)
{
	t_s_symbol_list *symbol_elem;

	if ((symbol_elem = malloc(sizeof(t_s_symbol_list))) == NULL)
		ft_malloc_error();
	if (is_64 == TRUE)
	{
		symbol_elem->symbol_64 = symbol;
		symbol_elem->symbol_32 = NULL;
	}
	else
	{
		symbol_elem->symbol_32 = symbol;
		symbol_elem->symbol_64 = NULL;
	}
	symbol_elem->next = NULL;
	symbol_elem->prev = NULL;
	if (format->symbol_list == NULL)
		set_format_symbol_list(format, symbol_elem);
	else
		add_symbol(format, symbol_elem, is_64);
	return (symbol_elem);
}
