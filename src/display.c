#include "nm-otool.h"

void display_file_format(e_file_format file_format)
{
	if (file_format == MACHO_32)
		ft_putstr("File format: MACHO_32\n");
	else if (file_format == MACHO_64)
		ft_putstr("File format: MACHO_64\n");
	else
		ft_putstr("File format: UNKNOWN\n");
}

void	display_symbol(char *str)
{
	ft_putstr(str);
}

void	display_mach_header_32(struct mach_header *header)
{
	ft_putstr("magic: ");				ft_puthexa(header->magic);			ft_putstr("\n");
	ft_putstr("cputype: ");			ft_puthexa(header->cputype);		ft_putstr("\n");
	ft_putstr("cpusubtype: ");	ft_puthexa(header->cpusubtype);	ft_putstr("\n");
	ft_putstr("filetype: ");		ft_puthexa(header->filetype);		ft_putstr("\n");
	ft_putstr("ncmds: ");				ft_putnbr(header->ncmds);			ft_putstr("\n");
	ft_putstr("sizeofcmds: ");	ft_puthexa(header->sizeofcmds);	ft_putstr("\n");
	ft_putstr("flags: ");				ft_puthexa(header->flags);			ft_putstr("\n");
	ft_putstr("\n");
}

void	display_mach_header_64(struct mach_header_64 *header)
{
	ft_putstr("magic: ");				ft_puthexa(header->magic);			ft_putstr("\n");
	ft_putstr("cputype: ");			ft_puthexa(header->cputype);		ft_putstr("\n");
	ft_putstr("cpusubtype: ");	ft_puthexa(header->cpusubtype);	ft_putstr("\n");
	ft_putstr("filetype: ");		ft_puthexa(header->filetype);		ft_putstr("\n");
	ft_putstr("ncmds: ");				ft_putnbr(header->ncmds);			ft_putstr("\n");
	ft_putstr("sizeofcmds: ");	ft_puthexa(header->sizeofcmds);	ft_putstr("\n");
	ft_putstr("flags: ");				ft_puthexa(header->flags);			ft_putstr("\n");
	ft_putstr("reserved: ");		ft_puthexa(header->reserved);		ft_putstr("\n");
	ft_putstr("\n");
}
