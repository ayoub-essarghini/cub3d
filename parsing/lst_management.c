/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_management.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msaadidi <msaadidi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 17:47:18 by msaadidi          #+#    #+#             */
/*   Updated: 2024/08/10 18:08:05 by msaadidi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

t_lst	*ft_lstlast(t_lst *lst)
{
	while (lst && lst->next)
		lst = lst->next;
	return (lst);
}

t_lst	*lst_new(char *row)
{
	t_lst	*lst;

	lst = malloc(sizeof(t_lst));
	if (!lst)
	{
		free(lst);
		return (NULL);
	}
	lst->row = ft_strdup(row);
	lst->row_len = ft_strlen(row);
	lst->next = NULL;
	return (lst);
}

void	ft_lstadd_back(t_lst **lst, t_lst *new)
{
	t_lst	*last;

	if (!lst || !new)
		return ;
	if (!(*lst))
		*lst = new;
	else
	{
		last = ft_lstlast(*lst);
		last->next = new;
	}
}

int	ft_lstsize(t_lst *lst)
{
	int	i;

	i = 0;
	while (lst)
	{
		i++;
		lst = lst->next;
	}
	return (i);
}

void	ft_lstclear(t_lst **lst)
{
	t_lst	*curr;
	t_lst	*next;

	if (!lst || !(*lst))
		return ;
	curr = *lst;
	while (curr != NULL)
	{
		next = curr->next;
		free(curr->row);
		free(curr);
		curr = next;
	}
	*lst = NULL;
}
