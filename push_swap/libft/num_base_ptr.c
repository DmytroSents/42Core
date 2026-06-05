/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   num_base_ptr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbrusent <dbrusent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 14:03:26 by dbrusent          #+#    #+#             */
/*   Updated: 2025/12/24 12:13:12 by dbrusent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	find_len_base(long ntemp, int base)
{
	int	lnght;

	lnght = 1;
	if (ntemp < 0)
	{
		lnght++;
		ntemp = ntemp * (-1);
	}
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
	while (leng > sign)
	{
		leng = leng - 1;
		itoa[leng] = symbol[tmp % base];
		tmp = tmp / base;
	}
	return (write(1, itoa, num));
}

int	print_unsigned_base(unsigned int u_num, int base, char fmt_c)
{
	char	*symbol;
	char	itoa[12];
	long	tmp;
	int		len;

	symbol = "0123456789abcdef";
	if (fmt_c == 'X')
		symbol = "0123456789ABCDEF";
	tmp = (long)u_num;
	len = find_len_base(tmp, base);
	u_num = len;
	while (--len >= 0)
	{
		itoa[len] = symbol[tmp % base];
		tmp = tmp / base;
	}
	return (write(1, itoa, u_num));
}

int	ft_print_ptr(void *addres)
{
	unsigned long		temp[2];
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
