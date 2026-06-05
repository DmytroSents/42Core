/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbrusent <dbrusent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/18 15:44:48 by dbrusent          #+#    #+#             */
/*   Updated: 2025/12/17 23:21:40 by dbrusent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	s1_len;
	size_t	s2_len;
	size_t	chr_1st;
	size_t	chr_2nd;
	char	*new_str;

	chr_1st = 0;
	chr_2nd = 0;
	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	new_str = malloc(s1_len + s2_len + 1);
	if (!new_str)
		return (NULL);
	while (chr_1st < s1_len)
	{
		new_str[chr_1st] = s1[chr_1st];
		chr_1st++;
	}
	while (chr_2nd < s2_len)
	{
		new_str[chr_1st + chr_2nd] = s2[chr_2nd];
		chr_2nd++;
	}
	new_str[s1_len + s2_len] = '\0';
	return (new_str);
}
