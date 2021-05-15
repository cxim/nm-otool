#include "nmotool.h"

void	hex_output(char c)
{
	if (c < 10)
	{
		c += 48;
		write(1, &c, 1);
	}
	else
	{
		c += 87;
		write(1, &c, 1);
	}
}

void	print_addr(void *address)
{
	long	num;

	num = (long)address;
	if (num < 16)
		hex_output(num);
	else if (num > 9)
	{
		print_addr((void *)(num / 16));
		print_addr((void *)(num % 16));
	}
}

void	out_mach_nm_p_two(char arch_size, char c)
{
	if (arch_size == 64)
		write(1, "0000000000000000", 15 - c);
	else
		write(1, "0000000000000000", 7 - c);
}

void	print_o(size_t offset, char arch_size)
{
	int		i;
	size_t	s;

	i = 0;
	s = offset;
	while (offset > 15)
	{
		offset = offset / 16;
		i++;
	}
	out_mach_nm_p_two(arch_size, i);
	print_addr((void *)s);
}

void	print_lst(t_lst *lst, char arch_size)
{
	while (lst)
	{
		if (lst->data.type == 'U' || lst->data.type == 'u')
		{
			if (arch_size == 32)
				write(1, "                ", 8);
			else
				write(1, "                ", 16);
		}
		else
			print_o(lst->data.offset, arch_size);
		write(1, " ", 1);
		write(1, &(lst->data.type), 1);
		write(1, " ", 1);
		ft_putstr(lst->data.name);
		write(1, "\n", 1);
		lst = lst->next;
	}
}
