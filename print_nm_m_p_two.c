//
// Created by И Б on 20.05.2021.
//

#include "nmotool.h"

void	ft_put_name(char *name)
{
	ft_putstr(name);
	ft_putstr(": ");
}

void	get_agg(t_flags *tmp, char *tmp_str, size_t i)
{
	if (tmp_str[i] == 'p')
		tmp->flag_block = 1;
	else if (tmp_str[i] == 'r')
		tmp->flag_reverse = 1;
	else if (tmp_str[i] == 'A')
		tmp->flag_put_name = 1;
	else if (tmp_str[i] == 'j')
		tmp->flag_no_hex = 1;
	else
	{
		ft_putstr_fd(tmp_str, 2);
		ft_putstr_fd(" : Invalid argument\n", 2);
		exit(0);
	}
}

void	init_flags(t_flags *flags)
{
	flags->sum_flags = 0;
	flags->flag_reverse = 0;
	flags->flag_put_name = 0;
	flags->flag_no_hex = 0;
	flags->flag_block = 0;
	flags->minus = 0;
}

void	init_part_two(t_flags *tmp, char *tmp_str, size_t *i, char **tmp_names)
{
	size_t	j;
	char	*name;
	t_flags	tmp_flag;

	tmp_flag = *tmp;
	name = *tmp_names;
	j = *i;
	get_agg(&tmp_flag, tmp_str, j);
	j++;
	if (j == ft_strlen(tmp_str))
		name = "\0";
	*i = j;
	*tmp_names = name;
	*tmp = tmp_flag;
}
