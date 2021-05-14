//
// Created by И Б on 14.05.2021.
//

#include "nmotool.h"


int check_part_segment_otool(void *lc, char arch_size, t_sect *sect)
{
	size_t				i;
	struct section_64	*section64;
	struct section		*section;

	i = 0;
	section = (void*)(lc + (arch_size == 64 ? sizeof(struct segment_command_64) :
							sizeof(struct segment_command)));
	section64 = (void*)section;
	while (i < *((unsigned int*)((void*)lc + (arch_size == 64 ? NSECTS_64 : NSECTS))))
	{
		if (!ft_strcmp(arch_size == 64 ? section64->sectname : section->sectname, "__text"))
		{
			(*sect).size = arch_size == 64 ? section64->size : section->size;
			(*sect).offset = arch_size == 64 ? section64->offset : section->offset;
			(*sect).addr = arch_size == 64 ? section64->addr : section->addr;
			return (1);
		}
		section += 1;
		section64 += 1;
		i++;
	}
	return (0);
}

int	get_size_sect(char *flb, size_t stat_size, char arch_size, t_sect *sect)
{
	struct load_command		*lc;
	unsigned int			j;
	size_t					i;

	j = 0;
	lc = (void*)flb + (arch_size == 32 ? sizeof(struct mach_header) :
					   sizeof(struct mach_header_64));
	while (j++ < *((unsigned int*)(flb + MH_NCMDS)) &&
			(void*)lc < stat_size + (void*)flb)
	{
		if (lc->cmd == (arch_size == 64 ? LC_SEGMENT_64 : LC_SEGMENT) && !(i = 0))
		{
			if (check_part_segment_otool((void*)lc, arch_size, sect))
				return (1);
		}
		lc = (void*)lc + lc->cmdsize;
	}
	return (0);
}

void	mach_o_otool(char *flb, size_t stat_size, char arch_size)
{
	int	sect_tab;
	t_sect	sect;

	sect.size = 0;
	sect.offset = 0;
	sect.addr = 0;
	if ((sect_tab = get_size_sect(flb, stat_size, arch_size, &sect)) == 0)
		return;
	output_mach_o_otool(flb, sect, arch_size);
}