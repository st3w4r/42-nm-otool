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
** All typedef to simplify function prototype and variable declaration
*/
// struct load_command typedef s_load_command;


/*
** All file format supported by the program
*/
enum	file_format
{
	MACHO_32,
	MACHO_64,
	UNKNOWN
}	typedef e_file_format;

/*
** Structure to store all data use by the program
*/

struct nm {
	e_file_format	file_format;
	void *ptr_header;
}	typedef s_nm;

/*
** File: utils.c
** Description: Utilities to open and map file into memory
*/

void			*map_file_into_memory(int fd);
void			release_memory(void *ptr, int fd);
size_t			get_size_of_file(int fd);
struct stat	get_stat_of_file(int fd);
int					open_file(char *name);

/*
** File: display.c
** Description: Functions to display on the standard output
*/
void	display_file_format(e_file_format file_format);
void	display_symbol(char *str);
void	display_mach_header_32(struct mach_header *header);
void	display_mach_header_64(struct mach_header_64 *header);

/*
** File: format_information.c
** Description: Get the information from the right file type
*/
e_file_format	get_file_format(void *ptr);
struct load_command	*get_first_load_command(struct mach_header_64 *header);
struct load_command	*get_next_load_command(struct load_command *lc);
struct nlist_64 *get_symbol_table(struct symtab_command *sym, void *ptr);
void *get_string_table(struct symtab_command *sym, void *ptr);
char	*get_symbol_string(struct nlist_64 *symbol_table, void *string_table, uint32_t num_symbol);

/*
** File: handler.c
** Description: Function to handle each kind files with load command
*/
void	handle_symtab_command(struct symtab_command *sym, void *ptr);
void	handle_load_command(struct load_command *lc, void *ptr);
void	handle_macho_64(void *ptr);

#endif
