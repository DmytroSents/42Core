/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_ptr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbrusent <dbrusent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 18:54:13 by dbrusent          #+#    #+#             */
/*   Updated: 2025/11/10 18:04:56 by dbrusent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_print_ptr(void *addres)
{
	unsigned long long	temp[2];
	char				itoa[22];
	int					i[3];
	char				*symbol;

	i[1] = 1;
	i[2] = 0;
	symbol = "0123456789abcdef";
	if (addres == NULL)
		return (write(1, "(nil)", 5));
	temp[0] = (unsigned long long) addres;
	i[2] = i[2] + write(1, "0x", 2);
	temp[1] = temp[0];
	while (temp[0] >= 16)
	{
		temp[0] = temp[0] / 16;
		i[1]++;
	}
	i[0] = i[1];
	while (i[1]-- > 0)
	{
		itoa[i[1]] = symbol[temp[1] % 16];
		temp[1] = temp[1] / 16;
	}
	return (i[2] + write(1, itoa, i[0]));
}
