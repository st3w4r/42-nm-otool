/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_mem.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybarbier <ybarbier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/29 15:08:45 by ybarbier          #+#    #+#             */
/*   Updated: 2017/06/29 16:58:09 by ybarbier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm_otool.h"
#include <stdint.h>

void	ft_print_mem(void *addr, void *memory_addr, int len, bool is_64)
{
	int				i;
	unsigned char	*byte_addr;

	byte_addr = addr;
	i = 0;
	while (i < len)
	{
		if ((i % 16) == 0)
		{
			if (i != 0)
				ft_putstr("\n");
			if (is_64)
				ft_puthexa_size((uint64_t) & (memory_addr[i]),
								sizeof(uint64_t) * 2);
			else
				ft_puthexa_size((uint32_t) & (memory_addr[i]),
								sizeof(uint32_t) * 2);
			ft_putstr("\t");
		}
		ft_puthexa_size(byte_addr[i], 2);
		ft_putstr(" ");
		i++;
	}
}
