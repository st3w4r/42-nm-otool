/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler_fat.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybarbier <ybarbier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/29 15:09:14 by ybarbier          #+#    #+#             */
/*   Updated: 2017/06/29 15:09:15 by ybarbier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm-otool.h"

/*
** Handle fat architecture
*/
void	handle_fat_arch(s_file *file, void *ptr, void *fat_arch)
{
	cpu_type_t cpu_type;
	cpu_subtype_t cpu_subtype;
	uint32_t offset;
	void *object_file;

	cpu_type = swap_uint32(((struct fat_arch *)fat_arch)->cputype);
	cpu_subtype = swap_uint32(((struct fat_arch *)fat_arch)->cpusubtype);
	offset = swap_uint32(((struct fat_arch *)fat_arch)->offset);
	object_file = get_object_file(ptr, offset);
	handle_format(object_file, file);
}

/*
** Handle the fat file
*/
void	handle_fat(s_file *file, void *ptr, bool is_64)
{
	uint64_t nfat_arch;
	uint64_t i;
	void *fat_arch;

	if (is_64 == TRUE)
		nfat_arch = ((struct fat_header*)ptr)->nfat_arch; // Need cast to 64bit struct
	else
		nfat_arch = ((struct fat_header*)ptr)->nfat_arch;
	nfat_arch = swap_uint32(nfat_arch);
	file->nb_archs = nfat_arch;
	i = 0;
	while (i < nfat_arch)
	{
		fat_arch = get_fat_ach(ptr, i, is_64);
		handle_fat_arch(file, ptr, fat_arch);
		i++;
	}
}
