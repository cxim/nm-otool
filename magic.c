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
	mh = (struct mach_header*)flb;
	if ((sc = (struct symtab_command*)get_symtab(flb, stat_size, size_arch)) == NULL)
		return (NULL);
	reverse_size(flb + sc->stroff, sc->strsize);
	return (flb);
}

char 	*swap_bytes_fat(char *flb, int size_arch)
{
	reverse_size(flb, 8);
	reverse_size(flb + 8, *(unsigned int*)(flb + 4) * (size_arch == 64 ?
													   sizeof(struct fat_arch) : sizeof(struct fat_arch_64)));
	return (flb);
}



char *get_endian_reverse(char *flb, size_t stat_size)
{
//	unsigned int *tmp = (unsigned int*) flb;

//	stat_size += 1;
	if (*(unsigned int*)flb == MH_CIGAM)
		return (swap_bytes(flb, stat_size, 32));
	else if (*(unsigned int*)flb == MH_CIGAM_64)
		return (swap_bytes(flb, stat_size, 64));
	else if (*(unsigned int*)flb == FAT_CIGAM)
		return (swap_bytes_fat(flb, 32));
	else if (*(unsigned int*)flb == FAT_CIGAM_64)
		return (swap_bytes_fat(flb, 64));

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
