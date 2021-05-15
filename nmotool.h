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

#define NSECTS_64 (int)(&((struct segment_command_64*)(0x0))->nsects)
#define NSECTS (int)(&((struct segment_command*)(0x0))->nsects)
#define MH_NCMDS (int)(&((struct mach_header*)(0x0))->ncmds)

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

typedef struct	s_sect
{
	uint64_t	addr;
	uint64_t	offset;
	uint64_t	size;
}				t_sect;

enum	errors
{
	ARG = 1,
	OPEN,
	CLOSE,
	FSTAT,
	MMAP,
	MALLOC,
	ARCH_ERR,
	CORR_FILE
};

void	errors_nm_otool(enum errors error);
void get_info_file(char *name_file);
void	work_inside_binary(char *flb, size_t stat_size, char *file_name);
char *get_endian_reverse(char *flb, size_t stat_size);
t_lst *mach_o(char *flb, size_t file_size, char size_arch, char *a_s);
void *get_symtab(char *flb, size_t file_size, char size_arch);
void	new_elem_lst(t_lst **head, char *name, char type, size_t offset);
t_lst	*sorting_lst(t_lst *head);
void print_lst(t_lst *lst, char arch_size);
void	free_lst(t_lst *lst);
t_lst	*fat_o(char *flb, size_t stat_size, char arch_size, char *name);
char		*find_cpu(cpu_type_t cpu_type);
void	mach_o_otool(char *flb, size_t stat_size, char arch_size);
void	output_mach_o_otool(char *flb, t_sect sect, char arch_size);
void	fat_o_otool(char *flb, size_t stat_size, char arch_size, char *name);
void	work_inside_binary_otool(char *flb, size_t stat_size, char *file_name);
t_lst	*mach_o_64(char *flb, size_t file_size, char size_arch, char *ar);
char	*check_part_segment_64(void *addr, size_t *j, char n);
t_lst	*mach_o_32(char *flb, size_t file_size, char size_arch, char *ar);
void	*get_symtab_32(char *flb, size_t file_size);
void	*get_symtab_64(char *flb, size_t file_size);
char	*check_part_segment(void *addr, size_t *j, char n);

#endif //NM_OTOOL_NMOTOOL_H
