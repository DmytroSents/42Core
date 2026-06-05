/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   swap_push.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbrusent <dbrusent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/19 20:56:09 by dbrusent          #+#    #+#             */
/*   Updated: 2026/01/19 08:47:18 by dbrusent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../push_header.h"

void	swap_one(t_list **stack, char stk_name)
{
	t_list	*first;
	t_list	*second;

	if (!stack || !*stack || !(*stack)->next)
		return ;
	first = *stack;
	second = first->next;
	first->next = second->next;
	second->next = first;
	*stack = second;
	if (stk_name == 'a')
		write(1, "sa\n", 3);
	else if (stk_name == 'b')
		write(1, "sb\n", 3);
}

void	swap_both(t_list **stack_a, t_list **stack_b)
{
	if (!stack_a || !*stack_a || !(*stack_a)->next
		|| !stack_b || !*stack_b || !(*stack_b)->next)
		return ;
	swap_one(stack_a, 0);
	swap_one(stack_b, 0);
	write(1, "ss\n", 3);
}

void	just_push(t_list **a, t_list **b, char stk_name)
{
	t_list	*tmp;

	tmp = NULL;
	if ((stk_name == 'b' && !a && !(*a)->next)
		|| (stk_name == 'a' && !b && !(*b)->next))
		return ;
	if (stk_name == 'a')
	{
		tmp = *b;
		*b = (*b)->next;
		tmp->next = *a;
		*a = tmp;
		write(1, "pa\n", 3);
	}
	if (stk_name == 'b')
	{
		tmp = *a;
		*a = (*a)->next;
		tmp->next = *b;
		*b = tmp;
		write(1, "pb\n", 3);
	}
}
