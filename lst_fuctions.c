//
// Created by И Б on 09.05.2021.
//

#include "nmotool.h"

int		is_sorted(t_lst *lst)
{
	while (lst && lst->next)
	{
		if (ft_strcmp(lst->data.name, lst->next->data.name) > 0)
			return (0);
		lst = lst->next;
	}
	return (1);
}

t_lst	*sorting_lst(t_lst *head)
{
	t_data	tmp;
	t_lst	*lst;

	while (head && !is_sorted(head))
	{
		lst = head;
		while (lst->next)
		{
			if (ft_strcmp(lst->data.name, lst->next->data.name) > 0)
			{
				tmp = lst->data;
				lst->data = lst->next->data;
				lst->next->data = tmp;
			}
			lst = lst->next;
		}
	}
	return (head);
}

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