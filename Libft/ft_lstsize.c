/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbrusent <dbrusent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 20:42:41 by dbrusent          #+#    #+#             */
/*   Updated: 2025/10/27 20:58:12 by dbrusent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	int		numb;
	t_list	*temp;

	temp = lst;
	numb = 0;
	if (!lst)
		return (0);
	while (temp->next != NULL)
	{
		temp = temp->next;
		numb++;
	}
	if (temp->next == NULL)
		numb++;
	return (numb);
}
