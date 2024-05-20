/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_lst.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lewlee <lewlee@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 15:36:00 by lewlee            #+#    #+#             */
/*   Updated: 2024/05/19 15:36:00 by lewlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"


t_file_lst	*create_filenode(char *s) {
	t_file_lst *res = malloc(sizeof(t_file_lst) * 1);
	if (!res)
		return (NULL);
	res->s = s;
	res->next = NULL;
	res->prev = NULL;
	return (res);
}

int	ft_file_lstsize(t_file_lst *lst)
{
	int		i;

	i = 0;
	if (!lst)
		return (0);
	while (lst)
	{
		lst = lst->next;
		i++;
	}
	return (i);
}

t_file_lst	*ft_file_lstlast(t_file_lst *lst)
{
	t_file_lst	*temp;

	temp = lst;
	if (!lst)
		return (NULL);
	while (temp->next)
		temp = temp->next;
	return (temp);
}

void	ft_file_lstadd_back(t_file_lst **lst, t_file_lst *new)
{
	t_file_lst	*tmp;
	if (!new)
		return ;
	if (!*lst)
	{
		*lst = new;
		return ;
	}
	tmp = ft_file_lstlast(*lst);
	tmp->next = new;
	new->prev = tmp;
}

void	ft_file_lstclear(t_file_lst **lst, void (*del)(void*))
{
	t_file_lst	*i;

	if (!lst || !*lst || !del)
		return ;
	while (*lst)
	{
		i = *lst;
		*lst = (*lst)->next;
		del(i->s);
		free(i);
	}
	*lst = NULL;
}