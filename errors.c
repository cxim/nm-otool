//
// Created by И Б on 08.05.2021.
//
#include "nmotool.h"



void	errors_nm_otool(enum errors error)
{
	if (error == ARG)
	{
		write(2, "a.out: No such file or directory.\n", 34);
	}
	else if (error == OPEN)
		write(2, "No such file or directory.\n", 31);
	else if (error == FSTAT)
		write(2, "fstat problem.\n", 16);
	else if (error == MMAP)
		write(2, "mmap error\n", 11); //fail open dirs
	else if (error == CLOSE)
		write(2, "cant close file\n", 21);
	else if (error == ARCH_ERR)
	    write(2, "error: architecture problem\n", 29);
	else if (error == CORR_BIN)
		write(2, "file corrupted\n", 16);
}