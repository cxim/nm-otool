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

void get_info_file(char *name_file)
{
	struct stat stat;
	int		fd;
	void	*file_length_bytes;

	file_length_bytes = mmap(0, (size_t)stat.st_size, PROT_READ |
	PROT_WRITE, MAP_PRIVATE, fd, 0);

	if ((fd = open(name_file, O_RDONLY)) == -1)
	{
		errors_nm_otool(OPEN);
		return;
	}
	if (fstat(fd, &stat) == -1)
		errors_nm_otool(FSTAT);
	if (file_length_bytes == MAP_FAILED)
		errors_nm_otool(MMAP);


	if (munmap(file_length_bytes, (size_t)stat.st_size) == -1)
	{
		errors_nm_otool(MMAP);
		return;
	}
	if (close(fd) == -1)
		errors_nm_otool(CLOSE);
	work_inside_binary(file_length_bytes, stat.st_size, name_file);

}

int		main(int ac, char **av)
{
	if (ac < 2)
		errors_nm_otool(ARG);
	av += 1;
	if (ac > 2) //if no errors and files > 1
		while (*av)
		{
			write(1, "\n", 1);
			ft_putstr(*av);
			write(1, ":\n", 2);
			get_info_file(*av);
			av += 1;
		}
	else //if 1 file
		get_info_file(av[0]);
	return (0);
}
