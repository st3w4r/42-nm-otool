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
//	else if (magic == FAT_MAGIC_64 || magic == FAT_CIGAM_64)
//		return (FAT_64);
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
	return (object);
}

void *get_ar_string_table(void *ranlib_arr, size_t nranlibs)
{
	void *string_table;

	string_table = ranlib_arr
								+ (nranlibs * sizeof(struct ranlib))
								+ sizeof(uint32_t);
	return (string_table);
}

char *get_ar_string_element(void *string_table, struct ranlib *ranlib)
{
	char *string_elem;

	string_elem = string_table + ranlib->ran_un.ran_strx;
	return string_elem;
}

struct ar_header *get_ar_header_element(void *ptr, struct ranlib *ranlib)
{
		struct ar_header *ar_header;

		ar_header = ptr + ranlib->ran_off;
		return (ar_header);
}

struct ranlib *get_ranlib_element(void *ranlib_arr, size_t index)
{
	struct ranlib *ranlib;

	ranlib = (void*)ranlib_arr + (index * sizeof(struct ranlib));
	return (ranlib);
}

void *get_ranlib_array(void *symdef)
{
	return ((void*)symdef + sizeof(uint32_t));
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
	return (symdef);
}

char	*get_ar_header_name(struct ar_header *ar_header, size_t size_name)
{
	char *name;

	name = (void*)ar_header
				+ sizeof(struct ar_header);
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
	return (ptr + sizeof(struct ar_magic));
}

/*
** Get object file for fat haeder
*/
void *get_object_file(void *ptr, uint32_t offset)
{
	return (ptr + offset);
}

void *get_fat_ach(void *header, int index, bool is_64)
{
	if (is_64 == TRUE)
	{
		return ((void*)header + sizeof(struct fat_header))
					+ (index * sizeof(struct fat_arch_64));
	}
	else
	{
		return ((void*)header + sizeof(struct fat_header))
					+ (index * sizeof(struct fat_arch));
	}
}

struct load_command *get_first_load_command(void *header, bool is_64)
{
	if (is_64 == TRUE)
		return ((void*)header + sizeof(struct mach_header_64));
	else
		return ((void*)header + sizeof(struct mach_header));
}

struct load_command *get_next_load_command(struct load_command *lc)
{
	return ((void*)lc + lc->cmdsize);
}

/*
** Get the symbol table from a command and the ptr on the beginning of the
** mapped file. And return the ptr on the symbol tble (strcut nlist_64)
*/
void *get_symbol_table(struct symtab_command *sym, void *ptr)
{
	return (ptr + sym->symoff);
}

void *get_string_table(struct symtab_command *sym, void *ptr)
{
	return (ptr + sym->stroff);
}


// char	*get_symbol_string(struct nlist_64 *symbol_table, void *string_table, uint32_t num_symbol)
// {
// 	return (string_table + symbol_table[num_symbol].n_un.n_strx);
// }

char	*get_symbol_string(s_symbol_list *symbol_elem, void *string_table, bool is_64)
{
	if (is_64 == TRUE)
	{
		return (string_table + symbol_elem->symbol_64->n_un.n_strx);
	}
	else
	{
		return (string_table + symbol_elem->symbol_32->n_un.n_strx);
	}
}

/*
** Send a struct segment_command witht an index and return a struct section
*/
void *get_section_command(void *seg, uint32_t index_section, bool is_64)
{
	if (is_64 == TRUE)
	{
		return (void*)seg +
					sizeof(struct segment_command_64) +
					(index_section * sizeof(struct section_64));
	}
	else
	{
		return (void*)seg +
					sizeof(struct segment_command) +
					(index_section * sizeof(struct section));
	}
}

uint32_t get_section_type(s_section_list *section_elem, bool is_64)
{
	if (is_64 == TRUE)
		return section_elem->section_64->flags & SECTION_TYPE;
	else
		return section_elem->section_32->flags & SECTION_TYPE;
}

uint32_t get_section_attributes(s_section_list *section_elem, bool is_64)
{
	if (is_64 == TRUE)
		return section_elem->section_64->flags & SECTION_ATTRIBUTES;
	else
		return section_elem->section_32->flags & SECTION_ATTRIBUTES;
}

uint8_t get_symbol_type(uint8_t n_type)
{
	return  n_type & N_TYPE;
}
