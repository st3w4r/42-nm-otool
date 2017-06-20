#include "nm-otool.h"


void display_section_64(s_section_list *section_list)
{
	if (section_list != NULL && section_list->section_64 != NULL)
	{
		ft_putstr("Segment name: ");
		ft_putstr(section_list->section_64->segname);
		ft_putstr(" Section name: ");
		ft_putstr(section_list->section_64->sectname);
		ft_putstr("\n");
	}
}

void display_section_list_64(s_section_list *section_list)
{
	while (section_list)
	{
		display_section_64(section_list);
		section_list = section_list->next;
	}
}


void display_symbol_hexa_64(void *string_table, s_section_list *section_list, s_symbol_list *symbol_elem)
{
	uint8_t n_type;
	uint8_t type;
	uint8_t n_sect;
	// uint8_t type;
	uint16_t n_desc;
	uint64_t n_value;
	uint32_t n_strx;
	// s_section_list *section_elem;
	char *symbol_string;

	n_type = symbol_elem->symbol_64->n_type;
	n_sect = symbol_elem->symbol_64->n_sect;
	n_value = symbol_elem->symbol_64->n_value;
	n_desc = symbol_elem->symbol_64->n_desc;
	n_strx = symbol_elem->symbol_64->n_un.n_strx;
	type = get_symbol_type(n_type);
	symbol_string = get_symbol_string_64(symbol_elem, string_table);

	if ((type == N_SECT || type == N_UNDF) && ft_strcmp(symbol_string, ""))
	{
		ft_puthexa_size(n_value, sizeof(n_value) * 2); ft_putstr(" ");
		ft_puthexa_size(n_type, sizeof(n_type) * 2); ft_putstr(" ");
		ft_puthexa_size(n_sect, sizeof(n_sect) * 2); ft_putstr(" ");
		ft_puthexa_size(n_desc, sizeof(n_desc) * 2); ft_putstr(" ");
		ft_puthexa_size(n_strx, sizeof(n_strx) * 2); ft_putstr(" ");
		ft_putstr(symbol_string);
		ft_putstr("\n");
	}
}

void display_symbol_64(void *string_table, s_section_list *section_list, s_symbol_list *symbol_elem)
{
	// display_nlist_64(section_list,
	// 									symbol_elem->symbol->n_un.n_strx,
	// 									symbol_elem->symbol->n_type,
	// 									symbol_elem->symbol->n_sect,
	// 									symbol_elem->symbol->n_desc,
	// 									symbol_elem->symbol->n_value);

	uint8_t n_type;
	uint8_t n_sect;
	uint8_t type;
	uint16_t n_desc;
	uint64_t n_value;
	s_section_list *section_elem;
	char *symbol_string;

	n_type = symbol_elem->symbol_64->n_type;
	n_sect = symbol_elem->symbol_64->n_sect;
	n_value = symbol_elem->symbol_64->n_value;
	n_desc = symbol_elem->symbol_64->n_desc;
	type = get_symbol_type(n_type);
	symbol_string = get_symbol_string_64(symbol_elem, string_table);
	section_elem = get_section_index(section_list, n_sect);


	// if ((type != N_SECT && type != N_UNDF) || ft_strcmp(symbol_string, "") == 0)
	// 	return ;
	uint32_t secattr = get_section_attributes_64(section_elem);

	// ft_putnbr(section_elem->section->flags);
	// printf("\nFlags: %u\n", section_elem->section->flags & SECTION_ATTRIBUTES);

	// ft_putstr(" Section attribute: ");
	// ft_putnbr(section_elem->section->flags & 0x000000ff);
	// ft_putstr(" ");
	// if ((section_elem->section->flags & SECTION_TYPE)== S_ATTR_DEBUG)
	// 	ft_putstr("S_ATTR_DEBUG");

	if (n_value)
		ft_puthexa_size(n_value, sizeof(n_value) * 2);
	else
		ft_putstr("                ");
	ft_putstr(" ");

	if (type == N_UNDF)
		ft_putstr("(undefined) ");
	else if (type == N_ABS)
		ft_putstr("(absolute) ");
	else if (type == N_SECT)
		ft_putstr("");
	else if (type == N_PBUD)
		ft_putstr("N_PBUD ");
	else if (type == N_INDR)
		ft_putstr("(indirect) ");
	else if (type == N_UNDF && n_type == N_EXT && n_value)
		ft_putstr("(common) ");


	if (n_sect == NO_SECT)
	{
		ft_putstr("");
		// ft_putstr("NO_SECT ");
	}
	else if (n_type == MAX_SECT)
		ft_putstr("MAX_SECT ");
	else
	{

		// ft_putstr("Section n: ");
		// ft_putnbr(n_sect);
		ft_putstr("(");
		ft_putstr(section_elem->section_64->segname);
		ft_putstr(",");
		ft_putstr(section_elem->section_64->sectname);
		ft_putstr(") ");
	}




	uint16_t desc_reference;
	desc_reference = n_desc & REFERENCE_TYPE;
	// if (n_desc == REFERENCE_FLAG_UNDEFINED_NON_LAZY)
		// ft_putstr("REFERENCE_FLAG_UNDEFINED_NON_LAZY ");
	if (n_desc == REFERENCE_FLAG_UNDEFINED_LAZY)
		ft_putstr("REFERENCE_FLAG_UNDEFINED_LAZY ");
	else if (n_desc == REFERENCE_FLAG_DEFINED)
		ft_putstr("REFERENCE_FLAG_DEFINED ");
	else if (n_desc == REFERENCE_FLAG_PRIVATE_DEFINED)
		ft_putstr("REFERENCE_FLAG_PRIVATE_DEFINED ");
	else if (n_desc == REFERENCE_FLAG_PRIVATE_UNDEFINED_NON_LAZY)
		ft_putstr("REFERENCE_FLAG_PRIVATE_UNDEFINED_NON_LAZY ");
	else if (n_desc == REFERENCE_FLAG_PRIVATE_UNDEFINED_LAZY)
		ft_putstr("REFERENCE_FLAG_PRIVATE_UNDEFINED_LAZY ");
	else if (n_desc == REFERENCED_DYNAMICALLY)
		ft_putstr("[referenced dynamically] ");

	// if ((n_type & N_TYPE) == N_TYPE)
	// 	ft_putstr("N_TYPE ");
	if ((n_type & N_STAB) == N_STAB)
		ft_putstr("N_STAB ");

	if ((n_type & N_PEXT) == N_PEXT)
		ft_putstr("non-external ");
	if ((n_type & N_EXT) == N_EXT)
		ft_putstr("external ");

	ft_putstr(symbol_string);

	ft_putstr("\n");

}

void display_symbol_list_64(void *string_table, s_section_list *section_list, s_symbol_list *symbol_list)
{
	while (symbol_list)
	{
		display_symbol_64(string_table, section_list, symbol_list);
		// display_symbol_hexa(string_table, section_list, symbol_list);
		// display_section_command(section_list);
		symbol_list = symbol_list->next;
	}
}

void display_format_64(s_format *format)
{
		display_mach_header_64(format->ptr_header);
		// display_lc_list(format.lc_list);
		display_section_list_64(format->section_list);
		// display_section(get_section_index(format->section_list, 8));
		display_symbol_list_64(format->string_table, format->section_list, format->symbol_list);
}


// void	display_symbol(char *str)
// {
// 	ft_putstr(str);
// }


void	display_mach_header_64(struct mach_header_64 *header)
{
	ft_putstr("magic: ");				ft_puthexa(header->magic);			ft_putstr("\n");
	ft_putstr("cputype: ");			ft_puthexa(header->cputype);		ft_putstr("\n");
	ft_putstr("cpusubtype: ");	ft_puthexa(header->cpusubtype);	ft_putstr("\n");
	ft_putstr("filetype: ");		ft_puthexa(header->filetype);		ft_putstr("\n");
	ft_putstr("ncmds: ");				ft_putnbr(header->ncmds);			ft_putstr("\n");
	ft_putstr("sizeofcmds: ");	ft_putnbr(header->sizeofcmds);	ft_putstr("\n");
	ft_putstr("flags: ");				ft_puthexa(header->flags);			ft_putstr("\n");
	ft_putstr("reserved: ");		ft_puthexa(header->reserved);		ft_putstr("\n");
	ft_putstr("\n");
}


void display_section_command_64(s_section_list *section_elem)
{
	// ft_putstr("Section: Segment name: ");
	// ft_putstr(section_elem->section->segname);
	// ft_putstr(" Section name: ");
	// ft_putstr(section_elem->section->sectname);

	uint32_t sectype = get_section_type_64(section_elem);

	ft_putstr(" Section type: ");
	if (sectype == S_REGULAR)
		ft_putstr("S_REGULAR");
	 if (sectype == S_ZEROFILL)
		ft_putstr("S_ZEROFILL");
	 if (sectype == S_CSTRING_LITERALS)
		ft_putstr("S_CSTRING_LITERALS");
	 if (sectype == S_4BYTE_LITERALS)
		ft_putstr("S_4BYTE_LITERALS");
	 if (sectype == S_8BYTE_LITERALS)
		ft_putstr("S_8BYTE_LITERALS");
	 if (sectype == S_LITERAL_POINTERS)
		ft_putstr("S_LITERAL_POINTERS");
	 if (sectype == S_NON_LAZY_SYMBOL_POINTERS)
		ft_putstr("S_NON_LAZY_SYMBOL_POINTERS");
	 if (sectype == S_LAZY_SYMBOL_POINTERS)
		ft_putstr("S_LAZY_SYMBOL_POINTERS");
	 if (sectype == S_SYMBOL_STUBS)
		ft_putstr("S_SYMBOL_STUBS");
	 if (sectype == S_MOD_INIT_FUNC_POINTERS)
		ft_putstr("S_MOD_INIT_FUNC_POINTERS");
	 if (sectype == S_MOD_TERM_FUNC_POINTERS)
		ft_putstr("S_MOD_TERM_FUNC_POINTERS");
	 if (sectype == S_COALESCED)
		ft_putstr("S_COALESCED");
	 if (sectype == S_GB_ZEROFILL)
		ft_putstr("S_GB_ZEROFILL");
	 if (sectype == S_INTERPOSING)
		ft_putstr("S_INTERPOSING");
	 if (sectype == S_16BYTE_LITERALS)
		ft_putstr("S_16BYTE_LITERALS");
	 if (sectype == S_DTRACE_DOF)
		ft_putstr("S_DTRACE_DOF");
	 if (sectype == S_LAZY_DYLIB_SYMBOL_POINTERS)
		ft_putstr("S_LAZY_DYLIB_SYMBOL_POINTERS");
	 if (sectype == S_THREAD_LOCAL_REGULAR)
		ft_putstr("S_THREAD_LOCAL_REGULAR");
	 if (sectype == S_THREAD_LOCAL_ZEROFILL)
		ft_putstr("S_THREAD_LOCAL_ZEROFILL");
	 if (sectype == S_THREAD_LOCAL_VARIABLES)
		ft_putstr("S_THREAD_LOCAL_VARIABLES");
	 if (sectype == S_THREAD_LOCAL_VARIABLE_POINTERS)
		ft_putstr("S_THREAD_LOCAL_VARIABLE_POINTERS");
	 if (sectype == S_THREAD_LOCAL_INIT_FUNCTION_POINTERS)
		ft_putstr("S_THREAD_LOCAL_INIT_FUNCTION_POINTERS");
	// else
	// 	ft_putstr("UNKNOWN");


	uint32_t secattr = get_section_attributes_64(section_elem);
	ft_putstr(" Section attribute: ");
	if (secattr == SECTION_ATTRIBUTES_USR)
		ft_putstr("SECTION_ATTRIBUTES_USR");
	if (secattr == S_ATTR_PURE_INSTRUCTIONS)
		ft_putstr("S_ATTR_PURE_INSTRUCTIONS");
	if (secattr == S_ATTR_NO_TOC)
		ft_putstr("S_ATTR_NO_TOC");
	if (secattr == S_ATTR_STRIP_STATIC_SYMS)
		ft_putstr("S_ATTR_STRIP_STATIC_SYMS");
	if (secattr == S_ATTR_NO_DEAD_STRIP)
		ft_putstr("S_ATTR_NO_DEAD_STRIP");
	if (secattr == S_ATTR_LIVE_SUPPORT)
		ft_putstr("S_ATTR_LIVE_SUPPORT");
	if (secattr == S_ATTR_SELF_MODIFYING_CODE)
		ft_putstr("S_ATTR_SELF_MODIFYING_CODE");
	if (secattr == S_ATTR_DEBUG)
		ft_putstr("S_ATTR_DEBUG");
	if (secattr == SECTION_ATTRIBUTES_SYS)
		ft_putstr("SECTION_ATTRIBUTES_SYS");
	if (secattr == S_ATTR_SOME_INSTRUCTIONS)
		ft_putstr("S_ATTR_SOME_INSTRUCTIONS");
	if (secattr == S_ATTR_EXT_RELOC)
		ft_putstr("S_ATTR_EXT_RELOC");
	if (secattr == S_ATTR_LOC_RELOC)
		ft_putstr("S_ATTR_LOC_RELOC");
	// else
	// 	ft_putstr("UNKNOWN");
	ft_putstr("\n");
}


// void display_nlist_64(s_section_list *section_list,
// 	uint32_t n_strx, uint8_t n_type, uint8_t n_sect,
// 	uint16_t n_desc, uint64_t n_value)
// {
// 	// n_type
// 	if (n_type == N_STAB)
// 		ft_putstr("N_STAB ");
// 	else if (n_type == N_PEXT)
// 		ft_putstr("N_PEXT ");
// 	else if (n_type == N_TYPE)
// 		ft_putstr("N_TYPE ");
// 	else if (n_type == N_EXT)
// 		ft_putstr("N_EXT ");
//
// 	uint8_t type = get_symbol_type(n_type);
//
// 	if (type == N_UNDF)
// 		ft_putstr("N_UNDF ");
// 	else if (type == N_ABS)
// 		ft_putstr("N_ABS ");
// 	else if (type == N_SECT)
// 		ft_putstr("N_SECT ");
// 	else if (type == N_PBUD)
// 		ft_putstr("N_PBUD ");
// 	else if (type == N_INDR)
// 		ft_putstr("N_INDR ");
//
//
//
// 	// n_sect
// 	if (n_sect == NO_SECT)
// 		ft_putstr("NO_SECT ");
// 	else if (n_type == MAX_SECT)
// 		ft_putstr("MAX_SECT ");
// 	else {
// 		s_section_list *section_elem = get_section_index(section_list, n_sect);
//
// 		ft_putstr("Section n: ");
// 		ft_putnbr(n_sect);
// 		ft_putstr(" (");
// 		ft_putstr(section_elem->section->segname);
// 		ft_putstr(",");
// 		ft_putstr(section_elem->section->sectname);
// 		ft_putstr(") ");
// 	}
//
//
// 	// n_desc
// 	ft_putstr(" ndesc: ");
// 	if (n_desc == N_GSYM)
// 		ft_putstr("N_GSYM");
// 	else if (n_desc == N_FNAME)
// 		ft_putstr("N_FNAME");
// 	else if (n_desc == N_FUN)
// 		ft_putstr("N_FUN");
// 	else if (n_desc == N_STSYM)
// 		ft_putstr("N_STSYM");
// 	else if (n_desc == N_LCSYM)
// 		ft_putstr("N_LCSYM");
// 	else if (n_desc == N_BNSYM)
// 		ft_putstr("N_BNSYM");
// 	else if (n_desc == N_AST)
// 		ft_putstr("N_AST");
// 	else if (n_desc == N_OPT)
// 		ft_putstr("N_OPT");
// 	else if (n_desc == N_RSYM)
// 		ft_putstr("N_RSYM");
// 	else if (n_desc == N_SLINE)
// 		ft_putstr("N_SLINE");
// 	else if (n_desc == N_ENSYM)
// 		ft_putstr("N_ENSYM");
// 	else if (n_desc == N_SSYM)
// 		ft_putstr("N_SSYM");
// 	else if (n_desc == N_SO)
// 		ft_putstr("N_SO");
// 	else if (n_desc == N_OSO)
// 		ft_putstr("N_OSO");
// 	else if (n_desc == N_LSYM)
// 		ft_putstr("N_LSYM");
// 	else if (n_desc == N_BINCL)
// 		ft_putstr("N_BINCL");
// 	else if (n_desc == N_SOL)
// 		ft_putstr("N_SOL");
// 	else if (n_desc == N_PARAMS)
// 		ft_putstr("N_PARAMS");
// 	else if (n_desc == N_VERSION)
// 		ft_putstr("N_VERSION");
// 	else if (n_desc == N_OLEVEL)
// 		ft_putstr("N_OLEVEL");
// 	else if (n_desc == N_PSYM)
// 		ft_putstr("N_PSYM");
// 	else if (n_desc == N_EINCL)
// 		ft_putstr("N_EINCL");
// 	else if (n_desc == N_ENTRY)
// 		ft_putstr("N_ENTRY");
// 	else if (n_desc == N_LBRAC)
// 		ft_putstr("N_LBRAC");
// 	else if (n_desc == N_EXCL)
// 		ft_putstr("N_EXCL");
// 	else if (n_desc == N_RBRAC)
// 		ft_putstr("N_RBRAC");
// 	else if (n_desc == N_BCOMM)
// 		ft_putstr("N_BCOMM");
// 	else if (n_desc == N_ECOMM)
// 		ft_putstr("N_ECOMM");
// 	else if (n_desc == N_ECOML)
// 		ft_putstr("N_ECOML");
// 	else if (n_desc == N_LENG)
// 		ft_putstr("N_LENG");
// 	else if (n_desc == N_PC)
// 		ft_putstr("N_PC");
// 	else
// 		ft_putstr("UNKNOWN");
// 	ft_putstr(" ");
//
// 	// SET_COMM_ALIGN(n_desc,1);
// 	// uint16_t desc_reference;
// 	// desc_reference = n_desc & REFERENCE_TYPE;
// 	// if (n_desc == REFERENCE_FLAG_UNDEFINED_NON_LAZY)
// 	// 	ft_putstr("REFERENCE_FLAG_UNDEFINED_NON_LAZY ");
// 	// else if (n_desc == REFERENCE_FLAG_UNDEFINED_LAZY)
// 	// 	ft_putstr("REFERENCE_FLAG_UNDEFINED_LAZY ");
// 	// else if (n_desc == REFERENCE_FLAG_DEFINED)
// 	// 	ft_putstr("REFERENCE_FLAG_DEFINED ");
// 	// else if (n_desc == REFERENCE_FLAG_PRIVATE_DEFINED)
// 	// 	ft_putstr("REFERENCE_FLAG_PRIVATE_DEFINED ");
// 	// else if (n_desc == REFERENCE_FLAG_PRIVATE_UNDEFINED_NON_LAZY)
// 	// 	ft_putstr("REFERENCE_FLAG_PRIVATE_UNDEFINED_NON_LAZY ");
// 	// else if (n_desc == REFERENCE_FLAG_PRIVATE_UNDEFINED_LAZY)
// 	// 	ft_putstr("REFERENCE_FLAG_PRIVATE_UNDEFINED_LAZY ");
//
//
// 	ft_puthexa_size(n_value);
// 	ft_putstr(" ");
// 	ft_puthexa(n_type);
// 	ft_putstr(" ");
// 	ft_puthexa(n_sect);
// 	ft_putstr(" ");
// 	ft_puthexa(n_desc);
// 	ft_putstr(" ");
// 	ft_puthexa_size(n_strx);
// 	ft_putstr(" ");
// 	ft_putstr("\n");
// }
