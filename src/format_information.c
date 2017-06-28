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
** Functinos for archive
*/
void *get_ar_object(void *ptr, struct ranlib *ranlib, size_t size_name)
{
	void *object;

	object = ptr
					+ ranlib->ran_off
					+ sizeof(struct ar_header)
					+ size_name;
	check_memory_out(object);
	return (object);
}

void *get_ar_string_table(void *ranlib_arr, size_t nranlibs)
{
	void *string_table;

	string_table = ranlib_arr
								+ (nranlibs * sizeof(struct ranlib))
								+ sizeof(uint32_t);
	check_memory_out(string_table);
	return (string_table);
}

char *get_ar_string_element(void *string_table, struct ranlib *ranlib)
{
	char *string_elem;

	string_elem = string_table + ranlib->ran_un.ran_strx;
	check_memory_out(string_elem);
	return (string_elem);
}

struct ar_header *get_ar_header_element(void *ptr, struct ranlib *ranlib)
{
		struct ar_header *ar_header;

		ar_header = ptr + ranlib->ran_off;
		check_memory_out(ar_header);
		return (ar_header);
}

struct ranlib *get_ranlib_element(void *ranlib_arr, size_t index)
{
	struct ranlib *ranlib;

	ranlib = (void*)ranlib_arr + (index * sizeof(struct ranlib));
	check_memory_out(ranlib);
	return (ranlib);
}

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

void *get_symdef(struct ar_header *ar_header, size_t size_name)
{
	void *symdef;

	symdef = (void*)ar_header
					+ sizeof(struct ar_header)
					+ size_name;
	check_memory_out(symdef);
	return (symdef);
}

char	*get_ar_header_name(struct ar_header *ar_header, size_t size_name)
{
	char *name;

	name = (void*)ar_header
				+ sizeof(struct ar_header);
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
					+ (index * sizeof(struct fat_arch_64));
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

/*
** Get the next symbol from the symbol_table
** Use with get_symbol_table and iterate on nsyms
*/
void *get_next_symbol(void *symbol_table, bool is_64)
{
	void *next_symbol;

	if (is_64 == TRUE)
		next_symbol = symbol_table + sizeof(struct nlist_64);
	else
		next_symbol = symbol_table + sizeof(struct nlist);
	check_memory_out(next_symbol);
	return (next_symbol);
}

/*
** Get the symbol table from a command and the ptr on the beginning of the
** mapped file. And return the ptr on the symbol tble (strcut nlist_64)
*/
void *get_symbol_table(struct symtab_command *sym, void *ptr)
{
	void *symbol_table;

	symbol_table = (ptr + sym->symoff);
	check_memory_out(symbol_table);
	return (symbol_table);
}

void *get_string_table(struct symtab_command *sym, void *ptr)
{
	void *string_table;

	string_table = (ptr + sym->stroff);
	check_memory_out(string_table);
	return (string_table);
}


// char	*get_symbol_string(struct nlist_64 *symbol_table, void *string_table, uint32_t num_symbol)
// {
// 	return (string_table + symbol_table[num_symbol].n_un.n_strx);
// }

char	*get_symbol_string(s_symbol_list *symbol_elem, void *string_table, bool is_64)
{
	char *symbol_string;

	if (is_64 == TRUE)
	{
		symbol_string = (string_table + symbol_elem->symbol_64->n_un.n_strx);
	}
	else
	{
		symbol_string = (string_table + symbol_elem->symbol_32->n_un.n_strx);
	}
	check_memory_out(symbol_string);
	return (symbol_string);
}

/*
** Send a struct segment_command witht an index and return a struct section
*/
void *get_section_command(void *seg, uint32_t index_section, bool is_64)
{
	void *section_command;

	if (is_64 == TRUE)
	{
		section_command = (void*)seg +
					sizeof(struct segment_command_64) +
					(index_section * sizeof(struct section_64));
	}
	else
	{
		section_command = (void*)seg +
					sizeof(struct segment_command) +
					(index_section * sizeof(struct section));
	}
	check_memory_out(section_command);
	return (section_command);
}

uint32_t get_section_type(s_section_list *section_elem, bool is_64)
{
	if (is_64 == TRUE)
		return (section_elem->section_64->flags & SECTION_TYPE);
	else
		return (section_elem->section_32->flags & SECTION_TYPE);
}

uint32_t get_section_attributes(s_section_list *section_elem, bool is_64)
{
	if (is_64 == TRUE)
		return (section_elem->section_64->flags & SECTION_ATTRIBUTES);
	else
		return (section_elem->section_32->flags & SECTION_ATTRIBUTES);
}

uint8_t get_symbol_type(uint8_t n_type)
{
	return  (n_type & N_TYPE);
}
