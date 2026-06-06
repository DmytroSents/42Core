/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbrusent <dbrusent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 17:59:02 by dbrusent          #+#    #+#             */
/*   Updated: 2025/10/25 19:25:23 by dbrusent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	little_len;

	i = 0;
	if (!little[i] || little == big)
		return ((char *)big);
	if (len == 0)
		return (NULL);
	little_len = ft_strlen(little);
	while (big[i] && i < len)
	{
		if (big[i] == little[0] && (len - i) >= little_len)
		{
			if (ft_strncmp((big + i), little, little_len) == 0)
				return ((char *)big + i);
		}
		i++;
	}
	return (NULL);
}
