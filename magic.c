//
// Created by И Б on 08.05.2021.
//

#include "nmotool.h"

char 	*reverse_size(char *flb, size_t stat_size)
{
	int32_t		*new_flb;
	size_t		i;

	i = 0;
	stat_size = stat_size / 4;
	new_flb = (void*)flb;
	while (i < stat_size)
	{
		new_flb[i] = ((new_flb[i] & 0xff000000) >> 24) |
				  ((new_flb[i] & 0x00ff0000) >> 8) |
				  ((new_flb[i] & 0x0000ff00) << 8) | (new_flb[i] << 24);
		i++;
	}
	return (flb);
}

char 	*swap_bytes(char *flb, size_t stat_size, int size_arch)
{
	struct mach_header	*mh;
	struct symtab_command	*sc;

	reverse_size(flb, stat_size);
	return (flb);
}


char *get_endian_reverse(char *flb, size_t stat_size)
{
//	unsigned int *tmp = (unsigned int*) flb;

//	stat_size += 1;
	if (*(unsigned int*)flb == MH_CIGAM)
		return (swap_bytes(flb, stat_size, 32));
	else if (*(unsigned int*)flb == MH_CIGAM_64)
		return (flb);
	else if (*(unsigned int*)flb == FAT_CIGAM)
		return ("lol");
	else if (*(unsigned int*)flb == FAT_CIGAM_64)
		return ("lol");

//	if (*tmp == MH_CIGAM)
//		return ("lol");
//	else if (*tmp == MH_CIGAM_64)
//		return ("lol");
//	else if (*tmp == FAT_CIGAM)
//		return ("lol");
//	else if (*tmp == FAT_CIGAM_64)
//		return ("lol");
//	printf("%zu", stat_size);
	return flb;
}
