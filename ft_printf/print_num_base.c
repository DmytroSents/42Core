/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_num_base.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbrusent <dbrusent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 14:03:26 by dbrusent          #+#    #+#             */
/*   Updated: 2025/11/10 17:52:21 by dbrusent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	find_len_base(long ntemp, int base)
{
	int	lnght;

	lnght = 1;
	while (ntemp >= base)
	{
		ntemp = ntemp / base;
		lnght++;
	}
	return (lnght);
}

int	print_num_base(int num, int base)
{
	char	*symbol;
	char	itoa[12];
	long	tmp;
	int		leng;
	int		sign;

	sign = 0;
	symbol = "0123456789abcdef";
	tmp = (long)num;
	if (num < 0)
	{
		itoa[sign++] = '-';
		tmp = -1 * tmp;
	}
	leng = find_len_base(tmp, base) + sign;
	num = leng;
	itoa[leng - 1] = '\0';
	while (leng-- > sign)
	{
		itoa[leng] = symbol[tmp % base];
		tmp = tmp / base;
	}
	return (write(1, itoa, num));
}
