//
// Created by И Б on 08.05.2021.
//

#include "nmotool.h"

char *get_magic(char *flb, size_t stat_size)
{
	unsigned int *tmp = (unsigned int*) flb;

	if (*(unsigned int*)flb == MH_CIGAM)
		return ("lol");
	else if (*(unsigned int*)flb == MH_CIGAM_64)
		return ("lol");
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
	return (char*)tmp;
}
