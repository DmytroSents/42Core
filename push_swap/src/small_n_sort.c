/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   small_n_sort.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbrusent <dbrusent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/24 12:11:33 by dbrusent          #+#    #+#             */
/*   Updated: 2026/01/19 08:47:15 by dbrusent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../push_header.h"

static int	find_min(t_list **stack);
static void	sort_four(t_list **a, t_list **b);
static void	sort_five(t_list **a, t_list **b);
static void	sort_three(int i, t_list **stack, char stk_name);

void	small_sort(int num_elems, t_list **stk_a, t_list **stk_b)
{
	if (!num_elems || !stk_a || !*stk_a || is_itsorted(*stk_a))
		return ;
	if (num_elems == 3)
		sort_three(0, stk_a, 'a');
	else if (num_elems == 4)
		sort_four(stk_a, stk_b);
	else if (num_elems == 5)
		sort_five(stk_a, stk_b);
	else if (num_elems == 2)
		swap_one(stk_a, 'a');
}

static void	sort_three(int i, t_list **stack, char stk_name)
{
	int		si[3];
	t_list	*temp;

	temp = *stack;
	while (temp && i < 3)
	{
		si[i++] = temp->value;
		temp = temp->next;
	}
	if (si[0] < si[1] && si[0] < si[2] && si[1] > si[2])
	{
		swap_one(stack, stk_name);
		rotate_one(stack, stk_name);
	}
	if (si[0] > si[1] && si[0] < si[2] && si[1] < si[2])
		swap_one(stack, stk_name);
	if (si[0] < si[1] && si[0] > si[2] && si[1] > si[2])
		rev_rotate_one(stack, stk_name);
	if (si[0] > si[1] && si[0] > si[2] && si[1] < si[2])
		rotate_one(stack, stk_name);
	if (si[0] > si[1] && si[0] > si[2] && si[1] > si[2])
	{
		swap_one(stack, stk_name);
		rev_rotate_one(stack, stk_name);
	}
}

static void	sort_four(t_list **a, t_list **b)
{
	int	min;

	min = find_min(a);
	if (min == 1)
		swap_one(a, 'a');
	while (min >= 2 && min <= 3)
	{
		rev_rotate_one(a, 'a');
		min++;
	}
	just_push(a, b, 'b');
	sort_three(0, a, 'a');
	just_push(a, b, 'a');
}

static void	sort_five(t_list **a, t_list **b)
{
	int	min;

	min = find_min(a);
	if (min == 1)
		swap_one(a, 'a');
	while (min >= 2 && min <= 4)
	{
		rev_rotate_one(a, 'a');
		min++;
	}
	just_push(a, b, 'b');
	sort_four(a, b);
	just_push(a, b, 'a');
}

static int	find_min(t_list **stack)
{
	int		pos;
	int		min;
	int		min_pos;
	t_list	*node;

	pos = 0;
	min = INT_MAX;
	min_pos = -1;
	node = *stack;
	while (node)
	{
		if (node->value < min)
		{
			min = node->value;
			min_pos = pos;
		}
		pos++;
		node = node->next;
	}
	if (min_pos < 0)
		return (0);
	return (min_pos);
}

// 1 2 3 --sorted
// 1 3 2 --2 moves
// 2 1 3 --1 move
// 2 3 1 --1 move
// 3 1 2 --1 move
// 3 2 1 --n-1 moves
