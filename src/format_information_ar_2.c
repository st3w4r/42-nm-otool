/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format_information_ar_2.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybarbier <ybarbier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/29 15:08:27 by ybarbier          #+#    #+#             */
/*   Updated: 2017/06/29 15:08:27 by ybarbier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm-otool.h"

/*
** Functinos for archive
*/

void *get_ranlib_array(void *symdef)
{
	void *ranlib_array;

	ranlib_array = ((void*)symdef + sizeof(uint32_t));
	check_memory_out(ranlib_array);
	return (ranlib_array);
}

uint32_t get_nranlibs(void *symdef)
{
	uint32_t nranlibs;

	nranlibs = *(uint32_t *)symdef;
	nranlibs =  nranlibs / (sizeof(struct ranlib));
	return (nranlibs);
}

void *get_symdef(struct s_ar_header *ar_header, size_t size_name)
{
	void *symdef;

	symdef = (void*)ar_header
					+ sizeof(struct s_ar_header)
					+ size_name;
	check_memory_out(symdef);
	return (symdef);
}

char	*get_ar_header_name(struct s_ar_header *ar_header)
{
	char *name;

	name = (void*)ar_header
				+ sizeof(struct s_ar_header);
	check_memory_out(name);
	return (name);
}

size_t	get_size_from_identifier(char *file_identifier)
{
	size_t size_name;
	char *str_new;

	str_new = ft_strnew(16);
	str_new = ft_memcpy(str_new, file_identifier, 16);
	size_name = ft_atoi(&(str_new[3]));
	free(str_new);
	return (size_name);
}
