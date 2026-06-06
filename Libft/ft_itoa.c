/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbrusent <dbrusent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/18 22:46:25 by dbrusent          #+#    #+#             */
/*   Updated: 2025/10/27 16:21:53 by dbrusent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	find_lenght(long num)
{
	int	i;

	i = 1;
	if (num < 0)
	{
		num = -num;
		i++;
	}
	while (num >= 10)
	{
		num = num / 10;
		i++;
	}
	return (i);
}

char	*ft_itoa(int n)
{
	int		str_len;
	char	*str;
	long	num;

	num = n;
	str_len = find_lenght(num);
	str = malloc(str_len + 1);
	if (!str)
		return (NULL);
	if (num < 0)
		num = -num;
	str[str_len] = '\0';
	while (str_len-- > 0)
	{
		str[str_len] = num % 10 + '0';
		num = num / 10;
	}
	if (n < 0)
		str[0] = '-';
	return (str);
}
