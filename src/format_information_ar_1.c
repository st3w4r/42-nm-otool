#include "nm-otool.h"

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
