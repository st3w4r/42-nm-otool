#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <mach-o/loader.h>
#include <mach-o/nlist.h>

void print_output(int nsyms, int symoff, int stroff, void *ptr)
{
	int i;
	char *string_table;
	struct nlist_64 *array;


	array = ptr + symoff;
	string_table = ptr + stroff;

	i = 0;
	while (i < nsyms)
	{
		printf("%s\n", string_table + array[i].n_un.n_strx);
		i++;
	}
}

void handle_64(char *ptr)
{
	int										ncmds;
	int										i;
	struct mach_header_64	*header;
	struct load_command		*lc;
	struct symtab_command *sym;

	header = (struct mach_header_64*)ptr;
	ncmds = header->ncmds;
	i = 0;
	lc = (void*)ptr + sizeof(*header);
	while (i < ncmds)
	{
		if (lc->cmd == LC_SYMTAB)
		{
			sym = (struct symtab_command *)lc;
			// printf("nb symbols %d\n", sym->nsyms);
			print_output(sym->nsyms, sym->symoff, sym->stroff, ptr);
			break ;
		}
		lc = (void *)lc + lc->cmdsize;
		i++;
	}
}

void nm(char *ptr)
{
	int magic_number;

	magic_number = *(int *)ptr;
	if (magic_number == MH_MAGIC_64)
	{
		puts("Binary for 64bits");
		handle_64(ptr);
	}
}

int main(int argc, char **argv)
{
	int fd;
	char *ptr;
	struct stat buf;

	if (argc != 2)
	{
		fprintf(stderr, "Please 2 args\n");
		return (EXIT_FAILURE);
	}
	if ((fd = open(argv[1], O_RDONLY)) < 0)
	{
		// fprintf(stderr, "Open error\n" );
		perror("open");
		return (EXIT_FAILURE);
	}
	if (fstat(fd, &buf) < 0)
	{
		perror("fstat");
		return (EXIT_FAILURE);
	}
	if ((ptr = mmap(0, buf.st_size, PROT_READ, MAP_PRIVATE, fd, 0)) == MAP_FAILED)
	{
		perror("mmap");
		return (EXIT_FAILURE);
	}
	nm(ptr);
	if (munmap(ptr, buf.st_size) < 0)
	{
		perror("munmap");
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
