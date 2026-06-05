/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_itsorted.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbrusent <dbrusent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/19 18:24:59 by dbrusent          #+#    #+#             */
/*   Updated: 2026/01/19 10:28:47 by dbrusent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../push_header.h"

int	is_itsorted(t_list *head)
{
	t_list	*temp[2];

	temp[0] = NULL;
	if (!head)
		return (-1);
	temp[0] = head;
	while (temp[0] && temp[0]->next)
	{
		temp[1] = temp[0]->next;
		if (temp[0]->value > temp[1]->value)
			return (0);
		temp[0] = temp[0]->next;
		temp[1] = temp[1]->next;
	}
	return (1);
}
