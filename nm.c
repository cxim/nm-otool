/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnarwhal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/22 16:51:53 by mnarwhal          #+#    #+#             */
/*   Updated: 2020/08/22 16:53:10 by mnarwhal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nmotool.h"
#include <stdio.h>
#include <sys/types.h>

void	check_error_nm(void *flb, struct stat stat, int fd)
{
	if (munmap(flb, (size_t)stat.st_size) == -1)
	{
		errors_nm_otool(MMAP);
		return ;
	}
	if (close(fd) == -1)
		errors_nm_otool(CLOSE);
}

void	get_info_file(char *name_file, t_flags flags)
{
	struct stat	stat;
	int			fd;
	void		*file_length_bytes;

	fd = open(name_file, O_RDONLY);
	if (fd == -1)
	{
		errors_nm_otool(OPEN);
		return ;
	}
	if (fstat(fd, &stat) == -1)
		errors_nm_otool(FSTAT);
	file_length_bytes = mmap(0, (size_t)stat.st_size, PROT_READ |\
		PROT_WRITE, MAP_PRIVATE, fd, 0);
	if (file_length_bytes == MAP_FAILED)
	{
		errors_nm_otool(MMAP);
		return ;
	}
	work_inside_binary(file_length_bytes, stat.st_size, name_file, flags);
	check_error_nm(file_length_bytes, stat, fd);
}

t_flags	init(char **names)
{
	t_flags	tmp;
	char	**tmp_names;
	size_t	i;
	char	*tmp_str;

	i = 1;
	tmp_names = names;
	init_flags(&tmp);
	tmp_names++;
	while (*tmp_names)
	{
		if (*tmp_names[0] == '-' && ft_strlen(*tmp_names) > 1)
		{
			tmp.minus = 1;
			tmp_str = *tmp_names;
			while (i < ft_strlen(tmp_str))
				init_part_two(&tmp, tmp_str, &i, tmp_names);
		}
		else
			tmp.sum_flags++;
		i = 1;
		tmp_names++;
	}
	return (tmp);
}

void	find_file(char **av, t_flags flags)
{
	while (*av)
	{
		if (!(flags.minus == 1 && ft_strcmp(*av, "\0") == 0))
		{
			get_info_file(*av, flags);
		}
		av += 1;
	}
}

int	main(int ac, char **av)
{
	t_flags	flags;

	flags = init(av);
	if (ac < 2)
		solo_func(flags);
	av += 1;
	if (ac > 2 && flags.sum_flags > 1 && flags.flag_put_name != 1)
	{
		while (*av)
		{
			if (!(flags.minus == 1 && ft_strcmp(*av, "\0") == 0))
			{
				write(1, "\n", 1);
				ft_putstr(*av);
				write(1, ":\n", 2);
				get_info_file(*av, flags);
			}
			av += 1;
		}
	}
	else if (ac - 1 - flags.sum_flags == 1 || flags.flag_put_name == 1)
		find_file(av, flags);
	else
		get_info_file(av[0], flags);
	return (0);
}
