//
// Created by И Б on 10.05.2021.
//

#include "nmotool.h"

void	hex_output(char c)
{
	char res;

	res = c + '0';
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

void print_addr(void *address)
{
	long	num;

	num = (long)address;
	if (num < 16)
		hex_output(num);
	else if (num > 9)
	{
		print_addr((void*)(num / 16));
		print_addr((void*)(num % 16));
	}
}

void print_o(size_t offset, char arch_size)
{
	int 	i;
	size_t 	s;

	i = 0;
	s = offset;
	while (offset > 15)
	{
		offset = offset / 16;
		i++;
	}
	write(1, "0000000000000000", arch_size == 64 ? 15 - i : 7 - i);
	print_addr((void*)s);
}

void print_lst(t_lst *lst, char arch_size)
{
	while (lst)
	{
		if (lst->data.type == 'U' || lst->data.type == 'u')
			write(1, "                ", arch_size == 32 ? 8 : 16);
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