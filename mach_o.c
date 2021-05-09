//
// Created by Merrett Narwhal on 5/9/21.
//

#include "nmotool.h"

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
		errors_nm_otool(CORR_BIN);
	if (i == mh->ncmds)
		return (NULL);
	return ((void*)lc);
}

t_list *mach_o(char *flb, size_t file_size, char size_arch)
{
	t_list *list = NULL;
	struct symtab_command	*sc;
//	struct nlist_64			*nl64;
//	struct nlist			*nl;
//	size_t					i;

	if ((sc = (struct symtab_command*)get_symtab(flb, file_size, size_arch)) == NULL)
		return (NULL);
	return list;
}
