//
// Created by И Б on 08.05.2021.
//

#ifndef NM_OTOOL_NMOTOOL_H
#define NM_OTOOL_NMOTOOL_H

# include "ft_printf/includes/printf.h"
# include <sys/stat.h>
# include <sys/wait.h>
# include <sys/mman.h>
# include <mach/machine.h>
# include <mach-o/fat.h>
# include <mach-o/loader.h>

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
void	work_inside_binary(char *flb, size_t stat_size, char *file_name);
char	*get_magic(char *flb, size_t stat_size);
t_list *mach_o(char *flb, size_t file_size, char size_arch);

#endif //NM_OTOOL_NMOTOOL_H
