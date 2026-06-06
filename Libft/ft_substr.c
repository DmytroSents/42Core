/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbrusent <dbrusent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/18 14:31:34 by dbrusent          #+#    #+#             */
/*   Updated: 2025/10/27 20:11:10 by dbrusent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *str, unsigned int start, size_t len)
{
	char	*sub_str;
	size_t	i;
	size_t	src_len;

	i = 0;
	src_len = ft_strlen(str);
	if (start >= src_len)
		return (ft_strdup(""));
	if (start + len > src_len)
		len = src_len - start;
	sub_str = malloc(len + 1);
	if (!sub_str)
		return (NULL);
	while (str[i] != '\0' && i < len)
	{
		sub_str[i] = str[start + i];
		i++;
	}
	sub_str[i] = '\0';
	return (sub_str);
}
