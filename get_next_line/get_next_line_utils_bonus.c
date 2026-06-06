/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbrusent <dbrusent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/08 16:13:50 by dbrusent          #+#    #+#             */
/*   Updated: 2025/12/03 18:30:19 by dbrusent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

size_t	ft_strlen(const char *str)
{
	size_t	len;

	len = 0;
	while (str[len])
		len++;
	return (len);
}

char	*ft_strchr(const char *str, int c)
{
	char	*chr_ptr;

	if (!str)
		return (NULL);
	chr_ptr = (char *)str;
	while (*chr_ptr && *chr_ptr != (unsigned char)c)
		chr_ptr++;
	if (*chr_ptr == (unsigned char)c)
		return (chr_ptr);
	else
		return (NULL);
}

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t			i;
	unsigned char	*cast_dest;
	unsigned char	*cast_src;

	cast_dest = (unsigned char *)dest;
	cast_src = (unsigned char *)src;
	i = 0;
	if (!dest && !src)
		return (NULL);
	while (i < n)
	{
		cast_dest[i] = cast_src[i];
		i++;
	}
	return (dest);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	s1_len;
	size_t	s2_len;
	char	*new_str;

	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	new_str = malloc(s1_len + s2_len + 1);
	if (!new_str)
		return (NULL);
	ft_memcpy(new_str, s1, s1_len);
	ft_memcpy(new_str + s1_len, s2, s2_len);
	new_str[s1_len + s2_len] = '\0';
	return (new_str);
}

char	*ft_substr(char const *str, size_t start, size_t len)
{
	char	*sub_str;
	size_t	i;
	size_t	src_len;

	i = 0;
	src_len = ft_strlen(str);
	if (start >= src_len)
		len = 0;
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
