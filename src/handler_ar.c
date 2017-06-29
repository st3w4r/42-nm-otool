/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler_ar.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybarbier <ybarbier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/29 15:09:09 by ybarbier          #+#    #+#             */
/*   Updated: 2017/06/29 15:09:11 by ybarbier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm-otool.h"

void *handle_ar_object(s_file *file, void *ptr, void *ranlib_arr, size_t i)
{
	void *ar_object;
	struct ranlib *ranlib_elem;
	struct ar_header *ar_header_elem;
	size_t size_name;
	char *name;


	ranlib_elem = get_ranlib_element(ranlib_arr, i);
	ar_header_elem = get_ar_header_element(ptr, ranlib_elem);
	size_name = get_size_from_identifier((char*)ar_header_elem->file_identifier);
	ar_object = get_ar_object(ptr, ranlib_elem, size_name);
	name = get_ar_header_name(ar_header_elem);
	file->sub_filename = name;
	file->file_format = ARCHIVE;
	file->is_displayed = FALSE;
	return (ar_object);
}

/*
** Handle archive file
*/
void	handle_ar(s_file *file, void *ptr)
{
	struct ar_header *ar_header;
	void *symdef;
	void *ranlib_arr;
	size_t size_name;
	size_t i;

	ar_header = get_ar_header(ptr);
	size_name = get_size_from_identifier((char*)ar_header->file_identifier);
	symdef = get_symdef(ar_header, size_name);
	ranlib_arr = get_ranlib_array(symdef);
	i = 0;
	while (i < get_nranlibs(symdef))
	{
		handle_format(handle_ar_object(file, ptr, ranlib_arr, i), file);
		i++;
	}
}
