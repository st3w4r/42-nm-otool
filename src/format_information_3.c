#include "nm-otool.h"

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
