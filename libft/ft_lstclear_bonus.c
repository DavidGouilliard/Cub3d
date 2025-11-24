/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagouill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 20:51:04 by dagouill          #+#    #+#             */
/*   Updated: 2024/11/13 20:54:10 by dagouill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void
*))
{
	t_list	*p;

	if (!(*lst) || !del)
		return ;
	p = NULL;
	while (*lst)
	{
		p = (*lst)->next;
		(*del)((*lst)->content);
		if (*lst)
			free(*lst);
		*lst = p;
	}
	*lst = NULL;
}
