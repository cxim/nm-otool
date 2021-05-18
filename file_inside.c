#include "nmotool.h"

void	solo_func(t_flags flags)
{
	get_info_file("a.out", flags);
	exit(0);
}

t_lst	*work_ins_bin_p_two(char *flb, size_t stat_size, \
	char *arch_size, t_lst *list)
{
	if (flb == NULL)
		return (NULL);
	else if (*(unsigned int *)flb == MH_MAGIC_64)
		list = mach_o_64(flb, stat_size, 64, arch_size);
	else if (*(unsigned int *)flb == MH_MAGIC)
		list = mach_o_32(flb, stat_size, 32, arch_size);
	return (list);
}

void	work_inside_binary(char *flb, size_t stat_size, \
	char *file_name, t_flags flags)
{
	t_lst	*list;
	char	arch_size;

	list = NULL;
	arch_size = '\0';
	flb = get_endian_reverse(flb, stat_size);
	list = work_ins_bin_p_two(flb, stat_size, &arch_size, list);
	if (!list && !flb)
		return ;
	else if (!list && *(unsigned int *)flb == FAT_MAGIC_64)
	{
		list = fat_o_64(flb, stat_size, flags, file_name);
		arch_size = 64;
	}
	else if (!list && *(unsigned int *)flb == FAT_MAGIC)
	{
		list = fat_o_32(flb, stat_size, flags, file_name);
		arch_size = 32;
	}
	else if (!list)
		errors_nm_otool(ARCH_ERR);
	if (flags.flag_block != 1)
		sorting_lst(list, flags);
	print_lst(list, arch_size, flags, file_name);
	free_lst(list);
}
