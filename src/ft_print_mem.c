#include "nm-otool.h"
#include <stdint.h>

void	ft_print_mem(void *addr, void *memory_addr, int len, bool is_64)
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
			if (is_64)
				ft_puthexa_size((uint64_t)&memory_addr[i], sizeof(uint64_t) * 2);
			else
				ft_puthexa_size((uint32_t)&memory_addr[i], sizeof(uint32_t) * 2);
			ft_putstr("\t");
		}
		ft_puthexa_size(byte_addr[i], 2);
		ft_putstr(" ");
		i++;
	}
}
