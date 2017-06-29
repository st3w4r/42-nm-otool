/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format_information_ar_3.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybarbier <ybarbier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/29 15:08:30 by ybarbier          #+#    #+#             */
/*   Updated: 2017/06/29 15:08:31 by ybarbier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm-otool.h"

/*
** Functinos for archive
*/

struct ar_magic *get_ar_magic(void *ptr)
{
	return (ptr);
}

struct ar_header *get_ar_header(void *ptr)
{
	struct ar_header *ar_header;

	ar_header = (ptr + sizeof(struct ar_magic));
	check_memory_out(ar_header);
	return (ar_header);
}
