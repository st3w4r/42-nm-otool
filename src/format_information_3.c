/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format_information_3.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybarbier <ybarbier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/29 15:08:11 by ybarbier          #+#    #+#             */
/*   Updated: 2017/06/29 16:48:52 by ybarbier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm_otool.h"

uint32_t	get_section_type(t_s_section_list *section_elem, bool is_64)
{
	if (is_64 == TRUE)
		return (section_elem->section_64->flags & SECTION_TYPE);
	else
		return (section_elem->section_32->flags & SECTION_TYPE);
}

uint32_t	get_section_attributes(t_s_section_list *section_elem, bool is_64)
{
	if (is_64 == TRUE)
		return (section_elem->section_64->flags & SECTION_ATTRIBUTES);
	else
		return (section_elem->section_32->flags & SECTION_ATTRIBUTES);
}

uint8_t		get_symbol_type(uint8_t n_type)
{
	return (n_type & N_TYPE);
}
