/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbrusent <dbrusent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 20:42:41 by dbrusent          #+#    #+#             */
/*   Updated: 2025/12/21 21:59:11 by dbrusent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	int		numb;

	numb = 0;
	if (!lst)
		return (0);
	while (lst->next != NULL)
	{
		lst = lst->next;
		numb++;
	}
	if (lst->next == NULL)
		numb++;
	return (numb);
}
