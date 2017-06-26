#include "nm-otool.h"
#include <stdint.h>

void	ft_print_mem(void *addr, int len)
{
	int i;
	unsigned char *byte_addr;

	byte_addr = addr;
	i = 0;
	while (i < len)
	{
		if ((i % 16) == 0)
		{
			if (i != 0)
				ft_putstr("\n");
			ft_puthexa_size((uint64_t)&byte_addr[i], sizeof(addr) * 2);
			ft_putstr("\t");
		}
		ft_puthexa_size(byte_addr[i], 2);
		ft_putstr(" ");
		i++;
	}
}
