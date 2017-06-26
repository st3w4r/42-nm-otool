#include "nm-otool.h"

void process_file(char *file_name)
{
	int fd;
	void *ptr;

	fd = open_file(file_name);
	if (is_file(fd) == FALSE)
	{
		ft_error_str("Is a directory\n");
		return ;
	}
	ptr = map_file_into_memory(fd);
	handle_format(ptr);
	release_memory(ptr, fd);
	close_file(fd);
	// handle_macho_64(ptr);
	// display_file_format(get_file_format(ptr));
	// display_mach_header_32((struct mach_header*)ptr);
}

void parse_flags_args(int argc, char **argv)
{

}

void	parse_file_args(int nb_files, char **args_file)
{
	int i;

	i = 0;
	while (i < nb_files)
	{
		ft_putendl(args_file[i]);
		process_file(args_file[i]);
		i++;
	}
}

void parse_args(int argc, char **argv)
{
	if (argc < 2)
	{
		ft_error_str_exit("At least one argument is required\n");
		// process_file("a.out");
	}
	parse_file_args(argc -1, ++argv);
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
