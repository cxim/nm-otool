#include "nmotool.h"

void	errors_nm_otool(enum e_errors error)
{
	if (error == ARG)
		ft_putstr_fd("a.out: No such file or directory.\n", 2);
	else if (error == OPEN)
		ft_putstr_fd("No such file or directory.\n", 2);
	else if (error == FSTAT)
		ft_putstr_fd("fstat problem.\n", 2);
	else if (error == MMAP)
		ft_putstr_fd("mmap error\n", 2);
	else if (error == CLOSE)
		ft_putstr_fd("cant close file\n", 2);
	else if (error == ARCH_ERR)
		ft_putstr_fd("error: architecture problem\n", 2);
	else if (error == CORR_FILE)
		ft_putstr_fd("file corrupted\n", 2);
	else if (error == MALLOC)
		ft_putstr_fd("Malloc error\n", 2);
}
