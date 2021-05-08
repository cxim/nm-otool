//
// Created by И Б on 08.05.2021.
//

#include "nmotool.h"

void	work_inside_binary(char *flb, size_t stat_size, char *file_name)
{
	flb = get_magic(flb, stat_size);
	if (*(unsigned int*)flb == MH_MAGIC_64)
		printf("yes");
	else if (*(unsigned int*)flb == MH_MAGIC)
		printf("yes");
	else if (*(unsigned int*)flb == FAT_MAGIC_64)
		printf("yes");
	else if (*(unsigned int*)flb == FAT_MAGIC)
		printf("yes");
	else
		errors_nm_otool(ARCH_ERR);
	printf("%s", file_name);
}