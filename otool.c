#include "nmotool.h"

void	work_inside_binary_otool(char *flb, size_t stat_size, char *file_name)
{
	file_name ="a";
	flb = get_endian_reverse(flb, stat_size);
	if (flb == NULL)
		return ;
	else if (*(unsigned int *)flb == MH_MAGIC_64)
		mach_o_otool(flb, stat_size, 64);
	else if (*(unsigned int *)flb == MH_MAGIC)
		mach_o_otool(flb, stat_size, 32);
	else if (*(unsigned int *)flb == FAT_MAGIC_64)
		fat_o_otool_64(flb, stat_size, 64, file_name);
	else if (*(unsigned int *)flb == FAT_MAGIC)
		fat_o_otool_32(flb, stat_size, 32, file_name);
	else
		errors_nm_otool(ARCH_ERR);
}

void	check_error(void *flb, struct stat stat, int fd)
{
	if (munmap(flb, (size_t)stat.st_size) == -1)
	{
		errors_nm_otool(MMAP);
		return ;
	}
	if (close(fd) == -1)
		errors_nm_otool(CLOSE);
}

void	get_info_file_otool(char *name_file)
{
	struct stat	stat;
	int			fd;
	void		*flb;

	fd = open(name_file, O_RDONLY);
	if (fd == -1)
	{
		errors_nm_otool(OPEN);
		return ;
	}
	if (fstat(fd, &stat) == -1)
		errors_nm_otool(FSTAT);
	flb = mmap(0, (size_t)stat.st_size, PROT_READ |\
		PROT_WRITE, MAP_PRIVATE, fd, 0);
	if (flb == MAP_FAILED)
	{
		errors_nm_otool(MMAP);
		return ;
	}
	work_inside_binary_otool(flb, stat.st_size, name_file);
	check_error(flb, stat, fd);
}

int	main(int ac, char **av)
{
	if (ac < 2)
		errors_nm_otool(ARG);
	av += 1;
	while (*av)
	{
		ft_putstr(*av);
		write(1, ":\n", 2);
		get_info_file_otool(*av);
		av += 1;
	}
	return (0);
}
