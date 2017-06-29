/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_format.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybarbier <ybarbier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/29 15:09:39 by ybarbier          #+#    #+#             */
/*   Updated: 2017/06/29 15:09:40 by ybarbier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm_otool.h"

/*
** Init the structure format and return this one
*/
t_s_format *init_format(void *ptr)
{
	t_s_format					*format;

	if ((format = malloc(sizeof(t_s_format))) == NULL)
		ft_malloc_error();
	format->filename = NULL;
	format->file_format = get_file_format(ptr);
	format->ptr_header = ptr;
	format->symbol_table = NULL;
	format->string_table = NULL;
	format->section_list = NULL;
	format->symbol_list = NULL;
	format->archive_list = NULL;
	return format;
}
