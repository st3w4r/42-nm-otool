#include "nm-otool.h"

/*
** Add symbol to the symbol_list
*/
s_symbol_list *add_symbol_list(s_format *format, struct nlist_64 *symbol)
{
	s_symbol_list *symbol_list;

	symbol_list = format->symbol_list;
	while (symbol_list->next != NULL)
	{
		symbol_list = symbol_list->next;
	}
	if ((symbol_list->next = malloc(sizeof(s_symbol_list))) == NULL)
		ft_malloc_error();
	symbol_list->next->symbol = symbol;
	symbol_list->next->prev = symbol_list;
	symbol_list->next->next = NULL;
	return symbol_list->next;
}

/*
** Init the first symbol of the symbol_list
*/
s_symbol_list *init_symbol_list(s_format *format, struct nlist_64 *symbol)
{
	s_symbol_list *symbol_list;

	if ((symbol_list = malloc(sizeof(s_symbol_list))) == NULL)
		ft_malloc_error();
	symbol_list->symbol = symbol;
	symbol_list->prev = NULL;
	symbol_list->next = NULL;
	format->symbol_list = symbol_list;
 return format->symbol_list;
}
