#include "nm-otool.h"

/*
** Map a file into memory and retrun a pointer on the beginning
*/
void *map_file_into_memory(int fd)
{
	void *ptr;
	size_t file_size;

	file_size = get_size_of_file(fd);
	ptr = mmap(0, file_size, PROT_READ, MAP_PRIVATE, fd, 0);
	ft_putstr("File size: "); ft_putnbr(file_size); ft_putstr(" ");
	if (ptr == MAP_FAILED)
	{
		ft_error_str_exit("mmap error\n");
	}
	return ptr;
}

/*
** Release the memory allocation
*/
void release_memory(void *ptr, int fd)
{
	int result;
	size_t file_size;

	file_size = get_size_of_file(fd);
	result = munmap(ptr, file_size);
	if (result < 0)
	{
		ft_error_str_exit("munmap error\n");
	}
}

/*
** Get the size of a file from a file descriptor
*/
size_t get_size_of_file(int fd)
{
	struct stat s_stat;

	s_stat = get_stat_of_file(fd);
	return s_stat.st_size;
}

/*
** Get the stats of file from a fd
*/
struct stat get_stat_of_file(int fd)
{
	struct stat	buf;

	if (fstat(fd, &buf) < 0)
	{
		ft_error_str_exit("fstat error\n");
	}
	return buf;
}

/*
** Open file and return a file descriptor
*/
int open_file(char *name)
{
	int fd;

	fd = open(name, O_RDONLY);
	if (fd < 0)
	{
		ft_error_str_exit("open error\n");
	}
	return fd;
}

/*
** Close file, exit if error trhogt up
*/
void close_file(int fd)
{
	int result;

	result = close(fd);
	if (result < 0)
	{
		ft_error_str_exit("close error\n");
	}
}
