/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbrusent <dbrusent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/18 19:16:44 by dbrusent          #+#    #+#             */
/*   Updated: 2025/12/18 04:32:10 by dbrusent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_free_arr(char **str_arr, int current)
{
	int	f;

	f = 0;
	while (str_arr[f] && f <= current)
	{
		if (str_arr[f] != NULL)
			free(str_arr[f]);
		str_arr[f] = NULL;
		f++;
	}
	str_arr[f] = NULL;
	free(str_arr);
	str_arr = NULL;
	return (str_arr);
}

int	ft_count_substr(const char *str, char c)
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

static char	**put_arr_str(char **str_arr, char *sub_str, int c)
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
			str_arr[i] = ft_substr(sub_str, 0, (size_t)(sub_end - sub_str));
			if (!str_arr[i])
				return (ft_free_arr(str_arr, i));
			sub_str = sub_end;
			i++;
		}
	}
	str_arr[i] = NULL;
	return (str_arr);
}

char	**ft_split(char const *src, char c)
{
	int		i;
	int		amount;
	char	**str_arr;
	char	*src_str;

	i = 0;
	if (src == NULL)
		return (NULL);
	src_str = (char *)src;
	amount = ft_count_substr(src, c);
	str_arr = (char **)malloc((amount + 1) * sizeof(char *));
	if (!str_arr)
		return (NULL);
	while (i <= amount)
	{
		str_arr[i] = NULL;
		i++;
	}
	str_arr = put_arr_str(str_arr, src_str, c);
	return (str_arr);
}
