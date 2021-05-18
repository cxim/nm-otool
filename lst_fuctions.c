#include "nmotool.h"

void	free_lst(t_lst *lst)
{
	t_lst	*tmp;

	while (lst)
	{
		tmp = lst;
		lst = lst->next;
		free(tmp);
	}
}

int	is_sorted(t_lst *lst, t_flags flags)
{
	while (lst && lst->next)
	{
		if (flags.flag_reverse != 1 && ft_strcmp(lst->data.name, lst->next->data.name) > 0)
			return (0);
		else if (flags.flag_reverse == 1 && ft_strcmp(lst->data.name, lst->next->data.name) < 0)
			return (0);
		lst = lst->next;
	}
	return (1);
}

t_lst	*sorting_lst(t_lst *head, t_flags flags)
{
	t_data	tmp;
	t_lst	*lst;

	while (head && !is_sorted(head, flags))
	{
		lst = head;
		while (lst->next)
		{
			if (ft_strcmp(lst->data.name, lst->next->data.name)  > 0 && flags.flag_reverse != 1)
			{
				tmp = lst->data;
				lst->data = lst->next->data;
				lst->next->data = tmp;
			}
			else if (ft_strcmp(lst->data.name, lst->next->data.name ) < 0 && flags.flag_reverse == 1)
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

	tmp = *head;
	if (!tmp)
	{
		*head = malloc(sizeof(t_lst));
		if (!*head)
			errors_nm_otool(MALLOC);
		(*head)->data.name = name;
		(*head)->data.type = type;
		(*head)->data.offset = offset;
		(*head)->next = NULL;
		return ;
	}
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = malloc(sizeof(t_lst));
	if (!tmp->next)
		errors_nm_otool(MALLOC);
	tmp->next->data.name = name;
	tmp->next->data.type = type;
	tmp->next->data.offset = offset;
	tmp->next->next = NULL;
}
