#ifndef NMOTOOL_H
# define NMOTOOL_H

# include "libft/libft.h"
# include <sys/stat.h>
# include <sys/wait.h>
# include <sys/mman.h>
# include <mach/machine.h>
# include <mach-o/fat.h>
# include <mach-o/loader.h>
# include <mach-o/nlist.h>

typedef struct s_data
{
	char			*name;
	char			type;
	size_t			offset;
}				t_data;

typedef struct s_lst
{
	t_data				data;
	struct s_lst		*next;
}				t_lst;

typedef struct s_sect
{
	uint64_t	addr;
	uint64_t	offset;
	uint64_t	size;
}				t_sect;

enum	e_errors
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

typedef struct s_flags
{
	int	minus;
	int	flag_block;
	int	flag_reverse;
	int	flag_put_name;
	int	flag_no_hex;
	int	sum_flags;
}				t_flags;

void	errors_nm_otool(enum e_errors error);
void	get_info_file(char *name_file, t_flags flags);
void	work_inside_binary(char *flb, size_t stat_size, \
		char *file_name, t_flags flags);
char	*get_endian_reverse(char *flb, size_t stat_size);
//t_lst *mach_o(char *flb, size_t file_size, char size_arch, char *a_s);
//void *get_symtab(char *flb, size_t file_size, char size_arch);
void	new_elem_lst(t_lst **head, char *name, char type, size_t offset);
t_lst	*sorting_lst(t_lst *head, t_flags flags);
void	print_lst(t_lst *lst, char arch_size, t_flags flags, char *name);
void	free_lst(t_lst *lst);
t_lst	*fat_o_32(char *flb, size_t stat_size, t_flags flags, char *name);
char	*find_cpu(cpu_type_t cpu_type);
void	mach_o_otool(char *flb, size_t stat_size, char arch_size);
void	output_mach_o_otool(char *flb, t_sect sect, char arch_size);
void	fat_o_otool_32(char *flb, size_t stat_size, char arch_size, char *name);
void	work_inside_binary_otool(char *flb, size_t stat_size, char *file_name);
t_lst	*mach_o_64(char *flb, size_t file_size, char size_arch, char *ar);
char	*check_part_segment_64(void *addr, size_t *j, char n);
t_lst	*mach_o_32(char *flb, size_t file_size, char size_arch, char *ar);
void	*get_symtab_32(char *flb, size_t file_size);
void	*get_symtab_64(char *flb, size_t file_size);
char	*check_part_segment(void *addr, size_t *j, char n);
void	fat_o_otool_64(char *flb, size_t stat_size, char arch_size, char *name);
void	output_header_otool(char *name, cpu_type_t cpu_type);
void	init_fat_o_otool(size_t *i, struct fat_arch_64 **fa_64,	\
		struct fat_arch **fa_32, char *flb);
t_lst	*fat_o_64(char *flb, size_t stat_size, t_flags flags, char *name);
void	output_header(char *name, cpu_type_t cpu_type);
void	init_fat_o(size_t *i, struct fat_arch_64 **fa_64,	\
	struct fat_arch **fa_32, char *flb);
void	solo_func(t_flags flags);
void	ft_put_name(char *name);
void	init_part_two(t_flags *tmp, char *tmp_str, size_t *i, char **tmp_names);
void	get_agg(t_flags *tmp, char *tmp_str, size_t i);
void	get_agg(t_flags *tmp, char *tmp_str, size_t i);
void	init_flags(t_flags *flags);
#endif
