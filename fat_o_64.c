#include "nmotool.h"

int	check_it_64(char *flb, size_t i)
{
	unsigned int	cpu;
	size_t			iter;

	cpu = *(unsigned int *)(flb + 8 + (i * 24));
	iter = 0;
	while (iter < *(unsigned int *)(flb + 4))
	{
		if (iter != i)
		{
			if (*(unsigned int *)(flb + 8 + (iter * 24)) == cpu)
				return (0);
			if (*(unsigned int *)(flb + 8 + (iter * 24)) == \
					(cpu | 0x01000000))
				return (0);
			if ((*(unsigned int *)(flb + 8 + (iter * 24)) | 0x01000000) == cpu)
				return (1);
		}
		iter++;
	}
	return (iter);
}

size_t	len_flb_64(char *flb, size_t stat_size)
{
	size_t				len;
	size_t				res;
	size_t				i;
	struct fat_arch		*fa_32;
	struct fat_arch_64	*fa_64;

	i = 0;
	res = 0;
	len = *(unsigned int *)(flb + 4);
	fa_32 = (struct fat_arch *)(flb + 8);
	fa_64 = (struct fat_arch_64 *)(flb + 8);
	while (i < len && i * sizeof(*fa_64) + 8 < stat_size)
	{
		if (check_it_64(flb, i))
			res++;
		i++;
	}
	return (res);
}

//void 	init_fat_o(size_t *i, struct fat_arch_64 **fa_64,
//	struct fat_arch **fa_32, char *flb)
//{
//	*i = 0;
//	*fa_32 = (struct fat_arch *)(flb + 8);
//	*fa_64 = (struct fat_arch_64 *)(flb + 8);
//}
//
//void	output_header(char *name, cpu_type_t cpu_type)
//{
//	write(1, "\n", 1);
//	ft_putstr(name);
//	write(1, " (for architecture ", 19);
//	ft_putstr(find_cpu(cpu_type));
//	write(1, "):\n", 3);
//}

t_lst	*fat_o_64(char *flb, size_t stat_size, char arch_size, char *name)
{
	size_t				len;
	size_t				i;
	struct fat_arch		*fa_32;
	struct fat_arch_64	*fa_64;

	len = len_flb_64(flb, stat_size);
	init_fat_o(&i, &fa_64, &fa_32, flb);
	while (len && i * sizeof(*fa_64) + 8 < stat_size)
	{
		if (len_flb_64(flb, stat_size) > 1)
			output_header(name, fa_32->cputype);
		if (check_it_64(flb, i))
		{
			if (arch_size == 64)
				work_inside_binary(flb + fa_64->offset, fa_64->size, name);
			else
				work_inside_binary(flb + fa_32->offset, fa_32->size, name);
			len -= 1;
		}
		i++;
		fa_32 += 1;
		fa_64 += 1;
	}
	return (NULL);
}
