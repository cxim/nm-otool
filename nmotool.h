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
# include <mach-o/nlist.h>

typedef struct			s_data
{
	char				*name;
	char				type;
	size_t				offset;
}						t_data;

typedef struct			s_lst
{
	t_data				data;
	struct s_lst		*next;
}						t_lst;

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
char *get_endian_reverse(char *flb, size_t stat_size);
t_lst *mach_o(char *flb, size_t file_size, char size_arch, char *a_s);
void *get_symtab(char *flb, size_t file_size, char size_arch);
void	new_elem_lst(t_lst **head, char *name, char type, size_t offset);
t_lst	*sorting_lst(t_lst *head);
void print_lst(t_lst *lst, char arch_size);
void	free_lst(t_lst *lst);
t_lst	*fat_o(char *flb, size_t stat_size, char arch_size, char *name);

#endif //NM_OTOOL_NMOTOOL_H
