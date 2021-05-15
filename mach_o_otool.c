#include "nmotool.h"

int	check_part_segment_otool_64(void *lc, t_sect *sect)
{
	size_t				i;
	struct section_64	*se64;

	i = 0;
	se64 = (void *)(lc + sizeof(struct segment_command_64));
	while (i < *((unsigned int *)((void *)lc + NSECTS_64)))
	{
		if (!ft_strcmp(se64->sectname, "__text"))
		{
			(*sect).size = se64->size;
			(*sect).offset = se64->offset;
			(*sect).addr = se64->addr;
			return (1);
		}
		se64 += 1;
		i++;
	}
	return (0);
}

int	check_part_segment_otool_32(void *lc, t_sect *sect)
{
	size_t				i;
	struct section		*se;

	i = 0;
	se = (void *)(lc + sizeof(struct segment_command));
	while (i < *((unsigned int *)((void *)lc + NSECTS)))
	{
		if (!ft_strcmp(se->sectname, "__text"))
		{
			(*sect).size = se->size;
			(*sect).offset = se->offset;
			(*sect).addr = se->addr;
			return (1);
		}
		se += 1;
		i++;
	}
	return (0);
}

int	get_size_sect_64(char *flb, size_t stat_size, char arch_size, t_sect *sect)
{
	struct load_command		*lc;
	unsigned int			j;
	size_t					i;

	j = 0;
	i = 0;
	lc = (void *)flb + sizeof(struct mach_header_64);
	while (j++ < *((unsigned int *)(flb + MH_NCMDS)) && \
			(void *)lc < stat_size + (void *)flb)
	{
		if (lc->cmd == LC_SEGMENT_64)
		{
			if (arch_size == 64)
				if (check_part_segment_otool_64((void *)lc, sect))
					return (1);
		}
		lc = (void *)lc + lc->cmdsize;
	}
	return (0);
}

int	get_size_sect(char *flb, size_t stat_size, char arch_size, t_sect *sect)
{
	struct load_command		*lc;
	unsigned int			j;
	size_t					i;

	j = 0;
	i = 0;
	if (arch_size == 64)
		return (get_size_sect_64(flb, stat_size, 64, sect));
	lc = (void *)flb + sizeof(struct mach_header);
	while (j++ < *((unsigned int *)(flb + MH_NCMDS)) && \
			(void *)lc < stat_size + (void *)flb)
	{
		if (lc->cmd == LC_SEGMENT)
		{
			if (arch_size == 32)
				if (check_part_segment_otool_32((void *)lc, sect))
					return (1);
		}
		lc = (void *)lc + lc->cmdsize;
	}
	return (0);
}

void	mach_o_otool(char *flb, size_t stat_size, char arch_size)
{
	int		sect_tab;
	t_sect	sect;

	sect.size = 0;
	sect.offset = 0;
	sect.addr = 0;
	sect_tab = get_size_sect(flb, stat_size, arch_size, &sect);
	if (sect_tab == 0)
		return ;
	output_mach_o_otool(flb, sect, arch_size);
}
