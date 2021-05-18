#include "nmotool.h"

int	check_it_32(char *flb, size_t i)
{
	unsigned int	cpu;
	size_t			iter;

	cpu = *(unsigned int *)(flb + 8 + (i * 20));
	iter = 0;
	while (iter < *(unsigned int *)(flb + 4))
	{
		if (iter != i)
		{
			if (*(unsigned int *)(flb + 8 + (iter * 20)) == cpu)
				return (0);
			if (*(unsigned int *)(flb + 8 + (iter * 20)) == \
					(cpu | 0x01000000))
				return (0);
			if ((*(unsigned int *)(flb + 8 + (iter * 20)) | 0x01000000) == cpu)
				return (1);
		}
		iter++;
	}
	return (iter);
}

size_t	len_flb_32(char *flb, size_t stat_size)
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
	while (i < len && i * sizeof(*fa_32) + 8 < stat_size)
	{
		if (check_it_32(flb, i))
			res++;
		i++;
	}
	return (res);
}

void 	init_fat_o(size_t *i, struct fat_arch_64 **fa_64, \
	struct fat_arch **fa_32, char *flb)
{
	*i = 0;
	*fa_32 = (struct fat_arch *)(flb + 8);
	*fa_64 = (struct fat_arch_64 *)(flb + 8);
}

void	output_header(char *name, cpu_type_t cpu_type)
{
	write(1, "\n", 1);
	ft_putstr(name);
	write(1, " (for architecture ", 19);
	ft_putstr(find_cpu(cpu_type));
	write(1, "):\n", 3);
}

t_lst	*fat_o_32(char *flb, size_t stat_size, t_flags flags, char *name)
{
	size_t				len;
	size_t				i;
	struct fat_arch		*fa_32;
	struct fat_arch_64	*fa_64;

	len = len_flb_32(flb, stat_size);
	init_fat_o(&i, &fa_64, &fa_32, flb);
	while (len && i * sizeof(*fa_32) + 8 < stat_size)
	{
		if (len_flb_32(flb, stat_size) > 1)
			output_header(name, fa_32->cputype);
		if (check_it_32(flb, i))
		{
			work_inside_binary(flb + fa_32->offset, fa_32->size, name, flags);
			len -= 1;
		}
		i++;
		fa_32 += 1;
		fa_64 += 1;
	}
	return (NULL);
}
