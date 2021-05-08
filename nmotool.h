//
// Created by И Б on 08.05.2021.
//

#ifndef NM_OTOOL_NMOTOOL_H
#define NM_OTOOL_NMOTOOL_H

# include "ft_printf/includes/printf.h"
# include <sys/stat.h>
# include <sys/wait.h>
# include <sys/mman.h>

enum	errors
{
	ARG = 1,
	OPEN,
	CLOSE,
	FSTAT,
	MMAP,
	MALLOC,
	ARCH_ERR,
	CORR_BIN
};

void	errors_nm_otool(enum errors error);

#endif //NM_OTOOL_NMOTOOL_H
