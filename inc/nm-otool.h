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

# include <stdio.h>
# include <stdlib.h>
# include <sys/mman.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <mach-o/loader.h>
# include <mach-o/nlist.h>
# include <mach-o/stab.h>
# include <mach-o/fat.h>
# include <mach-o/ranlib.h>
# include <mach/machine.h>
# include <stdbool.h>

# include "libft.h"

# define IS_64 TRUE
# define IS_32 FALSE

typedef unsigned char byte;

/*
** Archive header
*/
# define AR_MAGIC 0x213c617263683e0a
# define AR_CIGAM 0x0a3e686372613c21

struct ar_magic
{
	byte			magic[8];
};

struct ar_header
{
	byte			file_identifier[16];
	byte			file_modification_timestamp[12];
	byte			owner_id[6];
	byte			group_id[6];
	byte			file_mode[8];
	byte			file_size[10];
	byte			end_char[2];
};

struct symdef
{
	byte			name[20];
	uint32_t			nranlibs;
};

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
	FAT,
	FAT_64,
	ARCHIVE,
	UNKNOWN
}	 						e_file_format;

/*
** Structure to store all data use by the program
*/
// typedef struct symbol_list
// {
// 	void	*address;
// 	char	*name;
// 	char	*segment_name;
// 	char	*section_name;
// 	bool	is_external;
// 	void	*prev;
// 	void	*next;
// }								s_symbol_list;
//
// typedef struct section_lsit
// {
// 	void *ptr_section;
// 	void *prev;
// 	void *next;
// 	struct nlist *symbol_table;
// 	struct nlist_64 *symbol_table_64;
// 	s_symbol_list *symbol_list; // ptr on linked list of synbol_list
// }							s_section_list;
//
// typedef struct segment_list
// {
// 	void *segment;
// 	void *prev;
// 	void *next;
// 	s_section_list	*section_list; // ptr on linked list of section_list
// }							 s_segment_list;
//
// typedef struct lc_list
// {
// 	struct load_command *lc;
// 	void *prev;
// 	void *next;
// 	// s_segment_list	*segment_list; // ptr on linked list of segment_list
// }							s_lc_list;
//

typedef struct section_list s_section_list;
struct section_list
{
	struct section_64 *section_64;
	struct section *section_32;
	s_section_list *prev;
	s_section_list *next;
};

typedef struct symbol_list s_symbol_list;
struct symbol_list
{
	struct nlist_64 *symbol_64;
	struct nlist *symbol_32;
	s_symbol_list *prev;
	s_symbol_list *next;
};

typedef struct fromat
{
	e_file_format	file_format;
	bool	is_64;
	bool	is_big_endian;
	void *ptr_header;
	void *symbol_table;
	void *string_table;
	// s_lc_list				*lc_list; //ptr on linked list of lc_list
	s_section_list *section_list;
	s_symbol_list *symbol_list;
}	 						s_format;

typedef struct file s_file;
struct file
{
	e_file_format file_format;
	bool is_displayed;
	int nfat_arch;
};

typedef struct files s_files;
struct files
{
	char **files;
	uint32_t flags;
};
// s_file g_file;

/*
** File: section_list.c
** Description: All functions to deal with the section_list
*/
s_section_list *get_section_index(s_section_list *section_list, uint8_t index_section);
// s_section_list *add_section_list(s_format *format, struct section_64 *sec);
// s_section_list *init_section_list(s_format *format, struct section_64 *sec);
s_section_list *add_section_list(s_format *format, void *sec, bool is_64);
s_section_list *init_section_list(s_format *format, void *sec, bool is_64);

/*
** File: symbol_list.c
** Description: All functions to deal with the section_list
*/
// s_symbol_list *add_symbol_list(s_format *format, struct nlist_64 *symbol);
// s_symbol_list *init_symbol_list(s_format *format, struct nlist_64 *symbol);
s_symbol_list *add_symbol_list(s_format *format, void *symbol, bool is_64);
// s_symbol_list *init_symbol_list(s_format *format, void *symbol, bool is_64);

/*
** File: init_format.c
** Description: Create structure with all information
*/
// s_symbol_list		init_symbol_list();
// s_section_list	init_section_list();
// s_segment_list	init_segment_list();
// s_lc_list				*init_lc_list(struct mach_header_64 *header);
// s_section_list *add_section_list(s_format *format, struct section_64 *sec);
// s_section_list *init_section_list(s_format *format, struct section_64 *sec);
s_format				*init_format(void *ptr);

/*
** File: utils.c
** Description: Utilities to open and map file into memory
*/

void			*map_file_into_memory(int fd);
void			release_memory(void *ptr, int fd);
size_t			get_size_of_file(int fd);
struct stat	get_stat_of_file(int fd);
bool				is_file(int fd);
int					open_file(char *name);
void				close_file(int fd);

/*
** File: display.c
** Description: Functions to display on the standard output
*/
void	display_file_format(e_file_format file_format);
void	display_format(s_format *format);
// void	display_symbol(char *str);
void	display_mach_header_32(struct mach_header *header);
void	display_mach_header_64(struct mach_header_64 *header);

void display_load_command_type(uint32_t cmd);
void display_section_command(s_section_list *section_elem);
void display_cpu_type(cpu_type_t cputype, cpu_subtype_t cpusubtype);
void display_file_type(uint32_t filetype);
void display_nlist_64(s_section_list *section_list,
											uint32_t n_strx, uint8_t n_type, uint8_t n_sect,
											uint16_t n_desc, uint64_t n_value);


/*
** File: format_information.c
** Description: Get the information for archive file
*/
void *get_ar_object(void *ptr, struct ranlib *ranlib, size_t size_name);
void *get_ar_string_table(void *ranlib_arr, size_t nranlibs);
char *get_ar_string_element(void *string_table, struct ranlib *ranlib);
struct ar_header *get_ar_header_element(void *ptr, struct ranlib *ranlib);
struct ranlib *get_ranlib_element(void *ranlib_arr, size_t index);
void *get_ranlib_array(void *symdef);
uint32_t get_nranlibs(void *symdef);
void *get_symdef(struct ar_header *ar_header, size_t size_name);
char	*get_ar_header_name(struct ar_header *ar_header, size_t size_name);
size_t	get_size_from_identifier(char *file_identifier);
struct ar_magic *get_ar_magic(void *ptr);
struct ar_header *get_ar_header(void *ptr);
/*
** File: format_information.c
** Description: Get the information from the right file type
*/
void	*get_object_file(void *ptr, uint32_t offset);
e_file_format	get_file_format(void *ptr);
void	*get_fat_ach(void *header, int index, bool is_64);
// struct load_command	*get_first_load_command(struct mach_header_64 *header);
struct load_command *get_first_load_command(void *header, bool is_64);
struct load_command	*get_next_load_command(struct load_command *lc);
void	*get_symbol_table(struct symtab_command *sym, void *ptr);
void	*get_string_table(struct symtab_command *sym, void *ptr);
// char	*get_symbol_string(struct nlist_64 *symbol_table, void *string_table, uint32_t num_symbol);
// char	*get_symbol_string(s_symbol_list *symbol_elem, void *string_table);
char	*get_symbol_string(s_symbol_list *symbol_elem, void *string_table, bool is_64);
// struct section_64	*get_section_command(struct segment_command_64 *seg, uint32_t index_section);
void *get_section_command(void *seg, uint32_t index_section, bool is_64);
// uint32_t	get_section_type(s_section_list *section_elem);
// uint32_t	get_section_attributes(s_section_list *section_elem);
uint32_t	get_section_type(s_section_list *section_elem, bool is_64);
uint32_t	get_section_attributes(s_section_list *section_elem, bool is_64);
uint8_t		get_symbol_type(uint8_t n_type);

/*
** File: handler.c
** Description: Function to handle each kind files with load command
*/
// void	handle_symtab_command(s_format *format, struct symtab_command *sym, void *ptr);
void	handle_symtab_command(s_format *format, struct symtab_command *sym, void *ptr, bool is_64);
// void	handle_segment_command(s_format *format, struct segment_command_64 *seg, void *ptr);
void	handle_segment_command(s_format *format, void *seg, void *ptr, bool is_64);
// void	handle_load_command(s_format *format, struct load_command *lc, void *ptr);
void	handle_load_command(s_format *format, struct load_command *lc, void *ptr, bool is_64);
void	handle_macho(s_format *format, void *ptr, bool is_64);
void	handle_format(void *ptr);

/*
** File: ft_puthexa_size.c
*/
void	ft_puthexa_size(uint64_t nb, size_t size);

/*
** File: ft_print_mem.c
*/
void	ft_print_mem(void *addr, int len);

/*
** File: swap.c
** Description: Function to swap between little endian and big endian
*/
uint16_t	swap_uint16(uint16_t nb);
uint32_t	swap_uint32(uint32_t nb);
uint64_t	swap_uint64(uint64_t nb);

#endif
