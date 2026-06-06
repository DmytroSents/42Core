/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbrusent <dbrusent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/10 17:54:55 by dbrusent          #+#    #+#             */
/*   Updated: 2025/11/01 13:55:55 by dbrusent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char	*cast_dest;
	unsigned char	*cast_src;

	if (dest == src || n == 0)
		return (dest);
	if (!dest && !src)
		return (NULL);
	cast_dest = (unsigned char *) dest;
	cast_src = (unsigned char *) src;
	if (cast_src < cast_dest)
		while (n-- > 0)
			cast_dest[n] = cast_src[n];
	else
		ft_memcpy(dest, src, n);
	return (dest);
}
