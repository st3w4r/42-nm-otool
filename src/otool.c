#include "nm-otool.h"

void process_file(char *file_name)
{
	int fd;
	void *ptr;
	s_file *file;

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
	// handle_macho_64(ptr);
	// display_file_format(get_file_format(ptr));
	// display_mach_header_32((struct mach_header*)ptr);
}

int parse_flags_args(int argc, char **argv)
{
	int i;
	int nb_flags;

	nb_flags = 0;
	i = 0;
	while (i < argc)
	{
		if (argv[i][0] == '-' && argv[i][1] != '\0')
		{
			if (argv[i][1] == 'a')
				g_prog.flags |= FLAG_a;
			else if (argv[i][1] == 'g')
				g_prog.flags |= FLAG_g;
			else if (argv[i][1] == 'm')
				g_prog.flags |= FLAG_m;
			else if (argv[i][1] == 'p')
				g_prog.flags |= FLAG_p;
			else if (argv[i][1] == 'u')
				g_prog.flags |= FLAG_u;
			else if (argv[i][1] == 'U')
				g_prog.flags |= FLAG_U;
			else if (argv[i][1] == 'x')
				g_prog.flags |= FLAG_x;
			nb_flags++;
		}
		i++;
	}
	return (nb_flags);
}

void	parse_file_args(int nb_files, char **args_file, int nb_flags)
{
	// int file_index;
	int i;

	// if ((g_prog.files = malloc(sizeof(char*) * (nb_files - nb_flags))) == NULL)
	// 	ft_malloc_error();

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
			// g_prog.files[file_index++] = args_file[i];
			// ft_putendl(args_file[i]);
			process_file(args_file[i]);
		}
		i++;
	}
}

void parse_args(int argc, char **argv)
{
	int nb_flags;

	if (argc < 2)
	{
		ft_error_str_exit("At least one argument is required\n");
		// process_file("a.out");
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
int	main(int argc, char **argv)
{
	parse_args(argc, argv);
	return (0);
}
