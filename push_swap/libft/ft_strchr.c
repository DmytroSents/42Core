/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbrusent <dbrusent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 15:02:06 by dbrusent          #+#    #+#             */
/*   Updated: 2025/12/17 16:52:03 by dbrusent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *str, int c)
{
	char	*chr_ptr;

	chr_ptr = (char *)str;
	while (*chr_ptr && *chr_ptr != (unsigned char)c)
		chr_ptr++;
	if (*chr_ptr == (unsigned char)c)
		return (chr_ptr);
	else
		return (NULL);
}
