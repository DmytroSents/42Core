/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbrusent <dbrusent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/18 16:59:26 by dbrusent          #+#    #+#             */
/*   Updated: 2026/06/06 11:39:05 by dbrusent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *str, char const *set)
{
	size_t	str_len;
	char	*new_str;
	size_t	start;
	size_t	s_end;

	start = 0;
	s_end = 0;
	if (!*set)
		return (ft_strdup(str));
	if (!*str)
		return (ft_strdup(""));
	str_len = ft_strlen(str);
	while (ft_strchr(set, str[start]) && str[start])
		start++;
	while (str_len > s_end && ft_strchr(set, str[str_len - s_end]))
		s_end++;
	if (start + --s_end >= str_len)
		return (ft_strdup(""));
	str_len = ft_strlen(str + start) - s_end;
	new_str = malloc(str_len + 1);
	if (!new_str)
		return (NULL);
	ft_memcpy(new_str, str + start, str_len);
	new_str[str_len] = '\0';
	return (new_str);
}
