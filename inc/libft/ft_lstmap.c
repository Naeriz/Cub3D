/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sionow <sionow@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 18:55:09 by sionow            #+#    #+#             */
/*   Updated: 2025/12/02 02:58:51 by sionow           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*lstc;
	t_list	*temp;

	if (!lst || !f || !del)
		return (NULL);
	temp = ft_lstnew(f(lst->content));
	if (!temp)
		return (NULL);
	lstc = temp;
	lst = lst->next;
	while (lst)
	{
		temp->next = ft_lstnew(f(lst->content));
		if (!temp->next)
		{
			ft_lstclear(&lstc, del);
			return (NULL);
		}
		temp = temp->next;
		lst = lst->next;
	}
	temp->next = NULL;
	return (lstc);
}
