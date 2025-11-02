/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 17:48:43 by marvin            #+#    #+#             */
/*   Updated: 2025/04/05 17:48:43 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new_lst;
	t_list	*new_node;
	t_list	*current;

	new_lst = NULL;
	new_node = NULL;
	current = lst;
	if (!lst)
		return (NULL);
	while (current)
	{
		new_node = ft_lstnew(f(current->content));
		if (!new_node)
			ft_lstclear(&new_node, del);
		else
			ft_lstadd_back(&new_lst, new_node);
		current = current->next;
	}
	return (new_lst);
}
