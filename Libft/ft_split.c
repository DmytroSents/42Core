/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbrusent <dbrusent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/18 19:16:44 by dbrusent          #+#    #+#             */
/*   Updated: 2026/06/07 20:42:11 by dbrusent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	free_split(char **str_arr, char flah)
{
	int	i;

	i = 0;
	while (str_arr[i])
	{
		if (str_arr[i])
			free(str_arr[i]);
		i++;
	}
	if (str_arr[i])
		free(str_arr[i]);
	if (flah)
	{
		free(str_arr);
		str_arr = NULL;
	}
}

static int	count_substr(const char *str, char c)
{
	size_t	i;
	int		substrings;

	i = 0;
	substrings = 0;
	while (str[i])
	{
		while (str[i] && str[i] == c)
			i++;
		if (str[i] && str[i] != c)
			substrings++;
		while (str[i] && str[i] != c)
			i++;
	}
	return (substrings);
}

static char	**put_arr_str(char **str_arr, char *sub_str, int amount, int c)
{
	int		i;
	char	*sub_end;

	i = 0;
	sub_end = sub_str;
	while (*sub_end)
	{
		while (*sub_str == c)
			sub_str++;
		sub_end = sub_str;
		while (*sub_end && *sub_end != c)
			sub_end++;
		if (*sub_end == c || sub_end > sub_str)
		{
			str_arr[i] = ft_substr(sub_str, 0, sub_end - sub_str);
			if (!str_arr[i])
				return (free_split(str_arr, amount), NULL);
			sub_str = sub_end;
			i++;
		}
	}
	str_arr[i] = NULL;
	return (str_arr);
}

char	**ft_split(char const *src, char c)
{
	int		amount;
	char	**str_arr;
	char	*sub_str;

	if (src == NULL)
		return (NULL);
	sub_str = (char *)src;
	amount = count_substr(src, c);
	str_arr = (char **)malloc((amount + 1) * sizeof(char *));
	if (!str_arr)
		return (NULL);
	str_arr = put_arr_str(str_arr, sub_str, amount, c);
	return (str_arr);
}
