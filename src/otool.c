/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   otool.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybarbier <ybarbier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/29 15:09:47 by ybarbier          #+#    #+#             */
/*   Updated: 2017/06/29 17:07:35 by ybarbier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm_otool.h"

void	process_file(char *file_name)
{
	int			fd;
	void		*ptr;
	t_s_file	*file;

	fd = open_file(file_name);
	if (is_file(fd) == FALSE)
	{
		ft_error_str("Is a directory.\n");
		return ;
	}
	ptr = map_file_into_memory(fd);
	file = init_file(ptr);
	file->filename = file_name;
	handle_format(ptr, file);
	release_memory(ptr, fd);
	close_file(fd);
	free(file);
}

int		parse_flags_args(int argc, char **argv)
{
	int i;
	int nb_flags;

	nb_flags = 0;
	i = 0;
	while (i < argc)
	{
		if (argv[i][0] == '-' && argv[i][1] != '\0')
		{
			nb_flags++;
		}
		i++;
	}
	return (nb_flags);
}

void	parse_file_args(int nb_files, char **args_file, int nb_flags)
{
	int i;

	g_prog.nbfiles = (nb_files - nb_flags);
	if (g_prog.nbfiles == 0)
	{
		ft_error_str_exit("At least one file is required\n");
	}
	i = 0;
	while (i < nb_files)
	{
		if (args_file[i][0] != '-')
		{
			process_file(args_file[i]);
		}
		i++;
	}
}

void	parse_args(int argc, char **argv)
{
	int nb_flags;

	if (argc < 2)
	{
		ft_error_str_exit("At least one argument is required\n");
	}
	nb_flags = parse_flags_args(argc, argv);
	parse_file_args(--argc, ++argv, nb_flags);
}

/*
** Contol flow:
** Read file
** Map file into memroy
** Display header
*/

int		main(int argc, char **argv)
{
	parse_args(argc, argv);
	return (0);
}
