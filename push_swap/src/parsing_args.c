/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_args.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbrusent <dbrusent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/14 11:18:48 by dbrusent          #+#    #+#             */
/*   Updated: 2026/01/19 08:47:06 by dbrusent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../push_header.h"

static int		are_they_unique(t_list *head);
static int		validate_one_s(char *sub_str);
static t_list	*validate_array(char *str_arr[], int fflag);
static t_list	*ft_int_to_lst(char *numeric_s, int index, int i);

t_list	*parsing_args(int argc, char *argv[])
{
	t_list	*rtrn_lst;
	char	**split_tmp;

	split_tmp = NULL;
	rtrn_lst = NULL;
	if (argc == 1)
		exit(0);
	if (argc == 2)
	{
		split_tmp = ft_split(argv[1], ' ');
		if (!split_tmp)
			ft_perror(1);
		rtrn_lst = validate_array(split_tmp, 'S');
	}
	else if (argc > 2)
		rtrn_lst = validate_array(argv + 1, 0);
	if (!rtrn_lst || are_they_unique(rtrn_lst) < 0)
	{
		ft_lstclear(&rtrn_lst);
		ft_perror(1);
	}
	return (rtrn_lst);
}

static t_list	*validate_array(char *str_arr[], int fflag)
{
	int		i;
	t_list	*t_temp;
	t_list	*new_list;

	i = -1;
	new_list = NULL;
	while (str_arr[++i])
	{
		if (validate_one_s(str_arr[i]) < 0 && fflag)
			return (ft_free_arr(str_arr, i), NULL);
		if (validate_one_s(str_arr[i]) < 0 && !fflag)
			return (NULL);
	}
	i = 0;
	while (str_arr[i])
	{
		t_temp = ft_int_to_lst(str_arr[i], i, 0);
		if (!t_temp)
			return (ft_free_all(str_arr, &new_list, i, fflag));
		ft_lstadd_back(&new_list, t_temp);
		i++;
	}
	if (fflag == 'S')
		ft_free_arr(str_arr, i);
	return (new_list);
}

static t_list	*ft_int_to_lst(char *numeric_s, int index, int i)
{
	int		sign;
	t_list	*t_temp;
	long	temp_num;

	sign = 1;
	t_temp = NULL;
	temp_num = 0;
	if (numeric_s[i] == '-')
		sign = -1;
	if (numeric_s[i] == '+' || numeric_s[i] == '-')
		i++;
	while (numeric_s[i])
	{
		temp_num = (temp_num * 10) + (numeric_s[i] - '0');
		if (temp_num > 2147483648)
			break ;
		i++;
	}
	temp_num = temp_num * sign;
	if (temp_num > INT_MAX || temp_num < INT_MIN)
		return (NULL);
	t_temp = ft_lstnew(temp_num, index);
	if (!t_temp)
		return (NULL);
	return (t_temp);
}

static int	validate_one_s(char *sub_str)
{
	size_t	j;
	size_t	leng;

	j = 0;
	leng = ft_strlen(sub_str);
	while (sub_str[j])
	{
		if (!ft_strchr("-0123456789+", sub_str[j]))
			return (-1);
		if ((leng == 1 && *sub_str == '-')
			|| (leng == 1 && *sub_str == '+')
			|| (sub_str[j] == '-' && j != 0)
			|| (sub_str[j] == '+' && j != 0))
			return (-1);
		j++;
	}
	return (11);
}

static int	are_they_unique(t_list *head)
{
	t_list	*l_next;
	t_list	*current;

	if (!head)
		return (-1);
	l_next = head->next;
	while (l_next)
	{
		current = head;
		while (current != l_next)
		{
			if (current->value == l_next->value)
				return (-1);
			current = current->next;
		}
		l_next = l_next->next;
	}
	return (0);
}
