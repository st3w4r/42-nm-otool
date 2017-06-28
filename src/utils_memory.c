#include "nm-otool.h"

/*
** Map a file into memory and retrun a pointer on the beginning
*/
void *map_file_into_memory(int fd)
{
	void *ptr;
	size_t file_size;

	file_size = get_size_of_file(fd);
	if (file_size <= 0)
	{
		ft_error_str_exit("file is empty\n");
	}
	ptr = mmap(0, file_size, PROT_READ, MAP_PRIVATE, fd, 0);
	g_prog.current_max_addr = ptr + file_size;
	if (ptr == MAP_FAILED)
	{
		ft_error_str_exit("mmap error\n");
	}
	return (ptr);
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
