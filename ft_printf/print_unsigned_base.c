/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_unsigned_base.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbrusent <dbrusent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 14:17:22 by dbrusent          #+#    #+#             */
/*   Updated: 2025/11/10 17:59:15 by dbrusent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

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
