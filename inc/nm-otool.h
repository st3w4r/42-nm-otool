/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm-otool.hh                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybarbier <ybarbier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/08 18:20:50 by ybarbier          #+#    #+#             */
/*   Updated: 2017/06/08 18:23:12 by ybarbier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NM_OTOOL_H
# define NM_OTOOL_H

#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <mach-o/loader.h>
#include <mach-o/nlist.h>

#include "libft.h"

/*
** File: utils.c
** Description: Utilities to open and map file into memory
*/

void			*map_file_into_memory(int fd, size_t size);
void			release_memory(void *ptr, size_t size);
size_t			get_size_of_file(int fd);
struct stat	get_stat_of_file(int fd);
int					open_file(char *name);

/*
** File:
** Description:
*/

#endif
