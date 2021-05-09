//
// Created by И Б on 08.05.2021.
//

#include "nmotool.h"

void	work_inside_binary(char *flb, size_t stat_size, char *file_name)
{
    t_list	*list;

	flb = get_magic(flb, stat_size);
	if (*(unsigned int*)flb == MH_MAGIC_64)
		list = mach_o(flb, stat_size, 64);
	else if (*(unsigned int*)flb == MH_MAGIC)
		ft_printf("yes");
	else if (*(unsigned int*)flb == FAT_MAGIC_64)
		ft_printf("yes");
	else if (*(unsigned int*)flb == FAT_MAGIC)
		ft_printf("yes");
	else
		errors_nm_otool(ARCH_ERR);
	ft_printf("%s", file_name);
}