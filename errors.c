//
// Created by И Б on 08.05.2021.
//
#include "nmotool.h"



void	errors_nm_otool(enum errors error)
{
	if (error == ARG)
	{
		ft_putstr_fd("a.out: No such file or directory.\n", 2);
	}
	else if (error == OPEN)
		ft_putstr_fd("No such file or directory.\n", 2);
	else if (error == FSTAT)
		ft_putstr_fd("fstat problem.\n", 2);
	else if (error == MMAP)
		ft_putstr_fd("mmap error\n", 2); //fail open dirs
	else if (error == CLOSE)
		ft_putstr_fd("cant close file\n", 2);
	else if (error == ARCH_ERR)
	    ft_putstr_fd("error: architecture problem\n", 2);
	else if (error == CORR_BIN)
		ft_putstr_fd("file corrupted\n", 2);
}