//
// Created by И Б on 12.05.2021.
//

#include "nmotool.h"

int		check_it(char *flb, size_t i, char arch_size)
{
	unsigned int	cpu;
	size_t			iter;

	cpu = *(unsigned int*)(flb + 8 + (i * (arch_size == 64 ? 24 : 20)));
	iter = 0;
	while (iter < *(unsigned int*)(flb + 4))
	{
		if (iter != i)
		{
			if (*(unsigned int*)(flb + 8 + (iter * (arch_size == 64 ? 24 : 20))) == cpu)
				return (0);
			if (*(unsigned int*)(flb + 8 + (iter * (arch_size == 64 ? 24 : 20))) ==
					(cpu | 0x01000000))
				return (0);
			if ((*(unsigned int*)(flb + 8 + (iter * (arch_size == 64 ? 24 : 20))) | 0x01000000) == cpu)
				return (1);
		}
		iter++;
	}
	return (iter);
}

size_t	len_flb(char *flb, size_t stat_size, char arch_size)
{
	size_t	len;
	size_t	res;
	size_t	i;
	struct fat_arch		*fa_32;
	struct fat_arch_64		*fa_64;

	i = 0;
	res = 0;
	len = *(unsigned int*)(flb + 4);
	fa_32 = (struct fat_arch*)(flb + 8);
	fa_64 = (struct fat_arch_64*)(flb + 8);
	while (i < len && i * (arch_size == 64 ? sizeof(*fa_64) :
						   sizeof(*fa_32)) + 8 < stat_size)
	{
		if (check_it(flb, i, arch_size))
			res++;
		i++;
	}
	return (res);
}

t_lst	*fat_o(char *flb, size_t stat_size, char arch_size, char *name)
{
	size_t		len;
	size_t		i;
	struct fat_arch		*fa_32;
	struct fat_arch_64		*fa_64;

	len = len_flb(flb, stat_size, arch_size);
	//todo check cpu and print fat_o
}
