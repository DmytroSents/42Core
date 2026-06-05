/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleaning_service.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbrusent <dbrusent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/01 11:59:35 by dbrusent          #+#    #+#             */
/*   Updated: 2025/12/24 12:11:22 by dbrusent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_free_all(char **str_arr, t_list **lst_start, int i, int fflag);

void	ft_lstclear(t_list **lst)
{
	t_list	*temp;
	t_list	*current;

	if (!lst || !*lst)
		return ;
	current = *lst;
	while (current != NULL)
	{
		temp = current->next;
		free(current);
		current = temp;
	}
	*lst = NULL;
}

t_list	*ft_free_all(char **str_arr, t_list **lst_start, int i, int fflag)
{
	ft_lstclear(lst_start);
	if (fflag != 0)
		ft_free_arr(str_arr, i);
	return (NULL);
}
