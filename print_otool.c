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

void	print_addr_otool(u_int64_t address)
{
	uint64_t	num;

	num = address;
	if (num < 16)
		hex_output(num);
	else if (num > 9)
	{
		print_addr_otool((num / 16));
		print_addr_otool((num % 16));
	}
}

void	output_content(char *flb, uint64_t sector, uint64_t max)
{
	uint64_t	i;

	i = 0;
	while (i < 16 && sector + i < max)
	{
		if ((*(char *)(sector + i + flb) & 0xff) < 16)
			write(1, "0", 1);
		print_addr_otool(*(char *)(sector + i + flb) & 0xff);
		write(1, " ", 1);
		i++;
	}
}

void	out_mach_o_tool_p_two(char arch_size, char c)
{
	if (arch_size == 64)
		write(1, "0000000000000000", 15 - c);
	else
		write(1, "0000000000000000", 7 - c);
}

void	output_mach_o_otool(char *flb, t_sect sect, char arch_size)
{
	uint64_t	i;
	uint64_t	j;
	char		c;

	i = 0;
	write(1, "(__TEXT,__text) section\n", 24);
	while (i < sect.size)
	{
		c = 0;
		j = i + sect.addr;
		while (j > 15)
		{
			j /= 16;
			c++;
		}
		out_mach_o_tool_p_two(arch_size, c);
		print_addr_otool(i + sect.addr);
		write(1, " ", 1);
		output_content(flb, i + sect.offset, sect.size + sect.offset);
		write(1, "\n", 1);
		i += 16;
	}
}
