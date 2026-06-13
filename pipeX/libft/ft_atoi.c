/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbrusent <dbrusent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 14:45:41 by dbrusent          #+#    #+#             */
/*   Updated: 2025/10/18 15:55:50 by dbrusent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>

static int	ft_isspace(char c)
{
	return (((c >= '\t' && c <= '\r' ) || c == ' '));
}

int	ft_atoi(const char *nptr)
{
	int				i;
	int				sign;
	long			temp;

	i = 0;
	sign = 1;
	temp = 0;
	while (ft_isspace(nptr[i]) != 0)
		i++;
	if (nptr[i] == '-')
		sign = sign * (-1);
	if (nptr[i] == '+' || nptr[i] == '-')
		i++;
	while ((nptr[i] >= '0' && nptr[i] <= '9'))
	{
		if ((temp > INT_MAX) || (sign * temp < INT_MIN))
			return (0);
		temp = (temp * 10) + (nptr[i] - '0');
		i++;
	}
	return (temp * sign);
}
