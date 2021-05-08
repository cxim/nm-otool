//
// Created by И Б on 08.05.2021.
//
#include "nmotool.h"



void	errors_nm_otool(enum errors error)
{
	if (error == ARG)
	{
		write(2, "a.out: No such file or directory.", 33);
	}
	else if (error == OPEN)
		write(2, "No such file or directory.", 30);
}