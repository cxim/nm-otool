#include "nmotool.h"

char	*get_sect_tab_64(char *flb, size_t file_size, char n)
{
	struct load_command		*lc;
	unsigned int			index;
	char					*rslt;
	size_t					j;

	index = 0;
	j = 1;
	lc = (void *)flb + sizeof(struct mach_header_64);
	while (index++ < *((unsigned int *)(flb + MH_NCMDS)) && \
		   (void *)lc < file_size + (void *)flb)
	{
		if (lc->cmd == LC_SEGMENT_64)
		{
			rslt = check_part_segment_64((void *)lc, &j, n);
			if (rslt)
				return (rslt);
		}
		lc = (void *)lc + lc->cmdsize;
	}
	return (NULL);
}

char	type_part_two_64(char *flb, size_t file_size, char n)
{
	char	*str;

	str = get_sect_tab_64(flb, file_size, n);
	if (str == NULL)
		return ('S');
	if (ft_strcmp(str, "__text") == 0)
		return ('T');
	else if (ft_strcmp(str, "__bss") == 0)
		return ('B');
	else if (ft_strcmp(str, "__data") == 0)
		return ('D');
	return ('S');
}

char 	type_64(uint16_t section, char *flb, size_t file_size)
{
	uint8_t	sec;
	uint8_t	type_section;
	char	ret;

	type_section = section;
	sec = section >> 8;
	if ((type_section & N_TYPE) == N_UNDF && sec == 0)
		ret = 'U';
	else if ((type_section & N_TYPE) == N_SECT)
		ret = type_part_two_64(flb, file_size, sec);
	else if ((type_section & N_TYPE) == N_ABS)
		ret = 'A';
	else if ((type_section & N_TYPE) == N_INDR)
		ret = 'I';
	else
		return ('?');
	if (type_section & N_EXT)
		return (ret);
	else
		return (ret + 32);
}

void	*get_symtab_64(char *flb, size_t file_size)
{
	size_t					i;
	struct load_command		*lc;
	struct mach_header		*mh;

	mh = (struct mach_header *)flb;
	i = 0;
	lc = (void *)flb + sizeof(struct mach_header_64);
	while (i < mh->ncmds && (void *)lc < file_size + (void *)flb)
	{
		if (lc->cmd == LC_SYMTAB)
			break ;
		lc = (void *)lc + lc->cmdsize;
		i++;
	}
	if ((void *)lc > file_size + (void *)flb)
	{
		errors_nm_otool(CORR_FILE);
		return (NULL);
	}
	if (i == mh->ncmds)
		return (NULL);
	return ((void *)lc);
}

t_lst	*mach_o_64(char *flb, size_t file_size, char size_arch, char *ar)
{
	t_lst					*list;
	struct symtab_command	*sc;
	struct nlist_64			*nl64;
	size_t					i;

	sc = (struct symtab_command *)get_symtab_64(flb, file_size);
	if (sc == NULL)
		return (NULL);
	i = -1;
	list = NULL;
	nl64 = (void *)flb + sc->symoff;
	*ar = size_arch;
	while (++i < sc->nsyms)
	{
		if (size_arch == 64 && (nl64[i].n_type == 1 || nl64[i].n_type == 14 || \
			nl64[i].n_type == 15 || nl64[i].n_type == 0 || nl64[i].n_type == 3 \
			|| nl64[i].n_type == 30))
			new_elem_lst(&list, (void *) flb + sc->stroff + \
				nl64[i].n_un.n_strx, type_64((uint16_t)((nl64[i].n_sect << 8) \
				| nl64[i].n_type), flb, file_size), nl64[i].n_value);
	}
	return (list);
}
