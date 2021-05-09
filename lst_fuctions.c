//
// Created by И Б on 09.05.2021.
//

#include "nmotool.h"

void	new_elem_lst(t_lst **head, char *name, char type, size_t offset)
{
	t_lst	*tmp;

	if (!(tmp = *head))
	{
		if (!(*head = malloc(sizeof(t_lst))))
			errors_nm_otool(MALLOC);
		(*head)->data.name = name;
		(*head)->data.type = type;
		(*head)->data.offset = offset;
		(*head)->next = NULL;
		return ;
	}
	while (tmp->next)
		tmp = tmp->next;
	if (!(tmp->next = malloc(sizeof(t_lst))))
		errors_nm_otool(MALLOC);
	tmp->next->data.name = name;
	tmp->next->data.type = type;
	tmp->next->data.offset = offset;
	tmp->next->next = NULL;
	return ;
}