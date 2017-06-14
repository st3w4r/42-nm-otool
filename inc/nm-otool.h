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
#include <mach-o/stab.h>
#include <mach/machine.h>
#include <stdbool.h>

#include "libft.h"

/*
** All typedef to simplify function prototype and variable declaration
*/
// struct load_command typedef s_load_command;


/*
** All file format supported by the program
*/
typedef enum	file_format
{
	MACHO_32,
	MACHO_64,
	UNKNOWN
}	 						e_file_format;

/*
** Structure to store all data use by the program
*/
typedef struct symbol
{
	void	*address;
	char	*name;
	char	*segment_name;
	char	*section_name;
	bool	is_external;
	void	*prev;
	void	*next;
}								s_symbol_list;

typedef struct section_lsit
{
	void *ptr_section;
	void *prev;
	void *next;
	struct nlist *symbol_table;
	struct nlist_64 *symbol_table_64;
	s_symbol_list *symbol_list;
}							s_section_list;

typedef struct segment_list
{
	void *ptr_segment;
	void *prev;
	void *next;
	s_section_list	*section_list;
}							 s_segment_list;

typedef struct lc_list
{
	void *ptr_lc;
	void *prev;
	void *next;
	s_segment_list	*segment_list;
}							s_lc_list;

typedef struct fromat
{
	e_file_format	file_format;
	bool	is_64;
	bool	is_big_endian;
	void *ptr_header;
	void *string_table;
	void *symbol_table;
	s_lc_list				*lc_list;
}	 						s_format;

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

void display_load_command_type(uint32_t cmd);
void display_section_command(struct section_64 *sec, void *ptr);
void display_cpu_type(cpu_type_t cputype, cpu_subtype_t cpusubtype);
void display_file_type(uint32_t filetype);
void display_nlist_64(uint32_t n_strx, uint8_t n_type, uint8_t n_sect,
											uint16_t n_desc, uint64_t n_value);

/*
** File: format_information.c
** Description: Get the information from the right file type
*/
e_file_format	get_file_format(void *ptr);
struct load_command	*get_first_load_command(struct mach_header_64 *header);
struct load_command	*get_next_load_command(struct load_command *lc);
struct nlist_64	*get_symbol_table(struct symtab_command *sym, void *ptr);
void	*get_string_table(struct symtab_command *sym, void *ptr);
char	*get_symbol_string(struct nlist_64 *symbol_table, void *string_table, uint32_t num_symbol);
struct section_64	*get_section_command(struct segment_command_64 *seg, uint32_t index_section);
uint64_t	get_section_type(struct section_64 *sec);
uint64_t	get_section_attributes(struct section_64 *sec);
uint8_t		get_symbol_type(uint8_t n_type);

/*
** File: handler.c
** Description: Function to handle each kind files with load command
*/
void	handle_symtab_command(struct symtab_command *sym, void *ptr);
void	handle_load_command(struct load_command *lc, void *ptr);
void	handle_macho_64(void *ptr);
void	handle_format(void *ptr);

/*
** File: ft_puthexa_size.c
*/
void	ft_puthexa_size(uint64_t nb);

#endif
