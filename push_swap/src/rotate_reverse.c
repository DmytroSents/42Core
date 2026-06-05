/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate_reverse.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbrusent <dbrusent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/21 17:55:50 by dbrusent          #+#    #+#             */
/*   Updated: 2026/01/19 08:47:11 by dbrusent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../push_header.h"

void	rotate_one(t_list **head, char stack_name)
{
	t_list	*last;
	t_list	*first;

	if (!head || !*head || !(*head)->next)
		return ;
	first = *head;
	*head = first->next;
	last = *head;
	while (last->next)
		last = last->next;
	last->next = first;
	first->next = NULL;
	if (stack_name == 'a')
		write(1, "ra\n", 3);
	else if (stack_name == 'b')
		write(1, "rb\n", 3);
}

void	rotate_both(t_list **a, t_list **b)
{
	if (!a || !b || !*a || !*b || !(*a)->next || !(*b)->next)
		return ;
	rotate_one(a, 0);
	rotate_one(b, 0);
	write(1, "rr\n", 3);
}

void	rev_rotate_one(t_list **head, char stack_name)
{
	t_list	*last;
	t_list	*pre_last;

	if (!head || !(*head)->next)
		return ;
	last = *head;
	while (last->next)
	{
		pre_last = last;
		last = last->next;
	}
	last->next = *head;
	pre_last->next = NULL;
	*head = last;
	if (stack_name == 'a')
		write(1, "rra\n", 4);
	else if (stack_name == 'b')
		write(1, "rrb\n", 4);
}

void	rev_rotate_both(t_list **a, t_list **b)
{
	if (!a || !b || !*a || !*b || !(*a)->next || !(*b)->next)
		return ;
	rev_rotate_one(a, 0);
	rev_rotate_one(b, 0);
	write(1, "rrr\n", 4);
}
