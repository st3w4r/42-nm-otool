/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybarbier <ybarbier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/29 15:06:47 by ybarbier          #+#    #+#             */
/*   Updated: 2017/06/29 15:06:48 by ybarbier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm_otool.h"

/*
** Check is the adress is not out of memory file
*/
void check_memory_out(void *ptr)
{
	if (ptr > g_prog.current_max_addr)
	{
		ft_error_str_exit("malformed file\n");
	}
}
