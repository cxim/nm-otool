//
// Created by Merrett Narwhal on 5/9/21.
//

#include "nmotool.h"

#define NSECTS_64 (int)(&((struct segment_command_64*)(0x0))->nsects)
#define NSECTS_32 (int)(&((struct segment_command*)(0x0))->nsects)
#define HDR_NCMDS (int)(&((struct mach_header*)(0x0))->ncmds)


char	*check_part_segment(void *addr, size_t *j, char arch, char n)
{
	struct section_64	*sect_64;
	struct section		*sect_32;
	size_t				i;

	i = 0;
	sect_32 = (void*)(addr + (arch == 64 ? sizeof(struct segment_command_64) :
							  sizeof(struct segment_command)));
	sect_64 = (void*)sect_32;
	while (i < *((unsigned int*)((void*)addr +
								 (arch == 64 ? NSECTS_64 : NSECTS_32))))
	{
		if (n == (char)*j)
			return (arch == 64 ? sect_64->sectname : sect_32->sectname);
		sect_32 += 1;
		sect_64 += 1;
		i += 1;
		*j += 1;
	}
	return (NULL);
}

char	*get_sect_tab(char *flb, size_t file_size, char arch_size, char n)
{
	struct load_command		*lc;
	unsigned int			index;
	size_t					i;
	char					*rslt;
	size_t					j;

	index = 0;
	j = 1;
	lc = (void*)flb + (arch_size == 32 ? sizeof(struct mach_header) :
					   sizeof(struct mach_header_64));
	while (index++ < *((unsigned int*)(flb + HDR_NCMDS)) &&
		   (void*)lc < file_size + (void*)flb)
	{
		if (lc->cmd == (arch_size == 64 ? LC_SEGMENT_64 : LC_SEGMENT) && !(i = 0))
		{
			if ((rslt = check_part_segment((void*)lc, &j, arch_size, n)))
				return (rslt);
		}
		lc = (void*)lc + lc->cmdsize;
	}
	return (NULL);
}

char	type_part_two(char *flb, size_t file_size, char arch_size, char n)
{
	char *str;

	if ((str = get_sect_tab(flb, file_size, arch_size, n)) == NULL)
		return ('S');
	if (ft_strcmp(str, "__text") == 0)
		return ('T');
	else if (ft_strcmp(str, "__bss") == 0)
		return ('B');
	else if (ft_strcmp(str, "__data") == 0)
		return ('D');
	return ('S');
}

char 	type(uint16_t section, char *flb, size_t file_size, char arch_size)
{
	uint8_t sec;
	uint8_t type_section;
	char	ret;

	type_section = section;
	sec = section >> 8;
	if ((type_section & N_TYPE) == N_UNDF && sec == 0)
		ret = 'U';
	else if ((type_section & N_TYPE) == N_ABS)
		ret = 'A';
	else if ((type_section & N_TYPE) == N_INDR)
		ret = 'I';
	else if ((type_section & N_TYPE) == N_SECT)
		ret = type_part_two(flb, file_size, arch_size, sec);
	else
		return ('?');
	return ((type_section & N_EXT) ? ret : ret + 32);
}

void *get_symtab(char *flb, size_t file_size, char size_arch)
{
	size_t		i;
	struct load_command		*lc;
	struct mach_header		*mh;

	mh = (struct mach_header*)flb;
	i = 0;

	lc = (void*)flb + (size_arch == 32 ? sizeof(struct mach_header) :
					   sizeof(struct mach_header_64));
	while (i < mh->ncmds && (void*)lc < file_size + (void*)flb)
	{
		if (lc->cmd == LC_SYMTAB)
			break;
		lc = (void*)lc + lc->cmdsize;
		i++;
	}
	if ((void*)lc > file_size + (void*)flb)
	{
		errors_nm_otool(CORR_BIN);
		return (NULL);
	}
	if (i == mh->ncmds)
		return (NULL);
	return ((void*)lc);
}

t_lst *mach_o(char *flb, size_t file_size, char size_arch)
{
	t_lst *list;
	struct symtab_command	*sc;
	struct nlist_64			*nl64;
	struct nlist			*nl;
	size_t					i;

	if ((sc = (struct symtab_command*)get_symtab(flb, file_size, size_arch)) == NULL)
		return (NULL);
	i = -1;
	list = NULL;
	nl = (void*)flb + sc->symoff;
	nl64 = (void*)flb + sc->symoff;

	while (++i < sc->nsyms)
		if (size_arch == 64 && (nl64[i].n_type == 1 || nl64[i].n_type == 14
								|| nl64[i].n_type == 15 || nl64[i].n_type == 0
								|| nl64[i].n_type == 3 || nl64[i].n_type == 30))
			new_elem_lst(&list, (void*)flb + sc->stroff + nl64[i].n_un.n_strx,
					 type((uint16_t)((nl64[i].n_sect << 8) | nl64[i].n_type),
					 		flb, file_size, size_arch), nl64[i].n_value);
		else if (size_arch == 32 && (nl[i].n_type == 1 || nl[i].n_type == 14
								|| nl[i].n_type == 15 || nl[i].n_type == 0
								|| nl[i].n_type == 3 || nl[i].n_type == 30))
			new_elem_lst(&list, (void*)flb + sc->stroff + nl[i].n_un.n_strx,
					 type((uint16_t)((nl[i].n_sect << 8) | nl[i].n_type),
					 		flb, file_size, size_arch), nl[i].n_value);
	return list;
}
