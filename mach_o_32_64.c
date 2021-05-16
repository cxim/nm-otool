#include "nmotool.h"

char	*check_part_segment_64(void *addr, size_t *j, char n)
{
	struct section_64	*sect_64;
	size_t				i;

	i = 0;
	sect_64 = (void *)(addr + sizeof(struct segment_command_64));
	while (i < *((unsigned int *)((void *)addr + \
		(int)(&((struct segment_command_64 *)(0x0))->nsects))))
	{
		if (n == (char)*j)
			return (sect_64->sectname);
		sect_64 += 1;
		i += 1;
		*j += 1;
	}
	return (NULL);
}

char	*check_part_segment(void *addr, size_t *j, char n)
{
	struct section		*sect_32;
	size_t				i;

	i = 0;
	sect_32 = (void *)(addr + sizeof(struct segment_command));
	while (i < *((unsigned int *)((void *)addr + \
		(int)(&((struct segment_command *)(0x0))->nsects))))
	{
		if (n == (char)*j)
			return (sect_32->sectname);
		sect_32 += 1;
		i += 1;
		*j += 1;
	}
	return (NULL);
}
