/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm-otool.hh                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybarbier <ybarbier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/08 18:20:50 by ybarbier          #+#    #+#             */
/*   Updated: 2017/06/29 15:41:07 by ybarbier         ###   ########.fr       */
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

typedef unsigned char	t_byte;

/*
** Archive header
*/
# define AR_MAGIC 0x213c617263683e0a
# define AR_CIGAM 0x0a3e686372613c21

struct	s_ar_magic
{
	t_byte			magic[8];
};

struct	s_ar_header
{
	t_byte			file_identifier[16];
	t_byte			file_modification_timestamp[12];
	t_byte			owner_id[6];
	t_byte			group_id[6];
	t_byte			file_mode[8];
	t_byte			file_size[10];
	t_byte			end_char[2];
};

/*
** All typedef to simplify function prototype and variable declaration
*/

typedef enum	e_flags
{
	FLAG_a = 1 << 0,
	FLAG_g = 1 << 1,
	FLAG_m = 1 << 2,
	FLAG_p = 1 << 3,
	FLAG_u = 1 << 4,
	FLAG_U = 1 << 5,
	FLAG_x = 1 << 6,
	FLAG_j = 1 << 7
}				t_e_flag;

/*
** All file format supported by the program
*/
typedef enum	e_file_format
{
	MACHO_32,
	MACHO_64,
	FAT,
	FAT_64,
	ARCHIVE,
	UNKNOWN
}				t_e_file_format;

/*
** Structure to store all data use by the program
*/

typedef struct s_archive_list	t_s_archive_list;
struct	s_archive_list
{
	void				*ar_object;
	void				*name;
	t_s_archive_list	*prev;
	t_s_archive_list	*next;
};

typedef struct s_section_list	t_s_section_list;
struct	s_section_list
{
	struct section_64	*section_64;
	struct section		*section_32;
	t_s_section_list	*prev;
	t_s_section_list	*next;
};

typedef struct s_symbol_list	t_s_symbol_list;
struct	s_symbol_list
{
	struct nlist_64	*symbol_64;
	struct nlist	*symbol_32;
	t_s_symbol_list	*prev;
	t_s_symbol_list	*next;
};

typedef struct fromat
{
	char	*filename;
	t_e_file_format	file_format;
	bool	is_64;
	bool	is_big_endian;
	void *ptr_header;
	void *symbol_table;
	void *string_table;
	t_s_section_list *section_list;
	t_s_symbol_list *symbol_list;
	t_s_archive_list *archive_list;
}	 						s_format;

typedef struct file s_file;
struct file
{
	t_e_file_format	file_format;
	char					*filename;
	char					*sub_filename;
	uint32_t			nb_archs;
	bool					is_displayed;
};

typedef struct prog s_prog;
struct prog
{
	uint32_t nbfiles;
	uint32_t flags;
	void			*current_max_addr;
};
s_prog g_prog;


/*
** File: checker.c
** Description: Function to check if the file is valid
*/
void	check_memory_out(void *ptr);

/*
** File: archive_list.c
** Description: Function to deal with archive_list
*/
t_s_archive_list *add_archive_list(s_format *format, void *ar_object, char *name);

/*
** File: section_list.c
** Description: All functions to deal with the section_list
*/
t_s_section_list *get_section_index(t_s_section_list *section_list, uint8_t index_section);
t_s_section_list *add_section_list(s_format *format, void *sec, bool is_64);
t_s_section_list *init_section_list(s_format *format, void *sec, bool is_64);

/*
** File: symbol_list.c
** Description: All functions to deal with the section_list
*/
t_s_symbol_list *add_symbol_list(s_format *format, void *symbol, bool is_64);

/*
** File: init_format.c
** Description: Create structure with all information
*/
s_format				*init_format(void *ptr);

/*
** File: init_file.c
** Description: Create structure with all information
*/
s_file		*init_file(void *ptr);

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
void	display_ar_header(char *filename, char *name);
void	display_format(s_file *file, s_format *format);

/*
** File display_common_section.c
** Description: All function to display the text section
*/
void display_section_list(void *ptr, t_s_section_list *section_list, bool is_64);

/*
** File display_common_hexa.c
** Description: All function to display into hexa
*/
void display_symbol_hexa_64(void *string_table, t_s_symbol_list *symbol_elem);
void display_symbol_hexa_32(void *string_table, t_s_symbol_list *symbol_elem);

/*
** File display_common.c
** Description: All display function used by both programme
*/
void display_symbol_short_64(void *string_table, t_s_section_list *section_list, t_s_symbol_list *symbol_elem);
void display_symbol_short_32(void *string_table, t_s_section_list *section_list, t_s_symbol_list *symbol_elem);

/*
** File: format_information_ar_1.c
** Description: Get the information for archive file
*/
void *get_ar_object(void *ptr, struct ranlib *ranlib, size_t size_name);
void *get_ar_string_table(void *ranlib_arr, size_t nranlibs);
char *get_ar_string_element(void *string_table, struct ranlib *ranlib);
struct s_ar_header *get_ar_header_element(void *ptr, struct ranlib *ranlib);
struct ranlib *get_ranlib_element(void *ranlib_arr, size_t index);

/*
** File: format_information_ar_2.c
*/
void *get_ranlib_array(void *symdef);
uint32_t get_nranlibs(void *symdef);
void *get_symdef(struct s_ar_header *ar_header, size_t size_name);
char	*get_ar_header_name(struct s_ar_header *ar_header);
size_t	get_size_from_identifier(char *file_identifier);

/*
** File: format_information_ar_3.c
*/
struct s_ar_magic *get_ar_magic(void *ptr);
struct s_ar_header *get_ar_header(void *ptr);

/*
** File: format_information_1.c
** Description: Get the information from the right file type
*/
void	*get_object_file(void *ptr, uint32_t offset);
t_e_file_format	get_file_format(void *ptr);
void	*get_fat_ach(void *header, int index, bool is_64);
struct load_command *get_first_load_command(void *header, bool is_64);
struct load_command	*get_next_load_command(struct load_command *lc);

/*
** File: format_information_2.c
*/
void	*get_next_symbol(void *symbol_table, bool is_64);
void	*get_symbol_table(struct symtab_command *sym, void *ptr);
void	*get_string_table(struct symtab_command *sym, void *ptr);
char	*get_symbol_string(t_s_symbol_list *symbol_elem, void *string_table, bool is_64);
void *get_section_command(void *seg, uint32_t index_section, bool is_64);

/*
** File: format_information_3.c
*/
uint32_t	get_section_type(t_s_section_list *section_elem, bool is_64);
uint32_t	get_section_attributes(t_s_section_list *section_elem, bool is_64);
uint8_t		get_symbol_type(uint8_t n_type);


/*
** File: format_information_symbol.c
** Description: Functions to get the displayable information
*/
char	get_symbol_type_char_section(char *segname, char *sectname);
char	get_symbol_type_char(uint8_t type, uint64_t n_value, char *segname,
													char *sectname, bool is_external);
bool	select_diplay_symbol(uint8_t n_type);

/*
** File: handler.c
** Description: Function to handle each kind files with load command
*/

/*
** File: handler_format.c
*/
void	handle_format(void *ptr, s_file *file);

/*
** File: handler_macho.c
*/
void	handle_symtab_command(s_format *format, struct symtab_command *sym, void *ptr, bool is_64);
void	handle_segment_command(s_format *format, void *seg, bool is_64);
void	handle_load_command(s_format *format, struct load_command *lc, void *ptr, bool is_64);
void	handle_macho(s_format *format, void *ptr, bool is_64);

/*
** File: handler_ar.c
*/
void	handle_ar(s_file *file, void *ptr);

/*
** File: handler_fat.c
*/
void	handle_fat(s_file *file, void *ptr, bool is_64);

/*
** File: ft_puthexa_size.c
*/
void	ft_puthexa_size(uint64_t nb, size_t size);

/*
** File: ft_print_mem.c
*/
void	ft_print_mem(void *addr, void *memory_addr, int len, bool is_64);

/*
** File: swap.c
** Description: Function to swap between little endian and big endian
*/
uint16_t	swap_uint16(uint16_t nb);
uint32_t	swap_uint32(uint32_t nb);
uint64_t	swap_uint64(uint64_t nb);

#endif
