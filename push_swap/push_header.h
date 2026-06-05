/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_header.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbrusent <dbrusent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/14 11:13:29 by dbrusent          #+#    #+#             */
/*   Updated: 2026/01/19 06:41:38 by dbrusent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_HEADER_H
# define PUSH_HEADER_H

# include "./libft/libft.h"
# include <stdio.h>

void	ft_perror(int dupa);
int		is_itsorted(t_list *head);
int		main(int argc, char *argv[]);

t_list	*parsing_args(int argc, char *argv[]);

	/*_Operation functions_*/
void	swap_one(t_list **stack, char stk_name);
void	swap_both(t_list **stack_a, t_list **stack_b);
void	just_push(t_list **a, t_list **b, char stk_name);
void	rotate_one(t_list **head, char stack_name);
void	rotate_both(t_list **a, t_list **b);
void	rev_rotate_one(t_list **head, char stack_name);
void	rev_rotate_both(t_list **a, t_list **b);

	/*_Sorting happens here_*/
void	small_sort(int num_elems, t_list **stk_a, t_list **stk_b);

void	ft_put_radix(t_list *head);
void	radix_full(t_list **stk_a, t_list **stk_b);

#endif
