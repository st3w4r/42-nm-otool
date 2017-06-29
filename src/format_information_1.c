/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format_information_1.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybarbier <ybarbier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/29 15:07:55 by ybarbier          #+#    #+#             */
/*   Updated: 2017/06/29 15:07:56 by ybarbier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm-otool.h"

e_file_format	get_file_format(void *ptr)
{
	uint32_t magic;

	magic = *(uint32_t *)ptr;

	if (magic == MH_MAGIC || magic == MH_CIGAM)
		return (MACHO_32);
	else if (magic == MH_MAGIC_64 || magic == MH_CIGAM_64)
		return (MACHO_64);
	else if (magic == FAT_MAGIC || magic == FAT_CIGAM)
		return (FAT);
	else if ((*(uint64_t *)ptr) == AR_MAGIC || (*(uint64_t *)ptr) == AR_CIGAM)
		return (ARCHIVE);
	else
		return (UNKNOWN);
}

/*
** Get object file for fat haeder
*/
void *get_object_file(void *ptr, uint32_t offset)
{
	void *object_file;

	object_file = (ptr + offset);
	check_memory_out(object_file);
	return (object_file);
}

void *get_fat_ach(void *header, int index, bool is_64)
{
	void *fat_arch;

	if (is_64 == TRUE)
	{
		fat_arch = ((void*)header + sizeof(struct fat_header))
					+ (index * sizeof(struct fat_arch));
	}
	else
	{
		fat_arch = ((void*)header + sizeof(struct fat_header))
					+ (index * sizeof(struct fat_arch));
	}
	check_memory_out(fat_arch);
	return (fat_arch);
}

struct load_command *get_first_load_command(void *header, bool is_64)
{
	struct load_command *first_load_command;

	if (is_64 == TRUE)
	{
		first_load_command = ((void*)header + sizeof(struct mach_header_64));
	}
	else
	{
		first_load_command = ((void*)header + sizeof(struct mach_header));
	}
	check_memory_out(first_load_command);
	return (first_load_command);
}

struct load_command *get_next_load_command(struct load_command *lc)
{
	struct load_command *next_load_command;

	next_load_command = ((void*)lc + lc->cmdsize);
	check_memory_out(next_load_command);
	return (next_load_command);
}
