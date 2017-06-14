#include "nm-otool.h"

void handle_nlist_64(uint32_t n_strx, uint8_t n_type, uint8_t n_sect,
	uint16_t n_desc, uint64_t n_value)
{
	// n_type
	if (n_type == N_STAB)
		ft_putstr("N_STAB ");
	else if (n_type == N_PEXT)
		ft_putstr("N_PEXT ");
	else if (n_type == N_TYPE)
		ft_putstr("N_TYPE ");
	else if (n_type == N_EXT)
		ft_putstr("N_EXT ");

	uint8_t type = get_symbol_type(n_type);

	if (type == N_UNDF)
		ft_putstr("N_UNDF ");
	else if (type == N_ABS)
		ft_putstr("N_ABS ");
	else if (type == N_SECT)
		ft_putstr("N_SECT ");
	else if (type == N_PBUD)
		ft_putstr("N_PBUD ");
	else if (type == N_INDR)
		ft_putstr("N_INDR ");



	// n_sect
	if (n_sect == NO_SECT)
		ft_putstr("NO_SECT ");
	else if (n_type == MAX_SECT)
		ft_putstr("MAX_SECT ");
	else {
		ft_putstr("Section n: ");
		ft_putnbr(n_sect);
		ft_putstr(" ");
	}

	// n_desc
	ft_putstr(" ndesc: ");
	if (n_desc == N_GSYM)
		ft_putstr("N_GSYM");
	else if (n_desc == N_FNAME)
		ft_putstr("N_FNAME");
	else if (n_desc == N_FUN)
		ft_putstr("N_FUN");
	else if (n_desc == N_STSYM)
		ft_putstr("N_STSYM");
	else if (n_desc == N_LCSYM)
		ft_putstr("N_LCSYM");
	else if (n_desc == N_BNSYM)
		ft_putstr("N_BNSYM");
	else if (n_desc == N_AST)
		ft_putstr("N_AST");
	else if (n_desc == N_OPT)
		ft_putstr("N_OPT");
	else if (n_desc == N_RSYM)
		ft_putstr("N_RSYM");
	else if (n_desc == N_SLINE)
		ft_putstr("N_SLINE");
	else if (n_desc == N_ENSYM)
		ft_putstr("N_ENSYM");
	else if (n_desc == N_SSYM)
		ft_putstr("N_SSYM");
	else if (n_desc == N_SO)
		ft_putstr("N_SO");
	else if (n_desc == N_OSO)
		ft_putstr("N_OSO");
	else if (n_desc == N_LSYM)
		ft_putstr("N_LSYM");
	else if (n_desc == N_BINCL)
		ft_putstr("N_BINCL");
	else if (n_desc == N_SOL)
		ft_putstr("N_SOL");
	else if (n_desc == N_PARAMS)
		ft_putstr("N_PARAMS");
	else if (n_desc == N_VERSION)
		ft_putstr("N_VERSION");
	else if (n_desc == N_OLEVEL)
		ft_putstr("N_OLEVEL");
	else if (n_desc == N_PSYM)
		ft_putstr("N_PSYM");
	else if (n_desc == N_EINCL)
		ft_putstr("N_EINCL");
	else if (n_desc == N_ENTRY)
		ft_putstr("N_ENTRY");
	else if (n_desc == N_LBRAC)
		ft_putstr("N_LBRAC");
	else if (n_desc == N_EXCL)
		ft_putstr("N_EXCL");
	else if (n_desc == N_RBRAC)
		ft_putstr("N_RBRAC");
	else if (n_desc == N_BCOMM)
		ft_putstr("N_BCOMM");
	else if (n_desc == N_ECOMM)
		ft_putstr("N_ECOMM");
	else if (n_desc == N_ECOML)
		ft_putstr("N_ECOML");
	else if (n_desc == N_LENG)
		ft_putstr("N_LENG");
	else if (n_desc == N_PC)
		ft_putstr("N_PC");
	else
		ft_putstr("UNKNOWN");
	ft_putstr(" ");

	// SET_COMM_ALIGN(n_desc,1);
	// uint16_t desc_reference;
	// desc_reference = n_desc & REFERENCE_TYPE;
	// if (n_desc == REFERENCE_FLAG_UNDEFINED_NON_LAZY)
	// 	ft_putstr("REFERENCE_FLAG_UNDEFINED_NON_LAZY ");
	// else if (n_desc == REFERENCE_FLAG_UNDEFINED_LAZY)
	// 	ft_putstr("REFERENCE_FLAG_UNDEFINED_LAZY ");
	// else if (n_desc == REFERENCE_FLAG_DEFINED)
	// 	ft_putstr("REFERENCE_FLAG_DEFINED ");
	// else if (n_desc == REFERENCE_FLAG_PRIVATE_DEFINED)
	// 	ft_putstr("REFERENCE_FLAG_PRIVATE_DEFINED ");
	// else if (n_desc == REFERENCE_FLAG_PRIVATE_UNDEFINED_NON_LAZY)
	// 	ft_putstr("REFERENCE_FLAG_PRIVATE_UNDEFINED_NON_LAZY ");
	// else if (n_desc == REFERENCE_FLAG_PRIVATE_UNDEFINED_LAZY)
	// 	ft_putstr("REFERENCE_FLAG_PRIVATE_UNDEFINED_LAZY ");


	ft_puthexa_size(n_value);
	ft_putstr(" ");
	ft_puthexa(n_type);
	ft_putstr(" ");
	ft_puthexa(n_sect);
	ft_putstr(" ");
	ft_puthexa(n_desc);
	ft_putstr(" ");
	ft_puthexa_size(n_strx);
	ft_putstr(" ");
}

void handle_file_type(uint32_t filetype)
{
	ft_putstr("File type: ");
	if (filetype == MH_OBJECT)
		ft_putstr("MH_OBJECT");
	else if (filetype == MH_EXECUTE)
		ft_putstr("MH_EXECUTE");
	else if (filetype == MH_FVMLIB)
		ft_putstr("MH_FVMLIB");
	else if (filetype == MH_CORE)
		ft_putstr("MH_CORE");
	else if (filetype == MH_PRELOAD)
		ft_putstr("MH_PRELOAD");
	else if (filetype == MH_DYLIB)
		ft_putstr("MH_DYLIB");
	else if (filetype == MH_DYLINKER)
		ft_putstr("MH_DYLINKER");
	else if (filetype == MH_BUNDLE)
		ft_putstr("MH_BUNDLE");
	else if (filetype == MH_DYLIB_STUB)
		ft_putstr("MH_DYLIB_STUB");
	else if (filetype == MH_DSYM)
		ft_putstr("MH_DSYM");
	else if (filetype == MH_KEXT_BUNDLE)
		ft_putstr("MH_KEXT_BUNDLE");
	else if (filetype == MH_NOUNDEFS)
		ft_putstr("MH_NOUNDEFS");
	else if (filetype == MH_INCRLINK)
		ft_putstr("MH_INCRLINK");
	else if (filetype == MH_DYLDLINK)
		ft_putstr("MH_DYLDLINK");
	else if (filetype == MH_BINDATLOAD)
		ft_putstr("MH_BINDATLOAD");
	else if (filetype == MH_PREBOUND)
		ft_putstr("MH_PREBOUND");
	else if (filetype == MH_SPLIT_SEGS)
		ft_putstr("MH_SPLIT_SEGS");
	else if (filetype == MH_LAZY_INIT)
		ft_putstr("MH_LAZY_INIT");
	else if (filetype == MH_TWOLEVEL)
		ft_putstr("MH_TWOLEVEL");
	else if (filetype == MH_FORCE_FLAT)
		ft_putstr("MH_FORCE_FLAT");
	else if (filetype == MH_NOMULTIDEFS)
		ft_putstr("MH_NOMULTIDEFS");
	else if (filetype == MH_NOFIXPREBINDING)
		ft_putstr("MH_NOFIXPREBINDING");
	else if (filetype == MH_PREBINDABLE)
		ft_putstr("MH_PREBINDABLE");
	else if (filetype == MH_ALLMODSBOUND)
		ft_putstr("MH_ALLMODSBOUND");
	else if (filetype == MH_SUBSECTIONS_VIA_SYMBOLS)
		ft_putstr("MH_SUBSECTIONS_VIA_SYMBOLS");
	else if (filetype == MH_CANONICAL)
		ft_putstr("MH_CANONICAL");
	else if (filetype == MH_WEAK_DEFINES)
		ft_putstr("MH_WEAK_DEFINES");
	else if (filetype == MH_BINDS_TO_WEAK)
		ft_putstr("MH_BINDS_TO_WEAK");
	else if (filetype == MH_ALLOW_STACK_EXECUTION)
		ft_putstr("MH_ALLOW_STACK_EXECUTION");
	else if (filetype == MH_ROOT_SAFE)
		ft_putstr("MH_ROOT_SAFE");
	else if (filetype == MH_SETUID_SAFE)
		ft_putstr("MH_SETUID_SAFE");
	else if (filetype == MH_NO_REEXPORTED_DYLIBS)
		ft_putstr("MH_NO_REEXPORTED_DYLIBS");
	else if (filetype == MH_PIE)
		ft_putstr("MH_PIE");
	else if (filetype == MH_DEAD_STRIPPABLE_DYLIB)
		ft_putstr("MH_DEAD_STRIPPABLE_DYLIB");
	else if (filetype == MH_HAS_TLV_DESCRIPTORS)
		ft_putstr("MH_HAS_TLV_DESCRIPTORS");
	else if (filetype == MH_NO_HEAP_EXECUTION)
		ft_putstr("MH_NO_HEAP_EXECUTION");
	else if (filetype == MH_APP_EXTENSION_SAFE)
		ft_putstr("MH_APP_EXTENSION_SAFE");
	else
		ft_putstr("UNKNOWN");
	ft_putstr("\n");
}

void handle_load_command_type(uint32_t cmd)
{
	ft_putstr("Command type: ");
	if (cmd == LC_REQ_DYLD)
		ft_putstr("LC_REQ_DYLD");
	else if (cmd == LC_SEGMENT)
		ft_putstr("LC_SEGMENT");
	else if(cmd == LC_SYMTAB)
		ft_putstr("LC_SYMTAB");
	else if(cmd == LC_SYMSEG)
		ft_putstr("LC_SYMSEG");
	else if(cmd == LC_THREAD)
		ft_putstr("LC_THREAD");
	else if(cmd == LC_UNIXTHREAD)
		ft_putstr("LC_UNIXTHREAD");
	else if(cmd == LC_LOADFVMLIB)
		ft_putstr("LC_LOADFVMLIB");
	else if(cmd == LC_IDFVMLIB)
		ft_putstr("LC_IDFVMLIB");
	else if(cmd == LC_IDENT)
		ft_putstr("LC_IDENT");
	else if(cmd == LC_FVMFILE)
		ft_putstr("LC_FVMFILE");
	else if(cmd == LC_PREPAGE)
		ft_putstr("LC_PREPAGE");
	else if(cmd == LC_DYSYMTAB)
		ft_putstr("LC_DYSYMTAB");
	else if(cmd == LC_LOAD_DYLIB)
		ft_putstr("LC_LOAD_DYLIB");
	else if(cmd == LC_ID_DYLIB)
		ft_putstr("LC_ID_DYLIB");
	else if(cmd == LC_LOAD_DYLINKER)
		ft_putstr("LC_LOAD_DYLINKER");
	else if(cmd == LC_ID_DYLINKER)
		ft_putstr("LC_ID_DYLINKER");
	else if(cmd == LC_PREBOUND_DYLIB)
		ft_putstr("LC_PREBOUND_DYLIB");
	else if(cmd == LC_ROUTINES)
		ft_putstr("LC_ROUTINES");
	else if(cmd == LC_SUB_FRAMEWORK)
		ft_putstr("LC_SUB_FRAMEWORK");
	else if(cmd == LC_SUB_UMBRELLA)
		ft_putstr("LC_SUB_UMBRELLA");
	else if(cmd == LC_SUB_CLIENT)
		ft_putstr("LC_SUB_CLIENT");
	else if(cmd == LC_SUB_LIBRARY)
		ft_putstr("LC_SUB_LIBRARY");
	else if(cmd == LC_TWOLEVEL_HINTS)
		ft_putstr("LC_TWOLEVEL_HINTS");
	else if(cmd == LC_PREBIND_CKSUM)
		ft_putstr("LC_PREBIND_CKSUM");
	else if (cmd == LC_LOAD_WEAK_DYLIB)
		ft_putstr("LC_LOAD_WEAK_DYLIB");
	else if (cmd == LC_SEGMENT_64)
		ft_putstr("LC_SEGMENT_64");
	else if (cmd == LC_ROUTINES_64)
		ft_putstr("LC_ROUTINES_64");
	else if (cmd == LC_UUID)
		ft_putstr("LC_UUID");
	else if (cmd == LC_RPATH)
		ft_putstr("LC_RPATH");
	else if (cmd == LC_CODE_SIGNATURE)
		ft_putstr("LC_CODE_SIGNATURE");
	else if (cmd == LC_SEGMENT_SPLIT_INFO)
		ft_putstr("LC_SEGMENT_SPLIT_INFO");
	else if (cmd == LC_REEXPORT_DYLIB)
		ft_putstr("LC_REEXPORT_DYLIB");
	else if (cmd == LC_LAZY_LOAD_DYLIB)
		ft_putstr("LC_LAZY_LOAD_DYLIB");
	else if (cmd == LC_ENCRYPTION_INFO)
		ft_putstr("LC_ENCRYPTION_INFO");
	else if (cmd == LC_DYLD_INFO)
		ft_putstr("LC_DYLD_INFO");
	else if (cmd == LC_DYLD_INFO_ONLY)
		ft_putstr("LC_DYLD_INFO_ONLY");
	else if (cmd == LC_LOAD_UPWARD_DYLIB)
		ft_putstr("LC_LOAD_UPWARD_DYLIB");
	else if (cmd == LC_VERSION_MIN_MACOSX)
		ft_putstr("LC_VERSION_MIN_MACOSX");
	else if (cmd == LC_VERSION_MIN_IPHONEOS)
		ft_putstr("LC_VERSION_MIN_IPHONEOS");
	else if (cmd == LC_FUNCTION_STARTS)
		ft_putstr("LC_FUNCTION_STARTS");
	else if (cmd == LC_DYLD_ENVIRONMENT)
		ft_putstr("LC_DYLD_ENVIRONMENT");
	else if (cmd == LC_MAIN)
		ft_putstr("LC_MAIN");
	else if (cmd == LC_DATA_IN_CODE)
		ft_putstr("LC_DATA_IN_CODE");
	else if (cmd == LC_SOURCE_VERSION)
		ft_putstr("LC_SOURCE_VERSION");
	else if (cmd == LC_DYLIB_CODE_SIGN_DRS)
		ft_putstr("LC_DYLIB_CODE_SIGN_DRS");
	else if (cmd == LC_ENCRYPTION_INFO_64)
		ft_putstr("LC_ENCRYPTION_INFO_64");
	else if (cmd == LC_LINKER_OPTION)
		ft_putstr("LC_LINKER_OPTION");
	else if (cmd == LC_LINKER_OPTIMIZATION_HINT)
		ft_putstr("LC_LINKER_OPTIMIZATION_HINT");
	else if (cmd == LC_VERSION_MIN_TVOS)
		ft_putstr("LC_VERSION_MIN_TVOS");
	else if (cmd == LC_VERSION_MIN_WATCHOS)
		ft_putstr("LC_VERSION_MIN_WATCHOS");
	else
		ft_putstr("UNKNOWN");
	ft_putstr("\n");
}

void handle_cpu_type(cpu_type_t cputype, cpu_subtype_t cpusubtype)
{
	cpu_type_t type;
	cpu_subtype_t subtype;

	type = cputype;// & CPU_ARCH_MASK;

	ft_putstr("CPU Type: ");
	if (type == CPU_TYPE_ANY)
		ft_putstr("CPU_TYPE_ANY");
	else if (type == CPU_TYPE_VAX)
		ft_putstr("CPU_TYPE_VAX");
	else if (type == CPU_TYPE_MC680x0)
		ft_putstr("CPU_TYPE_MC680x0");
	else if (type == CPU_TYPE_X86)
		ft_putstr("CPU_TYPE_X86");
	else if (type == CPU_TYPE_I386)
		ft_putstr("CPU_TYPE_I386");
	else if (type == CPU_TYPE_X86_64)
		ft_putstr("CPU_TYPE_X86_64");
	else if (type == CPU_TYPE_MC98000)
		ft_putstr("CPU_TYPE_MC98000");
	else if (type == CPU_TYPE_HPPA)
		ft_putstr("CPU_TYPE_HPPA");
	else if (type == CPU_TYPE_ARM)
		ft_putstr("CPU_TYPE_ARM");
	else if (type == CPU_TYPE_ARM64)
		ft_putstr("CPU_TYPE_ARM64");
	else if (type == CPU_TYPE_MC88000)
		ft_putstr("CPU_TYPE_MC88000");
	else if (type == CPU_TYPE_SPARC)
		ft_putstr("CPU_TYPE_SPARC");
	else if (type == CPU_TYPE_I860)
		ft_putstr("CPU_TYPE_I860");
	else if (type == CPU_TYPE_POWERPC)
		ft_putstr("CPU_TYPE_POWERPC");
	else if (type == CPU_TYPE_POWERPC64)
		ft_putstr("CPU_TYPE_POWERPC64");
	else
		ft_putstr("UNKNOWN");
	ft_putstr("\n");

	subtype = cpusubtype;// & CPU_SUBTYPE_MASK;

	ft_putstr("CPU Subtype: ");
	if (subtype == CPU_SUBTYPE_MULTIPLE)
		ft_putstr("CPU_SUBTYPE_MULTIPLE");
	else if (subtype == CPU_SUBTYPE_LITTLE_ENDIAN)
		ft_putstr("CPU_SUBTYPE_LITTLE_ENDIAN");
	else if (subtype == CPU_SUBTYPE_BIG_ENDIAN)
		ft_putstr("CPU_SUBTYPE_BIG_ENDIAN");
	else
		ft_putstr("UNKNOWN");
	ft_putstr("\n");

}

void handle_symtab_command(struct symtab_command *sym, void *ptr)
{
	uint32_t				i;
	char						*str;
	void						*string_table;
	struct nlist_64	*symbol_table;

	symbol_table = get_symbol_table(sym, ptr);
	string_table = get_string_table(sym, ptr);

	i = 0;
	while (i < sym->nsyms)
	{
		str = get_symbol_string(symbol_table, string_table, i);
		handle_nlist_64(symbol_table[i].n_un.n_strx, symbol_table[i].n_type,
			symbol_table[i].n_sect, symbol_table[i].n_desc, symbol_table[i].n_value);
		ft_putstr(str);
		ft_putstr("\n");

		i++;
	}
}


void handle_section_command(struct section_64 *sec, void *ptr)
{
	ft_putstr("Section: Segment name: ");
	ft_putstr(sec->segname);
	ft_putstr(" Section name: ");
	ft_putstr(sec->sectname);

	uint64_t sectype = get_section_type(sec);

	ft_putstr(" Section type: ");
	if (sectype == S_REGULAR)
		ft_putstr("S_REGULAR");
	else if (sectype == S_ZEROFILL)
		ft_putstr("S_ZEROFILL");
	else if (sectype == S_CSTRING_LITERALS)
		ft_putstr("S_CSTRING_LITERALS");
	else if (sectype == S_4BYTE_LITERALS)
		ft_putstr("S_4BYTE_LITERALS");
	else if (sectype == S_8BYTE_LITERALS)
		ft_putstr("S_8BYTE_LITERALS");
	else if (sectype == S_LITERAL_POINTERS)
		ft_putstr("S_LITERAL_POINTERS");
	else if (sectype == S_NON_LAZY_SYMBOL_POINTERS)
		ft_putstr("S_NON_LAZY_SYMBOL_POINTERS");
	else if (sectype == S_LAZY_SYMBOL_POINTERS)
		ft_putstr("S_LAZY_SYMBOL_POINTERS");
	else if (sectype == S_SYMBOL_STUBS)
		ft_putstr("S_SYMBOL_STUBS");
	else if (sectype == S_MOD_INIT_FUNC_POINTERS)
		ft_putstr("S_MOD_INIT_FUNC_POINTERS");
	else if (sectype == S_MOD_TERM_FUNC_POINTERS)
		ft_putstr("S_MOD_TERM_FUNC_POINTERS");
	else if (sectype == S_COALESCED)
		ft_putstr("S_COALESCED");
	else if (sectype == S_GB_ZEROFILL)
		ft_putstr("S_GB_ZEROFILL");
	else if (sectype == S_INTERPOSING)
		ft_putstr("S_INTERPOSING");
	else if (sectype == S_16BYTE_LITERALS)
		ft_putstr("S_16BYTE_LITERALS");
	else if (sectype == S_DTRACE_DOF)
		ft_putstr("S_DTRACE_DOF");
	else if (sectype == S_LAZY_DYLIB_SYMBOL_POINTERS)
		ft_putstr("S_LAZY_DYLIB_SYMBOL_POINTERS");
	else if (sectype == S_THREAD_LOCAL_REGULAR)
		ft_putstr("S_THREAD_LOCAL_REGULAR");
	else if (sectype == S_THREAD_LOCAL_ZEROFILL)
		ft_putstr("S_THREAD_LOCAL_ZEROFILL");
	else if (sectype == S_THREAD_LOCAL_VARIABLES)
		ft_putstr("S_THREAD_LOCAL_VARIABLES");
	else if (sectype == S_THREAD_LOCAL_VARIABLE_POINTERS)
		ft_putstr("S_THREAD_LOCAL_VARIABLE_POINTERS");
	else if (sectype == S_THREAD_LOCAL_INIT_FUNCTION_POINTERS)
		ft_putstr("S_THREAD_LOCAL_INIT_FUNCTION_POINTERS");
	else
		ft_putstr("UNKNOWN");


	uint64_t secattr = get_section_attributes(sec);
	ft_putstr(" Section attribute: ");
	if (secattr == SECTION_ATTRIBUTES_USR)
		ft_putstr("SECTION_ATTRIBUTES_USR");
	else if (secattr == S_ATTR_PURE_INSTRUCTIONS)
		ft_putstr("S_ATTR_PURE_INSTRUCTIONS");
	else if (secattr == S_ATTR_NO_TOC)
		ft_putstr("S_ATTR_NO_TOC");
	else if (secattr == S_ATTR_STRIP_STATIC_SYMS)
		ft_putstr("S_ATTR_STRIP_STATIC_SYMS");
	else if (secattr == S_ATTR_NO_DEAD_STRIP)
		ft_putstr("S_ATTR_NO_DEAD_STRIP");
	else if (secattr == S_ATTR_LIVE_SUPPORT)
		ft_putstr("S_ATTR_LIVE_SUPPORT");
	else if (secattr == S_ATTR_SELF_MODIFYING_CODE)
		ft_putstr("S_ATTR_SELF_MODIFYING_CODE");
	else if (secattr == S_ATTR_DEBUG)
		ft_putstr("S_ATTR_DEBUG");
	else if (secattr == SECTION_ATTRIBUTES_SYS)
		ft_putstr("SECTION_ATTRIBUTES_SYS");
	else if (secattr == S_ATTR_SOME_INSTRUCTIONS)
		ft_putstr("S_ATTR_SOME_INSTRUCTIONS");
	else if (secattr == S_ATTR_EXT_RELOC)
		ft_putstr("S_ATTR_EXT_RELOC");
	else if (secattr == S_ATTR_LOC_RELOC)
		ft_putstr("S_ATTR_LOC_RELOC");
	else
		ft_putstr("UNKNOWN");
	ft_putstr("\n");
}

void handle_segment_command(struct segment_command_64 *seg, void *ptr)
{
	uint32_t i;
	struct section_64 *sec;

	ft_putstr("Segment name: ");
	ft_putstr(seg->segname);
	ft_putstr(" number of section: ");
	ft_putnbr(seg->nsects);
	ft_putstr("\n");
	i = 0;
	while (i < seg->nsects)
	{
		sec = get_section_command(seg, i);
		handle_section_command(sec, ptr);
		i++;
	}
}

/*
** Handle a load command to extract information
*/
void handle_load_command(struct load_command *lc, void *ptr)
{
	struct symtab_command *sym;
	struct segment_command_64 *seg;


	if (lc->cmd == LC_SYMTAB)
	{
		sym = (struct symtab_command *)lc;
		handle_symtab_command(sym, ptr);
	}
	else if (lc->cmd == LC_SEGMENT_64)
	{
		seg = (struct segment_command_64 *)lc;
		handle_segment_command(seg, ptr);
		// handle_section_command((void*)seg + sizeof(struct segment_command_64), ptr);
	}
}

/*
** Handle the macho file format
*/
void	handle_macho_64(void *ptr)
{
	struct mach_header_64 *header;
	uint32_t ncmds;
	uint32_t i;
	struct load_command *lc;

	header = (struct mach_header_64*)ptr;
	display_mach_header_64(header);
	handle_file_type(header->filetype);
	handle_cpu_type(header->cputype, header->cpusubtype);
	i = 0;
	ncmds = header->ncmds;
	lc = get_first_load_command(header);
	while (i < ncmds)
	{
		handle_load_command_type(lc->cmd);
		handle_load_command(lc, ptr);
		lc = get_next_load_command(lc);
		i++;
	}
}
