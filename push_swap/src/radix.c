/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   radix.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbrusent <dbrusent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/24 12:55:40 by dbrusent          #+#    #+#             */
/*   Updated: 2026/01/19 08:46:39 by dbrusent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../push_header.h"

static void	pre_radix(t_list *head)
{
	t_list	*current;

	current = head;
	while (current)
	{
		current->radix = -1;
		current = current->next;
	}
}

void	ft_put_radix(t_list *head)
{
	int		radix_counter;
	t_list	*min_n;
	t_list	*curren;

	if (!head)
		return ;
	pre_radix(head);
	radix_counter = 0;
	while (1)
	{
		min_n = NULL;
		curren = head;
		while (curren)
		{
			if (curren->radix == -1 && (!min_n || curren->value < min_n->value))
				min_n = curren;
			curren = curren->next;
		}
		if (!min_n)
			break ;
		min_n->radix = radix_counter++;
	}
}

static void	radix_once(t_list **a, t_list **b, int i)
{
	int		moved;
	int		size;

	moved = 0;
	size = ft_lstsize(*a);
	while (size--)
	{
		if (((*a)->radix >> i) & 1)
			rotate_one(a, 'a');
		else
		{
			just_push(a, b, 'b');
			++moved;
		}
	}
	while (moved--)
		just_push(a, b, 'a');
}

void	radix_full(t_list **a, t_list **b)
{
	int		max;
	int		bits;
	int		i;

	if (!a || !*a)
		return ;
	ft_put_radix(*a);
	max = ft_lstsize(*a) - 1;
	bits = 0;
	while (max > 0 && ++bits)
		max = max >> 1;
	i = -1;
	while (++i < bits)
		radix_once(a, b, i);
}
