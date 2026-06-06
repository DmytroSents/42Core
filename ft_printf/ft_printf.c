/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbrusent <dbrusent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 12:32:44 by dbrusent          #+#    #+#             */
/*   Updated: 2025/11/10 22:42:28 by dbrusent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
//#include <stdio.h>

char	ft_strchr(char *str, int c)
{
	while (*str && *str != (unsigned char)c)
		str++;
	if (*str == (unsigned char)c)
		return (*str);
	else
		return (0);
}

int	val_spc(char *fmt, int *err_flag)
{
	if (*fmt == '%' && *(fmt + 1) == '\0' && !(*err_flag))
		return (-1);
	if (*fmt == '%' && *(fmt + 1) && !ft_strchr("sdiupxXc%", *(fmt + 1)))
	{
		(*err_flag)++;
		return (0);
	}
	return (ft_strchr("sdiupxXc%", *(fmt + 1)));
}

int	ft_print_s(char *str)
{
	int		counter;

	counter = 0;
	if (!str)
		str = "(null)";
	while (str[counter])
		counter++;
	return (write(1, str, counter));
}

int	print_format(char fmt, va_list	arg_p)
{
	int	write_chr;

	if (fmt == 's')
		return (ft_print_s(va_arg(arg_p, char *)));
	else if (fmt == 'd' || fmt == 'i')
		return (print_num_base(va_arg(arg_p, int), 10));
	else if (fmt == 'u')
		return (print_unsigned_base(va_arg(arg_p, unsigned int), 10, 'u'));
	else if (fmt == 'p')
		return (ft_print_ptr(va_arg(arg_p, void *)));
	else if (fmt == 'x')
		return (print_unsigned_base(va_arg(arg_p, unsigned int), 16, 'x'));
	else if (fmt == 'X')
		return (print_unsigned_base(va_arg(arg_p, unsigned int), 16, 'X'));
	if (fmt == '%')
		return (write(1, "%", 1));
	else if (fmt == 'c')
	{
		write_chr = (char)va_arg(arg_p, int);
		return (write(1, &write_chr, 1));
	}
	return (-1);
}

int	ft_printf(const char*format, ...)
{
	va_list	arg_p;
	int		count[2];
	char	*fmt_s;

	count[0] = 0;
	count[1] = 0;
	if (format == NULL)
		return (-1);
	fmt_s = (char *)format;
	va_start(arg_p, format);
	while (*fmt_s)
	{
		if (*fmt_s == '%' && val_spc(fmt_s, &count[1]) == -1 && !count[1])
			return (-1);
		else if (*fmt_s == '%' && val_spc(fmt_s, &count[1]) == 0)
			count[0] += write(1, (fmt_s), 1);
		else if (*fmt_s == '%' && val_spc(fmt_s, &count[1]) > 0)
			count[0] += print_format(*(++fmt_s), arg_p);
		else if (*fmt_s && *fmt_s != '%')
			count[0] += write(1, (fmt_s), 1);
		fmt_s++;
	}
	va_end(arg_p);
	return (count[0]);
}
