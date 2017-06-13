#include "nm-otool.h"

void process_file(char *file_name)
{
	int fd;
	void *ptr;

	fd = open_file(file_name);
	ptr = map_file_into_memory(fd);
	display_mach_header_64((struct mach_header_64*)ptr);
}

void parse_flags_args(int argc, char **argv)
{

}

void	parse_file_args(int nb_files, char **args_file)
{
	int i;

	i = 0;
	if (i < nb_files)
	{
		process_file(args_file[i]);
		i++;
	}
}

void parse_args(int argc, char **argv)
{
	if (argc != 2)
	{
		ft_error_str_exit("An argument is required\n");
	}
	parse_file_args(argc, argv);
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
