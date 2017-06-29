/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybarbier <ybarbier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/29 15:10:08 by ybarbier          #+#    #+#             */
/*   Updated: 2017/06/29 17:12:38 by ybarbier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm_otool.h"

/*
** Get the size of a file from a file descriptor
*/

size_t		get_size_of_file(int fd)
{
	struct stat s_stat;

	s_stat = get_stat_of_file(fd);
	return (s_stat.st_size);
}

/*
** Get the stats of file from a fd
*/

struct stat	get_stat_of_file(int fd)
{
	struct stat	buf;

	if (fstat(fd, &buf) < 0)
	{
		ft_error_str_exit("fstat error\n");
	}
	return (buf);
}

bool		is_file(int fd)
{
	struct stat buf;

	if (fstat(fd, &buf) < 0)
	{
		ft_error_str_exit("fstat error\n");
	}
	if (S_ISREG(buf.st_mode))
		return (TRUE);
	else
		return (FALSE);
}

/*
** Open file and return a file descriptor
*/

int			open_file(char *name)
{
	int fd;

	fd = open(name, O_RDONLY);
	if (fd < 0)
	{
		ft_error_str_exit("open error\n");
	}
	return (fd);
}

/*
** Close file, exit if error trhogt up
*/

void		close_file(int fd)
{
	int result;

	result = close(fd);
	if (result < 0)
	{
		ft_error_str_exit("close error\n");
	}
}
