/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbrusent <dbrusent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/14 11:18:11 by dbrusent          #+#    #+#             */
/*   Updated: 2026/04/19 11:10:17 by dbrusent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_header.h"

void	ft_perror(int dupa)
{
	ft_print_s_fd(2, "Error\n");
	if (dupa != 0)
		exit(1);
}

int	main(int argc, char *argv[])
{
	t_list	*stk_a;
	t_list	*stk_b;

	stk_b = NULL;
	stk_a = parsing_args(argc, argv);
	if (!stk_a)
		ft_perror(1);
	if (ft_lstsize(stk_a) == 1 || is_itsorted(stk_a))
	{
		ft_lstclear(&stk_a);
		return (0);
	}
	if (ft_lstsize(stk_a) <= 5 && ft_lstsize(stk_a) > 1)
		small_sort(ft_lstsize(stk_a), &stk_a, &stk_b);

	else if (ft_lstsize(stk_a) > 5)
		radix_full(&stk_a, &stk_b);
	ft_lstclear(&stk_a);
	ft_lstclear(&stk_b);
	return (0);
}
//ft_printf("\nAfter_radix:\n");
//ft_print_list(stk_a);
// void	ft_print_list(t_list *t_head)
// {
// 	t_list	*temp;

// 	if (!t_head)
// 		return ;
// 	temp = t_head;
// 	while (temp)
// 	{
// 		write(1, "\n", 1);
// 		ft_printf("Value:_%d\n", temp->value);
// 		ft_printf("Radix:_%d\n", temp->radix);
// 		temp = temp->next;
// 	}
// }
